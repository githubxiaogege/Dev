#include<cstdio>
#define int long long
using namespace std;
const int N=110;
int n,m,c,b;
int g[N][N],vis[N][N],calc[N][N],cut[N][N];//最优性剪枝
int dx[4]={0,1,0,-1};
int dy[4]={-1,0,1,0};
inline int cal(int i,int j,int t){
	int res=0;
	if(calc[i][j]==1){
		if(t>g[i][j])
	}
	return res;
}
inline void dfs(int x,int y,int ans){
	if(cut[x][y]<ans){
		return ;
	}
	cut[x][y]=ans;
	if(x==n&&y==m){
		return ;
	}
	for(int i=0;i<4;i++){
		int xx=x+dx[i];
		int yy=y+dy[i];
		if(xx>=0&&yy>=0&&xx<=n&&yy<=m&&!vis[xx][yy]&&cal(xx,yy,ans)<=c){
			vis[xx][yy]=true;
			dfs(xx,yy,ans+1);
			vis[xx][yy]=false;
		}
	}
	return ;
}
signed main(){
	scanf("%lld%lld%lld%lld",&n,&m,&c,&b);
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			char op[3];
			scanf("%s",&op);
			g[i][j]=*op-'0';
			calc[i][j]=op[1]=='+'?1:-1;
		}
	}
	dfs(1,1,0);
	
	return 0;
}
