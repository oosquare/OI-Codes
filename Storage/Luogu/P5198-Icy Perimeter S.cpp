#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1000 + 10;

int n, id, ans[2];
char grid[maxn][maxn];
int vis[maxn][maxn], area[maxn * maxn], perimeter[maxn * maxn];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool invaild(int x, int y) {
    return x < 1 || x > n || y < 1 || y > n;
}

int degree(int x, int y) {
    int res = 0;
    for (int k = 0; k < 4; ++k) {
        int nx = x + dir[k][0], ny = y + dir[k][1];
        if (invaild(nx, ny))
            continue;
        if (grid[nx][ny] == '#')
            ++res;
    }
    return res;
}

void calc(int id, int sx, int sy) {
    queue<pair<int, int>> q;
    vis[sx][sy] = id;
    q.push({sx, sy});
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        ++area[id];
        perimeter[id] += 4 - degree(x, y);
        for (int i = 0; i < 4; ++i) {
            int nx = x + dir[i][0], ny = y + dir[i][1];
            if (invaild(nx, ny) || grid[nx][ny] == '.' || vis[nx][ny] != 0)
                continue;
            vis[nx][ny] = id;
            q.push({nx, ny});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> (grid[i] + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (grid[i][j] == '.' || vis[i][i] != 0)
                continue;
            calc(++id, i, j);
        }
    }
    for (int i = 1; i <= id; ++i) {
        if (ans[0] < area[i]) {
            ans[0] = area[i];
            ans[1] = perimeter[i];
        } else if (ans[0] == area[i] && ans[1] > perimeter[i]) {
            ans[1] = perimeter[i];
        }
    }
    cout << ans[0] << " " << ans[1] << endl;
    return 0;
}