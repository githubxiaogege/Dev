#include<vector>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define PII pair<int,int>
#define x first
#define y second
using namespace std;
const int N=5e5+7;
int T,n,m,k,cnt;
int c[N];
vector<PII> res;
bool st[N];
signed main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&m,&k);
		memset(st,0,sizeof st);
		cnt=0;
		res.clear();
		for(int i=1;i<=n;i++){
			scanf("%d",&c[i]);
			if(i>1&&c[i]==c[i-1]&&(!st[i-1])){
				st[i]=1;
			}
		}
		for(int i=2;i<=n;i++){
			if(st[i]){
				int k=0;
				if(c[i]==c[i-1]){
					k++;
				}
				if(c[i]==c[i+1]){
					k++;
				}
				res.push_back({i,k});
			}
		}
		sort(res.begin(),res.end(),[&](PII a,PII b){
			return a.y>b.y;
		});
		for(auto t:res){
			if(!m){
				break;
			}
			int i=t.x;
			for(int j=1;j<=k;j++){
				if(j!=c[i-1]&&j!=c[i+1]){
					c[i]=j;
					break;
				}
			}
			m--;
		}
		for(int i=1;i<=n;i++){
			if(c[i]!=c[i-1]){
				cnt++;
			}
		}
		printf("%d\n",cnt);
	}
	return 0;
}
