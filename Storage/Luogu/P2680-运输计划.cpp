#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

constexpr int maxn = 300000 + 10;

struct Path {
    int start, end;
    int dis;
};

int n, m;
vector<pair<int, int>> tree[maxn];
int dep[maxn], step[maxn][20], cnt[maxn];
int dis[maxn], ans, mx, mid, now;
Path paths[maxn];

void link(int x, int y, int t) {
    tree[x].push_back({y, t});
    tree[y].push_back({x, t});
}

void preprocess(int x, int fa) {
    for (int i = 1; i <= 19; ++i)
        step[x][i] = step[step[x][i - 1]][i - 1];

    for (auto [y, t] : tree[x]) {
        if (y == fa)
            continue;

        dep[y] = dep[x] + 1;
        step[y][0] = x;
        dis[y] = dis[x] + t;
        preprocess(y, x);
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);

    for (int i = 19; i >= 0; --i)
        if (dep[step[x][i]] >= dep[y])
            x = step[x][i];

    if (x == y)
        return x;

    for (int i = 19; i >= 0; --i) {
        if (step[x][i] != step[y][i]) {
            x = step[x][i];
            y = step[y][i];
        }
    }

    return step[x][0];
}

int distance(int x, int y) {
    int l = lca(x, y);
    return dis[x] + dis[y] - 2 * dis[l];
}

void add(int x, int y) {
    int l = lca(x, y);
    cnt[x] += 1;
    cnt[y] += 1;
    cnt[l] -= 2;
}

bool check(int x, int fa) {
    for (auto [y, t] : tree[x]) {
        if (y == fa)
            continue;

        if (check(y, x))
            return true;

        if (cnt[y] == now && mx - t <= mid)
            return true;

        cnt[x] += cnt[y];
    }

    return false;
}

bool check() {
    mx = 0;
    now = 0;

    for (int i = 1; i <= n; ++i)
        cnt[i] = 0;

    for (int i = 1; i <= m; ++i) {
        auto [st, ed, d] = paths[i];

        if (d > mid) {
            add(st, ed);
            mx = max(mx, d);
            ++now;
        }
    }

    return check(1, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i < n; ++i) {
        int x, y;
        int t;
        cin >> x >> y >> t;
        link(x, y, t);
    }

    preprocess(1, 0);

    for (int i = 1; i <= m; ++i) {
        auto &[st, ed, d] = paths[i];
        cin >> st >> ed;
        d = distance(st, ed);
    }

    int l = 0, r = 0x3f3f3f3f;

    while (l <= r) {
        mid = (l + r) / 2;

        if (check()) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    cout << ans << endl;
    return 0;
}