#include<cstdio>
using namespace std;
int num,res;
bool f=false;
signed main(){
	scanf("%d",&num);
	for(int i=2;i<=118098;i+=num,res++){
		if(i==486){
			f=true;
		}
		if(i==118098&&f){
			printf("Fuck CCF");
		}
	}
	return 0;
}
