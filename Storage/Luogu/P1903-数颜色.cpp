#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 150000;

struct querys {
	int l, r, id, time;
};

struct mo {
	int p, c1, c2;
};

querys qs[maxn];
mo ms[maxn];
int cnt[1000005], mid, qid, ans, anss[maxn];
int n, m, sze, co[maxn], tco[maxn];
int l = 1, r = 1, now;

bool operator<(querys lhs, querys rhs) {
	if (lhs.l / sze != rhs.l / sze)
		return lhs.l < rhs.l;
	if (lhs.r / sze != rhs.r / sze)
		return lhs.r < rhs.r;
	return lhs.id < rhs.id;
}

void add(int c) {
	if (cnt[c] == 0)
		++ans;
	++cnt[c];
}

void del(int c) {
	--cnt[c];
	if (cnt[c] == 0)
		--ans;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("project.in", "r", stdin);
	freopen("project.out", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin >> n >> m;
	sze = pow(n, 2.0 / 3.0);
	for (int i = 1; i <= n; ++i)
		cin >> co[i], tco[i] = co[i];
	for (int i = 1; i <= m; ++i) {
		char s[5];
		int x, y;
		cin >> s >> x >> y;
		if (s[0] == 'Q') {
			++qid;
			qs[qid] = {x, y, qid, mid};
		} else {
			ms[mid] = {x, tco[x], y};
			tco[x] = y;
			++mid;
		}
	}
	sort(qs + 1, qs + 1 + qid);
	add(co[1]);
	for (int i = 1; i <= qid; ++i) {
		for (; now < qs[i].time; ++now) {
			if (l <= ms[now].p && ms[now].p <= r)
				del(ms[now].c1), add(ms[now].c2);
			co[ms[now].p] = ms[now].c2;
		}
		for (; now > qs[i].time; --now) {
			if (l <= ms[now - 1].p && ms[now - 1].p <= r)
				del(ms[now - 1].c2), add(ms[now - 1].c1);
			co[ms[now - 1].p] = ms[now - 1].c1;
		}
		for (++r; r <= qs[i].r; ++r)
			add(co[r]);
		for (--r; r > qs[i].r; --r)
			del(co[r]);
		for (--l; l >= qs[i].l; --l)
			add(co[l]);
		for (++l; l < qs[i].l; ++l)
			del(co[l]);
		anss[qs[i].id] = ans;
	}
	for (int i = 1; i <= qid; ++i)
		cout << anss[i] << endl;
	return 0;
}