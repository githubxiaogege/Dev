#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2e5+7;
int n,x,res,cnt;
int a[N];
inline int calc(int k){
	int ans=0;
	for(int i=1;i*i<=k;i++){
		if(!(k%i)){
			int j=k/i;
			if(a[i]&&a[j]){
				int g=(a[i]*a[j])*a[k];
				if(i!=j){
					ans+=(g<<1);
				}
				else{
					ans+=g;
				}
			}
		}
	}
	return ans;
}
signed main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&x);
		a[x]++;
		cnt=max(cnt,x);
	}
	for(int i=1;i<=cnt;i++){
		if(a[i]){
			res+=calc(i);
		}
	}
	printf("%d",res);
	return 0;
}
