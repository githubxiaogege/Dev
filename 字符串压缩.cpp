#include <iostream> 
using namespace std; 
int a[10001] = {0}; 
int main() { 
	int n; 
	cin >> n; 
	for (int i = 1; i <= n; i++) 
		cin >> a[i]; 
	int cnt = 0; 
	for (int i = 1; i <= n; i++) { 
		int cur = i; 
		while (a[cur] < a[cur - 1] && cur >1)
			swap(a[cur], a[cur - 1]); 
			cur--; 
			cnt++; 
			
	} 
	
	cout << cnt << endl; 
	return 0;
}
