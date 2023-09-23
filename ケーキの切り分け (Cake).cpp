#include <bits/stdc++.h>
using namespace std;

using i32 = int;
using i64 = long long;
template <typename T>
using Vec = vector<T>;

#define OVERRIDE4(a, b, c, d, ...) d
#define REP2(i, n) for (i32 i = 0; i < (i32)(n); ++i)
#define REP3(i, m, n) for (i32 i = (i32)(m); i < (i32)(n); ++i)
#define REP(...) OVERRIDE4(__VA_ARGS__, REP3, REP2)(__VA_ARGS__)
#define PER2(i, n) for (i32 i = (i32)(n) - 1; i >= 0; --i)
#define PER3(i, m, n) for (i32 i = (i32)(n) - 1; i >= (i32)(m); --i)
#define PER(...) OVERRIDE4(__VA_ARGS__, PER3, PER2)(__VA_ARGS__)
#define ALL(x) begin(x), end(x)

template <typename T>
bool chmin(T &x, const T &y) {
	if (x > y) {
		x = y;
		return true;
	} else {
		return false;
	}
}
template <typename T>
bool chmax(T &x, const T &y) {
	if (x < y) {
		x = y;
		return true;
	} else {
		return false;
	}
}

constexpr i32 INF = 1001001001;
constexpr i64 INF64 = 3003003003003003003;

i32 msb(i32 x) {
	assert(x > 0);
	return 31 - __builtin_clz(x);
}

class SparseTable {
	using Value = i64;
	Vec<Vec<Value>> data;
	
public:
	SparseTable(Vec<Value> a) : data() {
		assert(!a.empty());
		i32 n = (i32)a.size();
		i32 m = msb(n);
		data.resize(m + 1);
		data[0] = a;
		REP(i, m) {
			i32 l = 1 << i, l2 = 1 << (i + 1);
			data[i + 1].resize(n - l2 + 1);
			REP(j, n - l2 + 1) {
				data[i + 1][j] = min(data[i][j], data[i][j + l]);
			}
		}
	}
	
	Value rmin(i32 l, i32 r) const {
		assert(l < r);
		i32 m = msb(r - l);
		return min(data[m][l], data[m][r - (1 << m)]);
	}
};

int main() {
	i32 n;
	cin >> n;
	Vec<i64> a(2 * n);
	REP(i, n) {
		cin >> a[i];
		a[i + n] = a[i];
	}
	
	Vec<i64> sum(2 * n + 1, 0), esum(2 * n + 1, 0);
	REP(i, 2 * n) {
		sum[i + 1] = sum[i] + a[i];
		esum[i + 1] = esum[i] + (i % 2 == 0 ? a[i] : 0);
	}
	
	SparseTable sp(a);
	
	map<pair<i32, i32>, i64> memo;
	const auto dp = [&](const auto &dp, i32 l, i32 r) -> i64 {
		if (r - l == 0) {
			return 0;
		}
		if (r - l == 1) {
			return a[l];
		}
		if (memo.count(make_pair(l, r))) {
			return memo[make_pair(l, r)];
		}
		
		i64 ans = 0;
		i64 nl = l, nr = r;
		if (a[l] > a[r - 1]) {
			i32 ok = l + 1, ng = r;
			while (ng - ok > 1) {
				i32 mid = (ok + ng) / 2;
				if (sp.rmin(l, mid) > a[r - 1]) {
					ok = mid;
				} else {
					ng = mid;
				}
			}
			nl = ok;
			if (l % 2 == 0) {
				ans += esum[ok] - esum[l];
			} else {
				ans += sum[ok] - sum[l] - (esum[ok] - esum[l]);
			}
		} else {
			i32 ok = r - 1, ng = l;
			while (ok - ng > 1) {
				i32 mid = (ok + ng) / 2;
				if (sp.rmin(mid, r) > a[l]) {
					ok = mid;
				} else {
					ng = mid;
				}
			}
			nr = ok;
			if (r % 2 == 0) {
				ans += sum[r] - sum[ok] - (esum[r] - esum[ok]);
			} else {
				ans += esum[r] - esum[ok];
			}
		}
		i64 sub = dp(dp, nl, nr);
		if ((r - l - (nr - nl)) % 2 == 0) {
			ans += sub;
		} else {
			ans += sum[nr] - sum[nl] - sub;
		}
		
		//cerr << l << ' ' << r << ' ' << nl << ' ' << nr << ' ' << ans << '\n';
		memo[make_pair(l, r)] = ans;
		return ans;
	};
	
	Vec<i64> ans(n);
	REP(i, n) {
		i64 sub = dp(dp, i + 1, i + n);
		ans[i] = sum[n] - sub;
	}
	
	REP(i, n) {
		cout << ans[i] << '\n';
	}
}
