#include <bits/stdc++.h>
using i64 = long long;
#define int i64

signed main() {
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
	
	int n, k, a;
	std::cin >> n >> k >> a;
	std::vector<int> s(n + 1), c(n + 1); // 二次差分数组
	for (int i = 1; i <= n; i ++) {
		std::cin >> s[i];
	}
	int ans = 0, sum = 0, d = 0; //原数组 和 差分数组
	for (int i = n; i >= 1; i --) { // 倒序，找到未消灭的
		d += c[i];
		sum += d;
		int l = std::max(1ll, i - k + 1), len = i - l + 1, at = (a + len - 1);
		s[i] += sum;
		int num = (s[i] + at - 1) / at;
		if (num > 0) {	//二次差分
			ans += num;
			d -= num * at;
			sum -= num * at;
			c[i - 1] += num * (at + 1);
			if (l - 1 > 0) c[l - 1] += num * (a - 1);
			if (l - 2 > 0) c[l - 2] -= num * a;
		}
	}
	std::cout << ans << '\n';
	return 0;
}