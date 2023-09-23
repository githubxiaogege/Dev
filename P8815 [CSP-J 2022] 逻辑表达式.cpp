#include<cstdio>
#include<cstring>
#include<ctype.h>
#include<string>
#include<algorithm>
#include<iostream>
#define fir first
#define sec second
using namespace std;
const int N=1e6+7;
int num[N],num_top;
char op[N];int op_top;
pair<int,int> c[N];int c_top;
pair<int,int> c1,c2;
string s;
inline void calc(){
	int x=num[num_top];
	num_top--;
	c1=c[c_top];
	c_top--;
	int y=num[num_top];
	num_top--;
	c2=c[c_top];
	c_top--;
	char p=op[op_top];
	op_top--;
	if(p=='&'){
		num[++num_top]=x&y;
		if(!y){
			c[++c_top]={c2.fir+1,c2.sec};
		}
		else{
			c[++c_top]={c1.fir+c2.fir,c1.sec+c2.sec};
		}
	}
	if(p=='|'){
		num[++num_top]=x|y;
		if(y){
			c[++c_top]={c2.fir,c2.sec+1};
		}
		else{
			c[++c_top]={c1.fir+c2.fir,c1.sec+c2.sec};
		}
	}
	return ;
}
inline int check(char p){
	if(p=='&'){
		return 2;
	}
	else if(p=='|'){
		return 1;
	}
	if(p=='('){
		return 0;
	}
}
signed main(){
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>s;
	for(int i=0;i<s.size();i++){
		if(isdigit(s[i])){
			num[++num_top]=s[i]-'0';
			c[++c_top]={0,0};
		}
		else{
			if(s[i]=='('){
				op[++op_top]=s[i];
			}
			else if(s[i]==')'){
				while(op[op_top]!='('){
					calc();
				}
				op_top--;
			}
			else{
				while(op_top>0&&check(op[op_top])>=check(s[i])){
					calc();
				}
				op[++op_top]=s[i];
			}
		}
	}
	while(op_top>0){
		calc();
	}
	printf("%d\n%d %d",num[num_top],c[c_top].fir,c[c_top].sec);
	return 0;
}
