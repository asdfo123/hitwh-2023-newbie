#include<bits/stdc++.h>
using i64 = long long;

void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<char>> s(n + 1, std::vector<char>(4));
	for (int i = 1; i <= n; i ++) {
		for (int j = 0; j < 4; j ++) {
			std::cin >> s[i][j];
		}
	}
	std::map<char, int> mp;
	mp['E'] = mp['I'] = 0;
	mp['S'] = mp['N'] = 1;
	mp['T'] = mp['F'] = 2;
	mp['J'] = mp['P'] = 3;
	for (int i = 0; i < m; i ++) {
		int op, l, r;
		std::cin >> op >> l >> r;
		if (op == 1) {
			char c;
			std::cin >> c;
			int d = mp[c];
			for (int j = l; j <= r; j ++) {
				s[j][d] = c; 
			}
		} else {
			for (int j = 0; j < 4; j ++) {
				std::cin >> s[0][j];
			}
			int num = 0;
			for (int j = l; j <= r; j ++) {
				bool f = 1;
				for (int k = 0; k < 4; k ++) {
					if (s[0][k] != 'X' && s[0][k] != s[j][k]) {
						f = 0;
					}
				}
				if (f) {
					num ++;
				}
			}
			std::cout << num << '\n';
		}
	}
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	//std::cin >> t;
	while (t --) {
		solve();
	}
	return 0;
}