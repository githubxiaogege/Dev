#include<cstdio>
#include<string>
#include<iostream>
using namespace std;
const int N=1e4+7;
int n,res;
string str;
inline int calc(int n){
	int cnt=0;
	while(n){
		n/=10;
		cnt++;
	}
	return cnt;
}
signed main(){
	cin.tie(NULL);
	scanf("%d",&n);
	while(n--){
		cin>>str;
		res=0;
		int len=str.length();
		bool f=false;
		char p;
		int num=0;
		for(int i=0;i<len;i++){
			if(!f||p!=str[i]){
				num++;
				res++;
				res+=calc(num);
				p=str[i];
				num=0;
				f=true;
			}
			else{
				num++;
			}
		}
		printf("%d\n",res);
	}
	return 0;
}
