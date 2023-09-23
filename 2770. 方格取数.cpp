#include<cstdio>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
const int N=1e3+7;
int n,m;
int w[N][N],f[N][N];
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%lld",&w[i][j]);
		}
	}
	memset(f,-0x3f,sizeof f);
	f[1][0]=0;
	for(int j=1;j<=m;j++){
		int s=-1e18;
		for(int i=1;i<=n;i++){
			s=max(s,f[i][j-1]+w[i][j]);
			f[i][j]=max(f[i][j],s);
		}
		s=-1e18;
		for(int i=n;i;i--){
			s=max(s,f[i][j-1]+w[i][j]);
			f[i][j]=max(f[i][j],s);
		}
	}
	printf("%lld",f[n][m]);
	return 0;
}
