#include <bits/stdc++.h>
using namespace std;

template <typename T>
void checkmax(T &x, const T &y) {
	if (x < y)
		x = y;
}

constexpr int maxsze = 3422;
constexpr int maxv = 1e5 + 5;
constexpr int maxe = maxv << 1;

constexpr int maxs = maxv << 2;

struct request {
	int lca, l, r, t, pos, ls, rs;
	request() {}
	request(int lc, int c, int d, int tim, int p):
		lca(lc), l(c), r(d), t(tim), pos(p) {
		ls = (l - 1) / maxsze + 1;
		rs = (r - 1) / maxsze + 1;
	}
	
	bool operator < (const request &rhs) const {
		if (ls != rhs.ls)
			return ls < rhs.ls;
		if (rs != rhs.rs)
			return rs < rhs.rs;
		return t < rhs.t;
	}
} req[maxv];

int n, m, mC, mQ, mR;
int a[maxv], b[maxv];
int nmaxsze, seq[maxe], st[maxv], ed[maxv];
int nE, to[maxe], nxt[maxe], adj[maxv];
int fa[maxv], sze[maxv], son[maxv], dep[maxv];
int nP, pos[maxv], idx[maxv], top[maxv];
int chg[maxv][3], ans[maxv];

void link(int u, int v) {
	nxt[++nE] = adj[u];
	adj[u] = nE;
	to[nE] = v;
}

namespace segment_tree {

	struct info {
		int sze, lef, rit;
		info() {}
		info(int a, int b, int c):
			sze(a), lef(b), rit(c) {}
			
		info operator + (const info &rhs) const {
			if (lef == -1)
				return rhs;
			if (rhs.lef == -1)
				return *this;
			return info(sze + rhs.sze - (rit == rhs.lef), lef, rhs.rit);

		}
		
		info swap() {
			return info(sze, rit, lef);
		}

	} seg[maxs];
	
	void upt(int x) {
		seg[x] = seg[x << 1] + seg[x << 1 | 1];

	}
	
	void build(int x, int l, int r) {
		if (l == r) {
			seg[x] = info(1, a[idx[l]], a[idx[l]]);
			return;
		}
		int mid = (l + r) / 2;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
		upt(x);
	}
	
	info seg_query(int x, int l, int r, int u, int v) {

		if (u <= l && r <= v)
			return seg[x];
		info res(0, -1, -1);

		int mid = (l + r) / 2;
		if (u <= mid)
			res = res + seg_query(x << 1, l, mid, u, v);
		if (v > mid)
			res = res + seg_query(x << 1 | 1, mid + 1, r, u, v);
		return res;

	}
	
	void seg_modify(int x, int l, int r, int pos, int val) {

		if (l == r) {
			seg[x] = info(1, val, val);
			return;
		}
		int mid = (l + r) / 2;
		if (pos <= mid)
			seg_modify(x << 1, l, mid, pos, val);
		else
			seg_modify(x << 1 | 1, mid + 1, r, pos, val);
		upt(x);
	}
}

namespace heavy_path {

	using namespace segment_tree;
	void DFmaxsze1(int u) {
		seq[st[u] = ++nmaxsze] = u;
		sze[u] = 1;
		for (int e = adj[u], v; v = to[e], e; e = nxt[e])
			if (v != fa[u]) {
				fa[v] = u;
				dep[v] = dep[u] + 1;
				DFmaxsze1(v);
				sze[u] += sze[v];
				if (sze[v] > sze[son[u]])
					son[u] = v;

			}
		seq[ed[u] = ++nmaxsze] = u;

	}
	
	void DFmaxsze2(int u) {
		if (son[u]) {
			top[son[u]] = top[u];
			idx[pos[son[u]] = ++nP] = son[u];
			DFmaxsze2(son[u]);
		}
		for (int e = adj[u], v; v = to[e], e; e = nxt[e])
			if (v != fa[u] && v != son[u]) {
				top[v] = v;
				idx[pos[v] = ++nP] = v;
				DFmaxsze2(v);
			}

	}
	
	void modify(int u, int val) {
		seg_modify(1, 1, n, pos[u], val);

	}
	
