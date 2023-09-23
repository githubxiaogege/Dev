#include<cstdio>
using namespace std;
const int N=5e5+7;
int T,a[N];
signed main(){
	scanf("%d",&T);
	while(T--){
		int op,n,x;
		scanf("%d%d%d",&op,&n,&x);
		if(op==1){
			int num=x-n+2;
			if(num<=0){
				putchar('-'),putchar('1');
				goto print;
			}
			for(int i=1;i<=n-2;i++){
				putchar('1'),putchar(' ');
			}
			for(int i=n-1;i<=n;i++){
				printf("%d ",num);
			}
		}
		else{
			int num=x-n+2;
			if(num<=0){
				putchar('-'),putchar('1');
				goto print;
			}
			for(int i=1;i<=n-1;i++){
				putchar('1'),putchar(' ');
			}
			printf("%d",num);
		}
		print:
			putchar('\n');
	}
	return 0;
}
