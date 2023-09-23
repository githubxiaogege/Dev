#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=500010,M=N<<1;
int n,m,s;
int h[N],e[M],ne[M],idx;
int depth[N],q[N],fa[N][20];
inline void add(int a,int b){
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
	return ;
}
inline void bfs(int root){
	memset(depth,0x3f,sizeof depth);
	depth[0]=0,depth[root]=1;
	int hh=0,tt=0;
	q[0]=root;
	while(hh<=tt){
		int t=q[hh++];
		for(int i=h[t];~i;i=ne[i]){
			int j=e[i];
			if(depth[j]>depth[t]+1){
				depth[j]=depth[t]+1;
				q[++tt]=j;
				fa[j][0]=t;
				for(int k=1;k<=19;k++){
					fa[j][k]=fa[fa[j][k-1]][k-1];
				}
			}
		}
	}
	return ;
}
inline int lca(int a,int b){
	if(depth[a]<depth[b]){
		swap(a,b);
	}
	for(int k=19;k>=0;k--){
		if(depth[fa[a][k]]>=depth[b]){
			a=fa[a][k];
		}
	}
	if(a==b){
		return a;
	}
	for(int k=19;k>=0;k--){
		if(fa[a][k]!=fa[b][k]){
			a=fa[a][k];
			b=fa[b][k];
		}
	}
	return fa[a][0];
}
signed main(){
	scanf("%d%d%d",&n,&m,&s);
	memset(h,-1,sizeof h);
	for(int i=0;i<n-1;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b),add(b,a);
	}
	bfs(s);
	for(int i=0;i<m;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		printf("%d\n",lca(a,b));
	}
	return 0;
}
