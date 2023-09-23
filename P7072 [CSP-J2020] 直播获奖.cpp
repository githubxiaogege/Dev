#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+7,NUM=610;
int n,w;
int t[NUM];
signed main(){
	scanf("%d%d",&n,&w);
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		t[x]++;
		int p=max(1,i*w/100),jj;
		for(int j=NUM-10;j>=0;j--){
			p-=t[j];
			jj=j;
			if(p<=0){
				break;
			}
		}
		printf("%d ",jj);
	}
	return 0;
}
