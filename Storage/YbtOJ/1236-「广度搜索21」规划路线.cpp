#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 800 + 10;
constexpr int oo = 0x3f3f3f3f;

char board[maxn][maxn];
int n, k, timet[maxn][maxn], step[maxn][maxn];
int sx, sy, ex, ey;
int dir[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

bool vaild(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > n)
        return false;
    if (board[x][y] == 'T' || board[x][y] == 'H')
        return false;
    return true;
}

int gettime(int t0, int step) {
    if (step % k == 0) {
        return t0 + step / k;
    } else {
        return t0 + step / k;
    }
}

bool vaild(int x, int y, int t0, int step) {
    if (x < 1 || x > n || y < 1 || y > n)
        return false;
    if (board[x][y] == 'T' || timet[x][y] <= gettime(t0, step))
        return false;
    return true;
}

void preprocess() {
    queue<pair<int, int>> q;
    memset(timet, 0x3f, sizeof(timet));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (board[i][j] == 'M')
                sx = i, sy = j;
            else if (board[i][j] == 'D')
                ex = i, ey = j;
            else if (board[i][j] == 'H')
                q.push(make_pair(i, j)), timet[i][j] = 0;
        }
    }
    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int nx = x + dir[i][0], ny = y + dir[i][1];
            if (!vaild(nx, ny))
                continue;
            if (timet[nx][ny] != oo)
                continue;
            timet[nx][ny] = timet[x][y] + 1;
            q.push(make_pair(nx, ny));
        }
    }
}

bool check(int t0) {
    if (timet[ex][ey] <= t0 || timet[sx][sy] <= t0)
        return false;
    queue<pair<int, int>> q;
    q.push(make_pair(sx, sy));
    memset(step, 0, sizeof(step));
    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int nx = x + dir[i][0], ny = y + dir[i][1];
            if (!vaild(nx, ny, t0, step[x][y] + 1))
                continue;
            if (step[nx][ny] != 0)
                continue;
            step[nx][ny] = step[x][y] + 1;
            q.push(make_pair(nx, ny));
        }
    }
    return step[ex][ey] != 0;
}

int solve() {
    int l = 0, r = oo - 1, ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("mecho.in", "r", stdin);
    freopen("mecho.out", "w", stdout);
#endif
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> (board[i] + 1);
    preprocess();
    cout << solve() << endl;
    return 0;
}
