#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N=5e4+7;
int T,n,x;
vector<int> nums;
signed main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		nums.clear();
		for(int i=0;i<n;i++){
			scanf("%d",&x);
			nums.push_back(x);
		}
		vector<int>::iterator res =unique(nums.begin(),nums.end());
		nums.erase(res,nums.end());
		for(int i=0;i<nums.size();i++){
			printf("%d ",nums[i]);
		}
		putchar('\n');
	}
	return 0;
}
