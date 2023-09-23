#include<cstdio>
using namespace std;
signed main(){
	int x=101,y=201;
	int *p=&x,*q=&y;
	p=q;
	printf("%d %d",x,y);
	return 0;
}
