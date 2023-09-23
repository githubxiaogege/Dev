
#include <bits/stdc++.h>

using namespace std;

int find(int n)
{
	int cnt = 0;
	while(n) cnt++, n >>= 1;
	return cnt;
}

int jos(int n)
{
	int len = find(n);
	n ^= (1 << (len - 1));
	n <<= 1;
	n |= 1;
	return n;
}
int main()
{
	int t, caseno = 0, n, survivor;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		
		int cnt = 0;
		for(;;) {
			cnt++;
			if((survivor = jos(n)) == n) break;
			n = survivor;
		}
		
		printf("Case %d: %d %d\n", ++caseno, cnt - 1, n);
	}
	
	return 0;
}

