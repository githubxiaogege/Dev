#include<unordered_map>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=210;
int n,k,T,S,E;
int res[N][N],g[N][N];
inline void mul(int c[][N],int a[][N],int b[][N]){
	static int temp[N][N];
	memset(temp,0x3f,sizeof temp);
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				temp[i][j]=min(temp[i][j],a[i][k]+b[k][j]);
	memcpy(c,temp,sizeof temp);
	return ;
}
inline void qmi(){
	memset(res,0x3f,sizeof res);
	for(int i=1;i<=n;i++) res[i][i]=0;
	while(k)
	{
		if(k&1) mul(res,res,g);
		mul(g,g,g);
		k>>=1;
	}
	return ;
}
signed main(){
	unordered_map<int,int> id;
	scanf("%d%d%d%d",&k,&T,&S,&E);
	id[S]=++n;
	id[E]=++n;
	for(int i=0;i<T;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		if(!id.count(a)){
			id[a]=++n;
		}
		if(!id.count(b)){
			id[b]=++n;
		}
		a=id[a],b=id[b];
		g[a][b]=g[b][a]=min(g[a][b],c);
	}
	qmi();
	printf("%d",res[S][E]);
	return 0;
}
