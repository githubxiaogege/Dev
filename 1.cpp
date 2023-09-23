#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
	try
	{
		// 将ROS图像消息转换为OpenCV图像
		cv_bridge::CvImagePtr cv_ptr;
		cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
		
		// 在这里添加图像处理步骤，用于识别禁止标识
		cv::Mat processed_image = cv_ptr->image.clone();
		
		// 转换为灰度图像
		cv::Mat gray_image;
		cv::cvtColor(processed_image, gray_image, cv::COLOR_BGR2GRAY);
		
		// 使用Canny边缘检测
		cv::Mat edges;
		cv::Canny(gray_image, edges, 50, 150);
		
		// 使用霍夫圆变换检测圆形区域
		std::vector<cv::Vec3f> circles;
		cv::HoughCircles(edges, circles, cv::HOUGH_GRADIENT, 1, edges.rows / 8, 200, 100, 0, 0);
		
		// 遍历检测到的圆
		for (const cv::Vec3f& circle : circles)
		{
			cv::Point center(cvRound(circle[0]), cvRound(circle[1]));
			int radius = cvRound(circle[2]);
			
			// 在圆心处绘制一个标志点  processed_image使用的图片，center图中位置。
			cv::circle(processed_image, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
			
			// 检测x形符号，通过画线交叉的方式
			cv::line(processed_image, cv::Point(center.x - radius, center.y - radius),
				cv::Point(center.x + radius, center.y + radius), cv::Scalar(0, 0, 255), 2, 8, 0);
			cv::line(processed_image, cv::Point(center.x - radius, center.y + radius),
				cv::Point(center.x + radius, center.y - radius), cv::Scalar(0, 0, 255), 2, 8, 0);
		}
		
		// 发布识别后的图像到ROS话题
		cv_bridge::CvImage cv_image;
		cv_image.header = msg->header;
		cv_image.encoding = sensor_msgs::image_encodings::BGR8;
		cv_image.image = processed_image;
		
		image_pub.publish(cv_image.toImageMsg());
	}
	catch (cv_bridge::Exception& e)
	{
		ROS_ERROR("cv_bridge exception: %s", e.what());
	}
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "forbidden_sign_detection");
	ros::NodeHandle nh;
	
	// 订阅相机图像
	image_transport::ImageTransport it(nh);
	image_transport::Subscriber sub = it.subscribe("/camera/image", 1, imageCallback);
	
	// 发布处理后的图像
	image_transport::Publisher image_pub = it.advertise("/forbidden_sign_detected", 1);
	
	ros::spin();
	
	return 0;
}

--------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------



#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <dirent.h>

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>////
#include "geometry_msgs/Twist.h"///
#include <nav_msgs/Odometry.h>
#include "std_msgs/Int8.h"
#include "std_msgs/Float64.h"
#include <std_msgs/Float64MultiArray.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "kcftracker.hpp"

#include "YoloObjectDetector.hpp"
#include <cstring>


using namespace std;
using namespace cv;

static const string RGB_WINDOW = "RGB Image window";
//static const string DEPTH_WINDOW = "DEPTH Image window";

ros::Publisher position_pub_;
ros::Publisher track_pub_;
ros::Publisher pub_;
ros::Subscriber box_sub_;
ros::Subscriber boxes_sub_;
nav_msgs::Odometry point;
std_msgs::Int8 back_msg;
std_msgs::Float64MultiArray track_msg;


Mat rgbimage;
Mat frame;
Mat depthimage;
vector<Rect> boxes, boxes_iou;
Rect selectRect;
Rect roi, roi_iou;
Point origin;
Rect result;
darknet_ros_msgs::BoundingBox boundingBox, boundingBox_person;
double distance_min = 1000.0;

//// 定义参数
//double angle = 90;
//double scale = 0.5;

float p_x, p_y, p_z;
double fx, fy, ppx, ppy;
int center_x, center_y;
double iou;
float distance_;

bool select_flag = false;
bool bRenewROI = false;  // the flag to enable the implementation of KCF algorithm for the new chosen ROI
bool bBeginKCF = false;
bool enable_get_depth = true;

bool HOG = true;
bool FIXEDWINDOW = false;
bool MULTISCALE = true;
bool SILENT = true;
bool LAB = false;


void boxesCb(const darknet_ros_msgs::BoundingBoxesConstPtr& msg)
{
	float nearest_distance = std::numeric_limits<float>::max(); // Initialize to a large value
	int nearest_person_idx = -1;
	
	for(int i = 0; i < msg->bounding_boxes.size(); i++)
	{
		boundingBox = msg->bounding_boxes[i];
		if(boundingBox.Class == "person" && boundingBox.probability > 0.45)
		{
			float dis = distance_;
			if (dis < nearest_distance)
			{
				nearest_distance = distance_;
				nearest_person_idx = i;
			}
		}
	}
	
	if (nearest_person_idx != -1)
	{
		boundingBox_person = msg->bounding_boxes[nearest_person_idx];
		select_flag = true;
	}
	else
	{
		boundingBox_person = darknet_ros_msgs::BoundingBox();
	}
	
	
	int xmin = boundingBox_person.xmin;
	int xmax = boundingBox_person.xmax;
	int ymin = boundingBox_person.ymin;
	int ymax = boundingBox_person.ymax;
	
	selectRect.x = xmin;
	selectRect.y = ymin;
	selectRect.width = xmax - xmin;
	selectRect.height = ymax - ymin;
}


