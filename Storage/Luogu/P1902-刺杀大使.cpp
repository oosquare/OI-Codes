#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1000 + 10;

int n, m, timer, mx;
int grid[maxn][maxn];
int vis[maxn][maxn];
constexpr int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool invaild(int x, int y) {
    return x < 1 || x > n || y < 1 || y > m;
}

bool check(int mid) {
    ++timer;
    queue<pair<int, int>> q;
    
    for (int i = 1; i <= m; ++i) {
        vis[1][i] = timer;
        q.push({1, i});        
    }

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == n)
            return true;

        for (int i = 0; i < 4; ++i) {
            int nx = x + dir[i][0], ny = y + dir[i][1];

            if (invaild(nx, ny) || vis[nx][ny] == timer || grid[nx][ny] > mid)
                continue;

            q.push({nx, ny});
            vis[nx][ny] = timer;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> grid[i][j];
            mx = max(mx, grid[i][j]);
        }
    }

    int left = 0, right = mx, ans = mx;
    
    while (left <= right) {
        int mid = (left + right) / 2;

        if (check(mid)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    cout << ans << endl;
    return 0;
}