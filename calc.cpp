#include<cstdio>
#define int double
using namespace std;
const int N=1000;
signed main(){
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			for(int k=1;k<=N;k++){
				if(1.0/j+1.0/(i+k)==0.25){
					printf("x=%.0lf,y=%.0lf,z=%.0lf\n",i,j,k);
				}
			}
		}
	}
	return 0;
}
