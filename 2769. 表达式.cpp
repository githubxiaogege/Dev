#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int N=1e6+7;
int n,m,q,k;
int h[N],e[N],ne[N],idx;
int stk[N],top;
int w[N];
char c[N];
bool st[N];
string s;
inline void add(int a,int b){
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
	return ;
}
inline int dfs(int u){
	if(!c[u]){
		return w[u];
	}
	if(c[u]=='!'){
		w[u]=!dfs(e[h[u]]);
	}
	else{
		int a=e[h[u]],b=e[ne[h[u]]];
		if(c[u]=='|'){
			w[u]=dfs(a)|dfs(b);
		}
		else{
			w[u]=dfs(a)&dfs(b);
		}
	}
	return w[u];
}
inline void calc(int u){
	st[u]=true;
	if(!c[u]){
		return ;
	}
	if(c[u]=='!'){
		calc(dfs(e[h[u]]));
		return ;
	}
	else{
		int a=e[h[u]],b=e[ne[h[u]]];
		if(c[u]=='|'){
			if(!w[a]){
				calc(b);
			}
			if(!w[b]){
				calc(a);
			}
		}
		if(c[u]=='&'){
			if(w[a]){
				calc(b);
			}
			if(w[b]){
				calc(a);
			}
		}
	}
	return ;
}
signed main(){
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>s;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&w[i]);
	}
	m=n;
	int len=s.size();
	for(int i=0;i<len;i++){
		if(s[i]==' '){
			continue;
		}
		if(s[i]=='x'){
			int j=i+1,x=0;
			while(j<len&&s[j]>='0'&&s[j]<='9'){
				x=(x<<1)+(x<<3)+s[j++]-'0';
			}
			stk[++top]=x;
			i=j;
		}
		else if(s[i]=='!'){
			c[++m]=s[i];
			add(m,stk[top--]);
			stk[++top]=m;
		}
		else{
			c[++m]=s[i];
			add(m,stk[top--]);
			add(m,stk[top]--);
			stk[++top]=m;
		}
	}
	int res=dfs(m);
	calc(m);
	scanf("%d",&q);
	for(int i=0;i<q;i++){
		scanf("%d",&k);
		if(st[k]){
			printf("%d\n",res^1);
		}
		else{
			printf("%d\n",res);
		}
	}
	return 0;
}
