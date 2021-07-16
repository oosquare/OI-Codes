#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 100 + 10;
constexpr int maxm = 100000 + 10;

struct Edge {
	int x, y, w;
};

struct Node {
	int sum;
	vector<Edge> edges; 
};

int n, m, q, fa[maxn];
Node tree[maxm * 4];
Edge es[maxm];

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx != fy)
		fa[fy] = fx;
}

Node pushup(Node lhs, Node rhs) {
	int it1 = 0, it2 = 0;
	int ed1 = lhs.edges.size() - 1, ed2 = rhs.edges.size() - 1;
	Node res;
	for (int i = 1; i <= n; ++i)
		fa[i] = i;
	while (it1 <= ed1 && it2 <= ed2) {
		if (lhs.edges[it1].w < rhs.edges[it2].w) {
			int x = lhs.edges[it1].x, y = lhs.edges[it1].y;
			int fx = find(x), fy = find(fy);
			if (fx != fy) {
				fa[fy] = fx;
				res.edges.push_back(lhs.edges[it1]);
			}
			++it1;
		} else {
			int x = rhs.edges[it2].x, y = rhs.edges[it2].y;
			int fx = find(x), fy = find(fy);
			if (fx != fy) {
				fa[fy] = fx;
				res.edges.push_back(rhs.edges[it2]);
			}
			++it2;
		}
		if (res.edges.size() == n - 1)
			break;
	}
	res.sum = 0;
	for (int i = 0; i < res.edges.size(); ++i)
		res.sum += res.edges[i].w;
	return res;
}

void build(int x, int l, int r) {
	if (l == r) {
		tree[x].sum = es[l].w;
		tree[x].edges.push_back(es[l]);
		return;
	}
	int mid = (l + r) / 2;
	build(x * 2, l, mid);
	build(x * 2 + 1, mid + 1, r);
	tree[x] = pushup(tree[x * 2], tree[x * 2 + 1]);
}

Node query(int x, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr)
		return tree[x];
	int mid = (l + r) / 2;
	return pushup(query(x * 2, l, mid, ql, qr), query(x * 2 + 1, mid + 1, r, ql, qr));
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("project.in", "r", stdin);
	freopen("project.out", "w", stdout);
#else
	freopen("forest.in", "r", stdin);
	freopen("forest.out", "w", stdout);
#endif
	cin >> n >> m >> q;
	for (int i = 1; i <= m; ++i)
		cin >> es[i].x >> es[i].y >> es[i].w;
	build(1, 1, m);
	for (int i = 1; i <= q; ++i) {
		int l, r;
		cin >> l >> r;
		cout << query(1, 1, m, l, r).sum << endl;
	}
	return 0;
}