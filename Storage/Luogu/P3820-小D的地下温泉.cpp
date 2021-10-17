#include <bits/stdc++.h>
using namespace std;

constexpr int maxnm = 1e6 + 10;

int n, m, q, cnt;
char grid[maxnm];
int fa[maxnm * 2], bel[maxnm], sze[maxnm * 2];
constexpr int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool invaild(int x, int y) {
    return x < 1 || x > n || y < 1 || y > m;
}

inline int id(int x, int y) {
    return (x - 1) * m + y;
}

inline pair<int, int> pos(int i) {
    return {i / m, i % m};
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        fa[x] = y;
        sze[y] += sze[x];
    }
}

void bfs(int sx, int sy) {
    queue<pair<int, int>> q;
    vector<int> neighbor;
    bel[id(sx, sy)] = ++cnt;
    sze[cnt] = 1;
    q.push({sx, sy});
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int nx = x + dir[i][0], ny = y + dir[i][1];
            if (invaild(nx, ny) || grid[id(nx, ny)] == '*')
                continue;
            if (bel[id(nx, ny)]) {
                neighbor.push_back(bel[id(nx, ny)]);
                continue;
            }
            bel[id(nx, ny)] = cnt;
            ++sze[cnt];
            q.push({nx, ny});
        }
    }
    for (int x : neighbor)
        merge(x, cnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i < maxnm; ++i)
        fa[i] = i;
    for (int i = 1; i <= n; ++i)
        cin >> (grid + id(i, 1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (grid[id(i, j)] == '.' && bel[id(i, j)] == 0)
                bfs(i, j);
    cin >> q;
    while (q--) {
        int op, w;
        vector<pair<int, int>> p;
        cin >> op >> w;
        for (int i = 1; i <= w; ++i) {
            int x, y;
            cin >> x >> y;
            p.push_back({x, y});
        }
        if (op == 1) {
            int ans = 1, sz = 0;
            for (int i = 0; i < (int)p.size(); ++i) {
                auto [x, y] = p[i];
                if (sz < sze[find(bel[id(x, y)])]) {
                    sz = sze[find(bel[id(x, y)])];
                    ans = i + 1;
                }
            }
            cout << ans << endl;
        } else {
            for (int i = 0; i < (int)p.size(); ++i) {
                auto [x, y] = p[i];
                if (grid[id(x, y)] == '.') {
                    --sze[find(bel[id(x, y)])];
                    bel[id(x, y)] = 0;
                    grid[id(x, y)] = '*';
                } else {
                    grid[id(x, y)] = '.';
                }
            }
            for (int i = 0; i < (int)p.size(); ++i) {
                auto [x, y] = p[i];
                if (grid[id(x, y)] == '.' && bel[id(x, y)] == 0)
                    bfs(x, y);
            }
        }
    }
    return 0;
}