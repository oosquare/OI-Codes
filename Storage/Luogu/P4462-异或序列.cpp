#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5 + 10;

typedef long long ll;

struct range {
	int l, r, id;
};

int n, m, k, l, r, a[maxn], cnt[maxn];
int blocksize, res;
range qs[maxn];
ll ans[maxn];

int blockid(int x) {
	return (x - 1) / blocksize + 1;
}

void add(int x) {
	res += cnt[k ^ a[x]];
	++cnt[a[x]];
}

void sub(int x) {
	res -= cnt[k ^ a[x]];
	--cnt[a[x]];
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("project.in", "r", stdin);
	freopen("project.out", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin >> n >> m >> k;
	blocksize = sqrt(n);
	for (int i = 1; i <= n; ++i)
		cin >> a[i], a[i] ^= a[i - 1];
	for (int i = 1; i <= m; ++i) {
		cin >> qs[i].l >> qs[i].r;
		--qs[i].l;
		qs[i].id = i;
	}
	sort(qs + 1, qs + 1 + m, [](const range &a, const range &b) {
        return blockid(a.l) == blockid(b.l)
                   ? (a.r == b.r ? 0 : (blockid(a.l) & 1) ^ (a.r < b.r))
                   : a.l < b.l;
    });
	int l = 1, r = 0;
	for (int i = 1; i <= m; ++i) {
		while (l > qs[i].l)
			add(--l);
		while (r < qs[i].r)
			add(++r);
		while (l < qs[i].l)
			sub(l++);
		while (r > qs[i].r)
			sub(r--);
		ans[qs[i].id] = res;
	}
	for (int i = 1; i <= m; ++i)
		cout << ans[i] << endl;
	return 0;
}