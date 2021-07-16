#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

constexpr int maxn = 55;
constexpr ull seed = 998244353;

struct Tree {
	struct Node {
		int to, next;
	};
	Node tree[maxn * 2];
	int uuid, head[maxn], size[maxn];

	void link(int x, int y) {
		tree[++uuid] = {y, head[x]};
		head[x] = uuid;
		tree[++uuid] = {x, head[y]};
		head[y] = uuid;
	}

	ull hash(int root) {
		return hash(root, 0);
	}

	ull hash(int x, int fa) {
		size[x] = 1;
		ull res = 1;
		for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next) {
			if (y == fa)
				continue;
			res ^= hash(y, x) * seed + size[y];
			size[x] += size[y];
		}
		return res;
	}
};

Tree tree[maxn];
int n[maxn], m;
ull val[maxn][maxn];
int fa[maxn];

int find(int x) {
	return fa[x] == x ? x : find(fa[x]);
}

void merge(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx == fy)
		return;
	if (fx > fy)
		swap(fx, fy);
	fa[fy] = fx;
}

bool check(int x, int y) {
	for (int i = 1; i <= n[x]; ++i) {
		for (int j = 1; j <= n[y]; ++j) {
			if (val[x][i] == val[y][j])
				return true;
		}
	}
	return false;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("project.in", "r", stdin);
	freopen("project.out", "w", stdout);
#endif
	cin >> m;
	for (int i = 1; i <= m; ++i) {
		cin >> n[i];
		for (int j = 1; j <= n[i]; ++j) {
			int x;
			cin >> x;
			if (x != 0)
				tree[i].link(j, x);
		}
	}
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= n[i]; ++j)
			val[i][j] = tree[i].hash(j);
	for (int i = 1; i <= m; ++i)
		fa[i] = i;
	for (int i = 1; i <= m; ++i) {
		for (int j = i + 1; j <= m; ++j) {
			if (check(i, j))
				merge(i, j);
		}
	}
	for (int i = 1; i <= m; ++i)
		cout << find(i) << endl;
	return 0;
}