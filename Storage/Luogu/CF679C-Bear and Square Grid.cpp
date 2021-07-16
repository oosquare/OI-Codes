#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 500 + 10;

int n, k, dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int b, res, ans, id[maxn][maxn], sum[maxn][maxn], vis[maxn][maxn];
int cnt[maxn * maxn], sze[maxn * maxn];
char grid[maxn][maxn];

int vaild(int x, int y) {
	return 1 <= x && x <= n && 1 <= y && y <= n;
} 

void BFS(int sx, int sy) {
	queue<pair<int, int>> q;
	q.push(make_pair(sx, sy));
	vis[sx][sy] = true;
	id[sx][sy] = ++b;
	sze[b] = 1;
	while (!q.empty()) {
		int x = q.front().first, y = q.front().second;
		q.pop();
		for (int i = 0; i < 4; ++i) {
			int nx = x + dir[i][0], ny = y + dir[i][1];
			if (!vaild(nx, ny) || vis[nx][ny] || grid[nx][ny] == 'X')
				continue;
			id[nx][ny] = b;
			++sze[b];
			vis[nx][ny] = true;
			q.push(make_pair(nx, ny));
		}
	}
}

void add(int x, int y) {
	if (!vaild(x, y) || !id[x][y])
		return;
	int bid = id[x][y];
	++cnt[bid];
	if (cnt[bid] == 1)
		res += sze[bid];
}

void sub(int x, int y) {
	if (!vaild(x, y) || !id[x][y])
		return;
	int bid = id[x][y];
	--cnt[bid];
	if (cnt[bid] == 0)
		res -= sze[bid];
}

int calc(int x, int y) {
	int x0 = x + k - 1, y0 = y + k - 1;
	return sum[x0][y0] - sum[x - 1][y0] - sum[x0][y - 1] + sum[x - 1][y - 1];
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("project.in", "r", stdin);
	freopen("project.out", "w", stdout);
#endif
	cin >> n >> k;
	for (int i = 1; i <= n; ++i)
		cin >> (grid[i] + 1);
	
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			sum[i][j] = (grid[i][j] == '.' ? 1 : 0) + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (grid[i][j] == '.' && !vis[i][j])
				BFS(i, j);
	for (int i = 1; i + k - 1 <= n; ++i) {
		memset(cnt, 0, sizeof(cnt));
		res = 0;
		for (int j = i - 1; j <= i + k; ++j)
			for (int l = 1; l <= k; ++l)
				add(j, l);
		for (int j = i; j <= i + k - 1; ++j)
			add(j, k + 1);
		ans = max(ans, res + k * k - calc(i, 1));
		for (int j = 2; j + k - 1 <= n; ++j) {
			for (int l = i; l <= i + k - 1; ++l) {
				sub(l, j - 2);
				add(l, j + k);
			}
			sub(i - 1, j - 1);
			sub(i + k, j - 1);
			add(i - 1, j + k - 1);
			add(i + k, j + k - 1);
			ans = max(ans, res + k * k - calc(i, j));
		}
	}
	cout << ans << endl;
	return 0;
}