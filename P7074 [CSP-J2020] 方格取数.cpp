#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e3+7;
int n,m,res=-0x3f3f3f3f;
int g[N][N],t[N][N][3];
bool vis[N][N];
int dx[3]={1,0,-1},dy[3]={0,1,0};
inline void dfs(int x,int y,int f,int ans){
	if(t[x][y][f]>ans){
		return ;
	}
	t[x][y][f]=ans;
	if(x==n&&y==m){
		return ;
	}
	for(int i=0;i<3;i++){
		int xx=x+dx[i],yy=y+dy[i];
		if(xx<=n&&yy<=m&&xx>=1&&yy>=1&&!vis[xx][yy]){
			vis[xx][yy]=true;
			dfs(xx,yy,i,ans+g[xx][yy]);
			vis[xx][yy]=false;
		}
	}
	return ;
}
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&g[i][j]);
			t[i][j][0]=t[i][j][1]=t[i][j][2]=-1e9;
		}
	}
	t[1][1][0]=t[1][1][1]=t[1][1][2]=g[1][1];
	vis[1][1]=true;
	dfs(1,1,0,g[1][1]);
	printf("%d",t[n][m]);
	return 0;
}
