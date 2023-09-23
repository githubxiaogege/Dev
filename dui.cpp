#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
const int N=1010;
int n;
struct Box{
	int a,b,c;
	bool operator<(const Box &box)const{
		if(box.a==a){
			if(box.b==b){
				if(box.c==c){
					return true;
				}
				return box.c<c;
			}
			return box.b>b;
		}
		return box.a<a;
	}
}box[N];
signed main(){
	scanf("%lld",&n);
	for(int i=0;i<n;i++){
		int a,b,c;
		scanf("%lld%lld%lld",&a,&b,&c);
		box[i]={c,a,b};
	}
	sort(box,box+n);
	printf("\n");
	int res=box[0].a;
	for(int i=0;i<n-1;i++){
		auto s=box[i],s1=box[i+1];
		if(s.c>s1.b){
			res+=s1.a;
		}
	}
	printf("%lld",res);
	return 0;
}
