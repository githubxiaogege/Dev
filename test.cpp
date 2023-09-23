#include<cstdio>
using namespace std;
const int pow2[233]={8338608,4194304,2097152,1048576,524288,262144,131072,65536,32768,16384,8192,4096,2048,1024,512,256,128,64,32,16,8,4,2};
//int n;
signed main(){
	freopen("t.out","w",stdout);
//	scanf("%d",&n);
	for(int n=1;n<=10000000;n++){
		int res=0;
		int nn=n;
		if(nn%2){
			continue;
		}
		printf("n=%d=",n);
		for(int i=0;i<=22;i++){
			if(nn>=pow2[i]){
				nn-=pow2[i];
				res+=pow2[i];
				printf("%d+",pow2[i]);
			}
		}
		if(res!=n){
			printf("WA");
			return 0;
		}
		printf("\n");
	}
		
	return 0;
}
