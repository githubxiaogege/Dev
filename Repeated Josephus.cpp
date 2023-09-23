#include<cstdio>
#include<cmath>
using namespace std;
int T,x,cnt,num;
inline int find(int n){//看n个人中要出圈多少人
	int res=0;//初始化
	while(n){
		res++;//次方数加一
		n>>=1;//位运算,相当于n/=2
	}
	return res;//答案为res,2^res=(n);
}
inline int calc(int k){
	k=((k^(1<<(find(k)-1)))<<1)|1;//计算出队后剩下的人数
	return k;
}
signed main(){
	scanf("%d",&T);//多组测试数据
	while(T--){
		scanf("%d",&x);
		int i=0;
		for(;;){
			i++;
			if(((num=calc(x))==x)){//如果出队的人数够了就跳出循环
				break;
			}
			x=num;//出队
		}
		cnt++;//测试数据组数计数器+1
		printf("Case %d: %d %d\n",cnt,i-1,x);//输出
	}
	return 0;
}
