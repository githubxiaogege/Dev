#include<bits/stdc++.h>
using namespace std;
string name;
int year,month,day,num;
int main(){
	cin>>name>>year>>month>>day;
	for(int i=0;i<name.length();i++) num=(num*107+name[i]+11)%15;
	num=(((num*31+year)%15*37+month)%15*41+day)%15;
	cout<<num;
	return 0;
}
