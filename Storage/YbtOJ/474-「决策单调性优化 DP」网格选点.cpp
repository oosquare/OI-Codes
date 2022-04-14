#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;

constexpr int MAXN = 2e5 + 10;
constexpr int MAXT = 2e6 + 10;
constexpr long long INFINITY = 0x3f3f3f3f3f3f3f3f;

struct Point {
    int x, y;

    bool operator<(const Point & rhs) const {
        return x < rhs.x;
    }

    bool contain(const Point &o) const {
        return x > o.x && y > o.y;
    }
};

struct Node {
    vector<int> id;
};

int t, n;
int bitree[MAXT];
Point points[MAXN];
int lis[MAXN], len;
Node tree[MAXN * 4];
vector<int> layer[MAXN];
long long f[MAXN], ans = INFINITY;

inline int lowbit(int x) {
    return x & (-x);
}

void modify(int x, int y) {
    ++x;

    for (; x <= t + 1; x += lowbit(x))
        bitree[x] = max(bitree[x], y);
}

int query(int x) {
    int res = 0;
    ++x;

    for (; x; x -= lowbit(x))
        res = max(res, bitree[x]);

    return res;
}

void getLIS() {
    sort(points + 1, points + 1 + n);

    for (int i = 1; i <= n; ++i) {
        lis[i] = query(points[i].y) + 1;
        modify(points[i].y, lis[i]);
        len = max(len, lis[i]);
    }

    for (int i = 1; i <= n; ++i)
        layer[lis[i]].push_back(i);
}

void assign(int root, int l, int r, int p, int dep) {
    if (points[layer[dep - 1][l]].x > points[p].x || points[layer[dep - 1][r]].y > points[p].y)
        return;

    if (points[p].contain(points[layer[dep - 1][l]]) && points[p].contain(points[layer[dep - 1][r]])) {
        tree[root].id.push_back(p);
        return;
    }

    int mid = (l + r) / 2;
    assign(root * 2, l, mid, p, dep);
    assign(root * 2 + 1, mid + 1, r, p, dep);
}

void calc(int root, int l, int r, int pl, int pr, int dep) {
    if (l > r)
        return;

    int mid = (l + r) / 2, i = tree[root].id[mid];
    long long mi = INFINITY, pos = 0;

    for (int p = pl; p <= pr; ++p) {
        int j = layer[dep - 1][p];
        auto [xj, yj] = points[j];

        if (mi > f[j] + 1ll * (points[i].x - xj) * (points[i].y - yj)) {
            mi = f[j] + 1ll * (points[i].x - xj) * (points[i].y - yj);
            pos = p;
        }
    }

    f[i] = min(f[i], mi);
    calc(root, l, mid - 1, pos, pr, dep);
    calc(root, mid + 1, r, pl, pos, dep);
}

void dfs(int root, int l, int r, int dep) {
    calc(root, 0, tree[root].id.size() - 1, l, r, dep);
    tree[root].id.clear();

    if (l == r)
        return;

    int mid = (l + r) / 2;
    dfs(root * 2, l, mid, dep);
    dfs(root * 2 + 1, mid + 1, r, dep);
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("grid.in", "r", stdin);
    freopen("grid.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> t;

    for (int i = 1; i <= n; ++i) {
        auto & [x, y] = points[i];
        cin >> x >> y;
    }

    points[++n] = { 0, 0 };
    points[++n] = { t, t };

    getLIS();

    for (int i = 1; i <= n; ++i)
        f[i] = (lis[i] == 1 ? 0 : INFINITY);

    for (int i = 2; i <= len; ++i) {
        for (int j : layer[i])
            assign(1, 0, layer[i - 1].size() - 1, j, i);

        dfs(1, 0, layer[i - 1].size() - 1, i);
    }

    for (int i = 1; i <= n; ++i)
        if (lis[i] == len)
            ans = min(ans, f[i]);

    cout << ans << endl;
    return 0;
}