	int query(int u, int v) {
		info resl(0, -1, -1), resr(0, -1, -1);
		while (top[u] != top[v]) {
			if (dep[top[u]] < dep[top[v]]) {
				resr = seg_query(1, 1, n, pos[top[v]], pos[v]) + resr;
				v = fa[top[v]];
			} else {
				resl =resl + seg_query(1, 1, n, pos[top[u]], pos[u]).swap();
				u = fa[top[u]];

			}
		}
		if (dep[u] < dep[v])
			return (resl+seg_query(1, 1, n, pos[u], pos[v]) + resr).sze;
		else
			return (resl+seg_query(1,1,n,pos[v],pos[u]).swap()+resr).sze;

	}
	
	int LCA(int u, int v) {
		while (top[u] != top[v]) {
			if (dep[top[u]] > dep[top[v]])
				u = fa[top[u]];
			else
				v = fa[top[v]];
		}
		return dep[u] < dep[v] ? u : v;
	}
}

bool exist[maxv];
int cnt[maxv], sum[maxv], maxcnt;

void add_x(int x) {
	++cnt[x];
	if (cnt[x])
		--sum[cnt[x] - 1];
	if (!(sum[cnt[x]]++))
		checkmax(maxcnt, cnt[x]);

}

void dec_x(int x) {
	--cnt[x], ++sum[cnt[x]];
	if (!(--sum[cnt[x] + 1]) && maxcnt == cnt[x] + 1)
		--maxcnt;

}

void modify(int x) {
	if (exist[x]) {
		exist[x] = false;
		dec_x(a[x]);
	} else {
		exist[x] = true;
		add_x(a[x]);
	}
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
	freopen("cw.in", "r", stdin);
	freopen("cw.out", "w", stdout);
#endif
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		b[i] = a[i];
	}
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		link(u, v), link(v, u);
	}
	using namespace heavy_path;
	DFmaxsze1(1);
	nP = idx[1] = pos[1] = top[1] = 1;
	DFmaxsze2(1);
	using namespace segment_tree;
	build(1, 1, n);
	for (int i = 1; i <= m; ++i) {
		int opt, u, v;
		cin >> opt >> u >> v;

		if (opt == 1) {
			++mC;
			chg[mC][0] = u;
			chg[mC][1] = b[u];
			chg[mC][2] = b[u] = v;
			modify(u, v);
		} else if (opt == 2)
			ans[++mQ] = query(u, v);
		else {
			++mQ;
			if (u == v) {
				ans[mQ] = 1;
				continue;
			}
			int lca = LCA(u, v);
			if (u == lca || v == lca) {
				if (dep[u] > dep[v]) swap(u, v);
				req[++mR] = request(0, st[u], st[v], mC, mQ);
			} else {
				if (ed[u] > st[v]) swap(u, v);
				req[++mR] = request(lca, ed[u], st[v], mC, mQ);
			}
		}
	}
	sort(req + 1, req + mR + 1);
	sum[0] = n;
	int l = 1, r = 0, tim = 0;
	for (int i = 1; i <= mR; ++i) {
		int ql = req[i].l, qr = req[i].r, qt = req[i].t;
		while (tim < qt) {
			++tim;
			int x = chg[tim][0];
			a[x] = chg[tim][2];
			if (exist[x]) {
				dec_x(chg[tim][1]);
				add_x(chg[tim][2]);
			}
		}
		while (tim > qt) {
			int x = chg[tim][0];
			a[x] = chg[tim][1];
			if (exist[x]) {
				add_x(chg[tim][1]);
				dec_x(chg[tim][2]);
			}
			--tim;
		}
		while (l < ql) modify(seq[l++]);
		while (l > ql) modify(seq[--l]);
		while (r < qr) modify(seq[++r]);
		while (r > qr) modify(seq[r--]);
		if (req[i].lca) {
			modify(req[i].lca);
			ans[req[i].pos] = maxcnt;
			modify(req[i].lca);
		} else
			ans[req[i].pos] = maxcnt;
	}
	for (int i = 1; i <= mQ; ++i) {
		cout << ans[i] << endl;
	}
	return 0;
}