class ImageConverter////////////////////////////////////
{
	ros::NodeHandle nh_;
	image_transport::ImageTransport it_;
	image_transport::Subscriber image_sub_;
	image_transport::Subscriber depth_sub_;
	
	ros::Subscriber camera_info_;
	ros::Subscriber iou_sub_;
	
	sensor_msgs::CameraInfo	camera_info;
	
//	Mat	colorImage;
//	Mat	depthImage	= Mat::zeros( 480, 640, CV_16UC1 );
	
	
	
public:
	ros::Publisher pub;
	ros::Publisher image_pub_; // Add a publisher for the image
	
	ImageConverter() : it_(nh_)
	{
		// Subscrive to input video feed and publish output video feed
		image_sub_ = it_.subscribe("/camera/color/image_raw", 1, 
			&ImageConverter::imageCb, this);
		depth_sub_ = it_.subscribe("/camera/aligned_depth_to_color/image_raw", 1, 
			&ImageConverter::depthCb, this);
		camera_info_ = nh_.subscribe("/camera/aligned_depth_to_color/camera_info", 1,
			&ImageConverter::cameraInfoCb, this);
//		iou_sub_ = nh_.subscribe("/iou_value", 1, &ImageConverter::iouCb, this);
		
//		pub_          = nh_.advertise<std_msgs::Int8>("/bool_found",1);
		track_pub_    = nh_.advertise<std_msgs::Float64MultiArray>("/track_box",1);
		position_pub_ = nh_.advertise<nav_msgs::Odometry>("/people_tracking",1);
//		namedWindow(RGB_WINDOW);
		//namedWindow(DEPTH_WINDOW);
	}
	
	~ImageConverter()
	{
//    	destroyWindow(RGB_WINDOW);
		//destroyWindow(DEPTH_WINDOW);
	}
	
	void imageCb(const sensor_msgs::ImageConstPtr& msg)
	{
		cv_bridge::CvImagePtr cv_ptr;
		try
		{
			cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
		}
		catch (cv_bridge::Exception& e)
		{
			ROS_ERROR("cv_bridge exception: %s", e.what());
			return;
		}
		
		cv_ptr->image.copyTo(frame);
		
		int x = selectRect.x;
		int y = selectRect.y;
		int width = selectRect.width;
		int height = selectRect.height;
		
		if(x < 0) x = 0;
		if(y < 0) y = 0;
		if(width > 424) width = 424;
		if(height > 240) height = 240;
		center_x = x + width/2;
		center_y = y + height/2;
		
//	    cout << "center_x:" << center_x << endl;
//		if(x >= 0 && y >= 0 && width <= 424 && height <= 240)
		if(select_flag)
		{
			rectangle(frame, selectRect, Scalar( 0, 0, 255 ), 2, 8 );
			select_flag = false;
		}
		
		// Convert the OpenCV Mat to sensor_msgs::Image
		cv_bridge::CvImage cv_image;
		cv_image.image = frame;
		cv_image.encoding = sensor_msgs::image_encodings::BGR8;
		
		sensor_msgs::ImagePtr image_msg = cv_image.toImageMsg();
		
		// Publish the image
		image_pub_.publish(image_msg);
		
//    	imshow(RGB_WINDOW, frame);
		waitKey(1);
	}
	
	void cameraInfoCb(const sensor_msgs::CameraInfo &msg)
	{
		camera_info = msg;
		fx  = msg.K[0];
		ppx = msg.K[2];
		fy  = msg.K[4];
		ppy = msg.K[5];
	}
	
	void iouCb(const std_msgs::Float64ConstPtr &msg)
	{
		iou = msg->data;
	}
	
	void depthCb(const sensor_msgs::ImageConstPtr& msg)
	{
		cv_bridge::CvImagePtr cv_ptr;
		try
		{
			cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::TYPE_16UC1);
			cv_ptr->image.copyTo(depthimage);
		}
		catch (cv_bridge::Exception& e)
		{
			ROS_ERROR( "cv_bridge exception: %s", e.what() );
			return;
		}
		
		if(enable_get_depth && center_x > 0 && center_y > 0)
		{
			p_z = depthimage.at<uint16_t>(center_y , center_x);
			distance_ = float(p_z)/1000;
			p_x = (center_x - ppx) / fx * distance_;
			p_y = (center_y - ppy) / fy * distance_;
			
			point.pose.pose.position.x = p_x;
			point.pose.pose.position.y = p_y;
			point.pose.pose.position.z = distance_;
		}
		
	}
};

int main(int argc, char** argv)
{
	ros::init(argc, argv, "kcf_tracker");
	ros::NodeHandle n;
	ImageConverter ic;
	
	boxes_sub_    = n.subscribe("/darknet_ros/bounding_boxes", 1, boxesCb);
	ic.image_pub_ = n.advertise<sensor_msgs::Image>("/people_image", 1);
	
	while(ros::ok())
	{
		ros::spinOnce();
		
//		point.header.frame_id="smart";
//      point.header.stamp.now();
		position_pub_.publish(point);//发布人的位置
		if (waitKey(33) == 'q')
			break;
	}
	
	return 0;
}

