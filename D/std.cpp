#include<bits/stdc++.h>
using i64 = long long;

const int N = 5e8 + 10;
int p[N], num, vis[N], ans[N];
void init() {
	int n = N - 1;
	vis[1] = 1;
	for (int i = 2; i <= n; i ++) {
		if (! vis[i]) {
			p[++ num] = i;
		}
		for (int j = 1; i * p[j] <= n; j ++) {
			vis[i * p[j]] = true;
		    if (i % p[j] == 0) {
		    	break;
		    }
		}
	}
	auto check = [&](int x) -> bool {
		std::vector<int> v;
		while (x) {
			v.push_back(x % 10);
			x /= 10;
		}
		int l = 0, r = v.size() - 1;
		while (l < r) {
			if (v[l] != v[r]) return false;
			l ++;
			r --;
		}
		return true;
	};
	for (int i = 1; i <= n; i ++) {
		ans[i] = ans[i - 1];
		if (! vis[i]) {
			if (check(i)) {
				ans[i] ++;
			}
		}
	}
}
void solve() {
	int n;
	std::cin >> n;
	std::cout << ans[n] << '\n';
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	init();
	int t = 1;
	std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}