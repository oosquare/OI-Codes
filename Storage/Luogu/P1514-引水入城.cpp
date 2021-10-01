#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 500 + 10;
constexpr int maxm = 500 + 10;

struct Range {
    int l, r;

    void update(const Range &other) {
        if (other.l == 0 && other.r == 0)
            return;
        if (l == 0 && r == 0) {
            l = other.l;
            r = other.r;
            return;
        }
        l = min(l, other.l);
        r = max(r, other.r);
    }
};

int n, m, height[maxn][maxm], in[maxn * maxm], f[maxn][maxm];
int seg[maxm * 4];
Range range[maxn * maxm];
bool vis[maxn][maxm];
vector<int> graph[maxn * maxm];
constexpr int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void pushup(int x) {
    seg[x] = min(seg[x * 2], seg[x * 2 + 1]);
}

void build(int x, int l, int r, int a[]) {
    if (l == r) {
        seg[x] = a[l - 1];
        return;
    }
    int mid = (l + r) / 2;
    build(x * 2, l, mid, a);
    build(x * 2 + 1, mid + 1, r, a);
    pushup(x);
}

int query(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return seg[x];
    int mid = (l + r) / 2, res = 0x3f3f3f3f;
    if (ql <= mid)
        res = min(res, query(x * 2, l, mid, ql, qr));
    if (mid < qr)
        res = min(res, query(x * 2 + 1, mid + 1, r, ql, qr));
    return res;
}

int id(int x, int y) {
    return (x - 1) * m + y;
}

void link(int x, int y) {
    graph[x].push_back(y);
    ++in[y];
}

bool invaild(int x, int y) {
    return x < 1 || x > n || y < 1 || y > m;
}

int check() {
    queue<pair<int, int>> q;
    for (int i = 1; i <= m; ++i) {
        q.push({1, i});
        vis[1][i] = true;
    }
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int nx = x + dir[i][0], ny = y + dir[i][1];
            if (invaild(nx, ny) || vis[nx][ny] || height[x][y] <= height[nx][ny])
                continue;
            vis[nx][ny] = true;
            q.push({nx, ny});
        }
    }
    int cnt = 0;
    for (int i = 1; i <= m; ++i)
        if (vis[n][i] == false)
            ++cnt;
    return cnt;
}

void build() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int k = 0; k < 4; ++k) {
                int ni = i + dir[k][0], nj = j + dir[k][1];
                if (invaild(ni, nj) || height[i][j] >= height[ni][nj])
                    continue;
                link(id(i, j), id(ni, nj));
            }
        }
    }
}

void spread() {
    queue<int> q;
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (in[id(i, j)] == 0) {
                q.push(id(i, j));
            }
        }
    }
    for (int i = 1; i <= m; ++i) {
        if (in[id(n, i)] == 0) {
            q.push(id(n, i));
        }
        range[id(n, i)] = {i, i};
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int y : graph[x]) {
            range[y].update(range[x]);
            --in[y];
            if (in[y] == 0)
                q.push(y);
        }
    }
}

void solve() {
    memset(f, 0x3f, sizeof(f));
    for (int i = 0; i <= n; ++i)
        f[i][0] = 0;
    build(1, 1, m + 1, f[0]);
    for (int i = 1; i <= m; ++i) {
        int pre = 0x3f3f3f3f;
        if (range[i].r > 0)
            pre = query(1, 1, m + 1, range[i].l, range[i].r) + 1;
        for (int j = 1; j <= range[i].r; ++j)
            f[i][j] = min(pre, f[i - 1][j]);
        for (int j = range[i].r + 1; j <= m; ++j)
            f[i][j] = min(f[i][j], f[i - 1][j]);
        build(1, 1, m + 1, f[i]);
    }
    cout << 1 << endl;
    cout << f[m][m] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> height[i][j];
    int cnt = check();
    if (cnt != 0) {
        cout << 0 << endl;
        cout << cnt << endl;
        return 0;
    }
    build();
    spread();
    solve();
    // for (int i = 1; i <= n; ++i)
    //     for (int j = 1; j <= m; ++j)
    //         cout << "(" << i << ", " << j << ") : " << range[id(i, j)].l << " " << range[id(i, j)].r << endl;
    // for (int i = 0; i <= m; ++i) {
    //     cout << i << " : ";
    //     for (int j = 0; j <= m; ++j) {
    //         cout << f[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    return 0;
}