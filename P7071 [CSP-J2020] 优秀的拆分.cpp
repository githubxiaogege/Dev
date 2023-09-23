#include <cstdio>
using namespace std;
const long long pow2[233] = {8388608, 4194304, 2097152, 1048576, 524288, 262144, 131072, 65536, 32768, 16384, 8192, 4096, 2048, 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2};
long long n;
signed main() {
	scanf("%lld", &n);
	if (n % 2) {
		printf("-1");
		return 0;
	}
	for (int i = 0; i <= 22; i++) {
		if (!pow2[i]) {
			return 0;
		}
		if (n >= pow2[i]) {
			n -= pow2[i];
			printf("%lld ", pow2[i]);
		}
	}
	return 0;
}
