#include<cmath>
#include<vector>
#include<cstdio>
#include<algorithm>
#define int long long
#define PII pair<int,int>
#define x first
#define y second
using namespace std;
const int N=1e6+7;
int n,cnt;
int nums[N];
vector<PII> res,sub;
inline void pf(){
	putchar('\n');
	for(int i=1;i<=n;i++){
		putchar('0'),putchar(' ');
	}
	return ;
}
inline bool check(int x){
	int u=sqrt(x);
	return u*u==x;
}
inline void calc_one(int p){
//	printf("p=%d\n",p);
	bool left=check(nums[p]+nums[p-1])||(p==1),right=check(nums[p]+nums[p+1])||(p==n);
	if(left&&right){
		return ;
	}
	int l=nums[p-1],r=nums[p+1];
	if(right){
		int u=sqrt(nums[p]);
		if(!check(nums[p])){
			u++;
		}
		nums[p-1]=u*u-nums[p];
	}
	else if(left){
		int u=sqrt(nums[p]);
		if(!check(nums[p])){
			u++;
		}
		nums[p+1]=u*u-nums[p];
	}
	return ;
}
inline void calc_two(int l,int p,int r){
	int s=nums[r]-nums[l];
	sub.clear();
	for(int i=1;i*i<=s;i++){
		if(!(s%i)){
			int ni=s/i;
			sub.push_back({i,ni});
		}
	}
	for(auto m:sub){
		int a=m.x,b=m.y,k;
		int u1=a-b>>1,u2=a+b>>1;
		if(nums[l]>nums[r]){
			k=u1*u1-nums[r];
		}
		else{
			k=u1*u1-nums[l];
		}
		nums[p]=k;
	}
	return ;
}
inline bool equals(){
	for(int i=2;i<=n;i++){
		if((!check(nums[i]+nums[i-1]))){
			return false;
		}
	}
	return true;
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&nums[i]);
	}
	for(int i=2;i<=n-1;i++){
		int k=0;
		if(!check(nums[i]+nums[i-1])){
			k++;
		}
		if(!check(nums[i]+nums[i+1])){
			k++;
		}
		res.push_back({i,k});
	}
	sort(res.begin(),res.end(),[&](PII a,PII b){
		return a.y>b.y;
	});
	for(auto t:res){
		if(equals()){
			break;
		}
		int i=t.x,k=t.y;
		if(k==2){
			calc_two(i-1,i,i+1);
			cnt++;
		}
		else{
			calc_one(i);
			cnt++;
		}
	}
	printf("%d\n",cnt);
	for(int i=1;i<=n;i++){
		printf("%d ",nums[i]);
	}
	return 0;
}
