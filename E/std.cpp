#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

std::vector<int> ans;

struct {
	ll qmul(ll a, ll b, ll mod) {
	    ll c = (ld)a / mod * b;
	    ll res = (ull)a * b - (ull)c * mod;
	    return (res + mod) % mod;
	}
	ll qpow(ll a, ll n, ll mod) {
	    ll res = 1;
	    while (n) {
	        if (n & 1) {
	        	res = qmul(res, a, mod);
	        }
	        a = qmul(a, a, mod);
	        n >>= 1;
	    }
	    return res;
	}
	bool MRtest(ll n) {//Miller Rabin Test
	    if (n < 3 || n % 2 == 0) return n == 2;
	    ll u = n - 1, t = 0;
	    while (u % 2 == 0) {
	    	u /= 2;
	     	++ t;
	    }
	    ll ud[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	    for (ll a : ud) {
	        ll v = qpow(a, u, n);
	        if (v == 1 || v == n - 1 || v == 0) {
	        	continue;
	        }
	        for (int j = 1; j <= t; j ++) {
	            v = qmul(v, v, n);
	            if (v == n - 1 && j != t) {
	            	v=1;
	            	break;
	            }
	            if (v == 1) {
	            	return 0;
	            }
	        }
	        if (v != 1) {
	        	return 0; //Fermat检验
	        }
	    }
	    return 1;
	}
}ty;
bool check(int x) {
	for (int i = 2; i * i <= x; i ++) {
		if (x % i == 0) return 0;
	}
	return 1;
}
void init() {
	ans.push_back(2);
	ans.push_back(3);
	ans.push_back(5);
	ans.push_back(7);
	ans.push_back(11);

	for (int i = 1; i < 10000; i ++) {
		for (int j = 0; j < 10; j ++) {
			int x = i;
			int y = i;
			y = y * 10 + j;
			while (x) {
				y = y * 10 + x % 10;
				x /= 10;
			}
			if (ty.MRtest(y)) {
				ans.push_back(y);
			}/*
			if (check(y)) {
				ans.push_back(y);
			}*/
		}
	}
	ans.push_back(1000000001);
	std::sort(ans.begin(), ans.end());
}
void solve() {
	int n;
	std::cin >> n;
	// er fen
	int x = std::upper_bound(ans.begin(), ans.end(), n) - ans.begin();
	std::cout << x << '\n';
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