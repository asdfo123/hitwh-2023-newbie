#include <bits/stdc++.h>
using i64 = long long;
#define int i64

const int M = 5e5 + 10;
int s[M];
struct SegmentTree {
    int l, r;
    i64 sum, add;
}t[M << 2];
void pushup(int p) {
    t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
}
void pushdown(int p) {
    if (! t[p].add) return ;
    t[p << 1].add += t[p].add;
    t[p << 1 | 1].add += t[p].add;
    t[p << 1].sum += t[p].add * (t[p << 1].r - t[p << 1].l + 1);
    t[p << 1 | 1].sum += t[p].add * (t[p << 1 | 1].r - t[p << 1 | 1].l + 1);
    t[p].add = 0;
}
void build(int p, int l, int r) {
    t[p] = {l, r, 0, 0};
    if (l == r) {
        t[p].sum = s[l];
        return ;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}
void update(int p, int l, int r, int v) {
	if (t[p].l >= l && t[p].r <= r) {
		t[p].sum += v * (t[p].r - t[p].l + 1);
		t[p].add += v;
		return ;
	}
	pushdown(p);
	int mid = (t[p].l + t[p].r) >> 1;
	if (l <= mid) update(p << 1, l, r, v);
	if (r > mid) update(p << 1 | 1, l, r, v);
	pushup(p);
}
void update(int p, int x, int v) {
	if (t[p].l == t[p].r) {
		t[p].sum += v;

		return ;
	}
	pushdown(p);
	int mid = (t[p].l + t[p].r) >> 1;
	if (x <= mid) update(p << 1, x, v);
	if (x > mid) update(p << 1 | 1, x, v);
	pushup(p);
}
int query(int p, int l, int r) {
    if (t[p].l >= l && t[p].r <= r) {
        return t[p].sum;
    }
    pushdown(p);
    int res = 0;
    int mid = (t[p].l + t[p].r) >> 1;
    if (l <= mid) res += query(p << 1, l, r);
    if (r > mid) res += query(p << 1 | 1, l, r);
    return res;
}

signed main() {
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
	
	int n, k, a;
	std::cin >> n >> k >> a;
	for (int i = 1; i <= n; i ++) {
		std::cin >> s[i];
	}
	for (int i = n; i >= 1; i --) {
		s[i] = s[i] - s[i - 1];
	}
	build(1, 1, n);
	int ans = 0;
	for (int i = n; i >= 1; i --) {
		int T = query(1, 1, i);
		if (T <= 0) continue;
		int l = std::max(1ll, i - k + 1), len = i - l + 1, at = (a + len - 1);

		int num = (T + at - 1) / at;
		ans += num;
		update(1, l, i, - num * 1); // 正序， 区别于上次倒序叠加。
		update(1, l, num * (1 - a));
	}
	std::cout << ans << '\n';
	return 0;
}