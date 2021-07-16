#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1600;
constexpr double oo = 1e9;
constexpr double epslion = 1e-9;

struct Node {
	int next[10];
	int fail;
	bool end;
	int cnt;
	double val;

	int &operator[](int x) {
		return next[x];
	}
};

Node trie[maxn];
int uuid, n, m, step[maxn][maxn][2];
double f[maxn][maxn];
char s[maxn], ans[maxn];
vector<int> tree[maxn];

void insert(char str[], double v) {
	int len = strlen(str + 1), x = 0;
	for (int i = 1; i <= len; ++i) {
		int c = (int)(str[i] - '0');
		if (trie[x][c] == 0)
			trie[x][c] = ++uuid;
		x = trie[x][c];
	}
	trie[x].end = true;
	trie[x].cnt = 1;
	trie[x].val = v;
}

void build() {
	queue<int> q;
	for (int i = 0; i <= 9; ++i)
		if (trie[0][i])
			trie[trie[0][i]].fail = 0, q.push(trie[0][i]);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i <= 9; ++i) {
			if (trie[x][i]) {
				trie[trie[x][i]].fail = trie[trie[x].fail][i];
				q.push(trie[x][i]);
			} else {
				trie[x][i] = trie[trie[x].fail][i];
			}
		}
	}
	for (int i = 1; i <= uuid; ++i)
		tree[trie[i].fail].push_back(i);
}

void DFS(int x) {
	trie[x].cnt += trie[trie[x].fail].cnt;
	trie[x].val += trie[trie[x].fail].val;
	for (int y : tree[x])
		DFS(y);
}

bool check(double mid) {
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= uuid; ++j)
			f[i][j] = -oo;
	f[0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= uuid; ++j) {
			if (f[i - 1][j] == -oo)
				continue;
			if (s[i] != '.') {
				int k = trie[j][s[i] - '0'];
				f[i][k] = max(f[i][k], f[i - 1][j] + trie[k].val - trie[k].cnt * mid);
			} else {
				for (int c = 0; c <= 9; ++c) {
					int k = trie[j][c];
					f[i][k] = max(f[i][k], f[i - 1][j] + trie[k].val - trie[k].cnt * mid);
				}
			}
		}
	}
	double mx = -oo;
	for (int i = 0; i <= uuid; ++i)
		mx = max(mx, f[n][i]);
	return mx > 0;
}

void output(double mid) {
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= uuid; ++j) {
			f[i][j] = -oo;
			step[i][j][0] = step[i][j][1] = -1;
		}
	f[0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= uuid; ++j) {
			if (f[i - 1][j] == -oo)
				continue;
			if (s[i] != '.') {
				int k = trie[j][s[i] - '0'];
				double tmp = f[i - 1][j] + trie[k].val - trie[k].cnt * mid;
				if (f[i][k] < tmp) {
					f[i][k] = tmp;
					step[i][k][0] = j;
					step[i][k][1] = s[i] - '0';
				}
			} else {
				for (int c = 0; c <= 9; ++c) {
					int k = trie[j][c];
					double tmp = f[i - 1][j] + trie[k].val - trie[k].cnt * mid;
					if (f[i][k] < tmp) {
						f[i][k] = tmp;
						step[i][k][0] = j;
						step[i][k][1] = c;
					}
				}
			}
		}
	}
	int id = 0;
	for (int i = 0; i <= uuid; ++i)
		if (f[n][id] < f[n][i])
			id = i;
	int x = id;
	for (int i = n; i >= 1; --i) {
		int y = step[i][x][0];
		ans[i] = (char)(step[i][x][1] + '0');
		x = y;
	}
	ans[n + 1] = '\0';
	cout << (ans + 1) << endl;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("project.in", "r", stdin);
	freopen("project.out", "w", stdout);
#endif
	cin >> n >> m;
	cin >> (s + 1);
	for (int i = 1; i <= m; ++i) {
		char t[maxn];
		int v;
		cin >> (t + 1) >> v;
		insert(t, log(v));
	}
	build();
	DFS(0);
	double l = 0, r = log(oo) + epslion;
	while (r - l > epslion) {
		double mid = (l + r) / 2;
		if (check(mid))
			l = mid;
		else
			r = mid;
	}
	output(l);
	return 0;
}