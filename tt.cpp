#include<cstdio>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
const int N=1010,M=1e4;
int n,a[N],b[N],h[N],f[N][M],ans;
signed main()
{
	memset(f,-0x3f,sizeof(f));
	scanf("%lld",&n);
	for (int i=1;i<=n;i++) scanf("%lld%lld%lld",&a[i],&b[i],&h[i]);
	f[n+1][0]=0;
	for (int i=n;i>0;i--)
		for (int j=0;j<=M;j++)
		{
			f[i][j]=f[i+1][j];
			if (j>=a[i]&&b[i]>=j-a[i]){
				f[i][j]=max(f[i][j],f[i+1][j-a[i]]+h[i]);
			}
		}
	for (int i=0;i<=M;i++) ans=max(ans,f[1][i]);
	printf("%lld",ans);
	return 0;
}

