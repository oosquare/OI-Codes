#include <iostream>
#include <vector>
using namespace std;

constexpr int maxn = 300000 + 10;

int n, q;
vector<int> tree[maxn];
int timer, sze[maxn], dep[maxn], son[maxn], dfn[maxn], rev[maxn];
long long arr[maxn], ans[maxn];
vector<pair<int, int>> qs[maxn];

inline int lowbit(int x) {
    return x & (-x);
}

void add(int p, int v) {
    for (; p <= n; p += lowbit(p))
        arr[p] += v;
}

long long query(int p) {
    p = min(p, n);
    long long res = 0;

    for (; p; p -= lowbit(p))
        res += arr[p];

    return res;
}

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void preprocess(int x, int fa) {
    sze[x] = 1;
    dep[x] = dep[fa] + 1;
    dfn[x] = ++timer;
    rev[timer] = x;

    for (int y : tree[x]) {
        if (y == fa)
            continue;

        preprocess(y, x);
        sze[x] += sze[y];
        son[x] = (sze[son[x]] < sze[y] ? y : son[x]);
    }
}

void solve(int x, int fa, bool keep) {
    for (int y : tree[x]) {
        if (y == fa || y == son[x])
            continue;

        solve(y, x, false);
    }
    if (son[x])
        solve(son[x], x, true);

    add(dep[x], sze[x] - 1);

    for (int y : tree[x]) {
        if (y == fa || y == son[x])
            continue;

        for (int i = dfn[y]; i < dfn[y] + sze[y]; ++i) 
            add(dep[rev[i]], sze[rev[i]] - 1);
    }

    for (auto [k, id] : qs[x])
        ans[id] = query(dep[x] + k) - query(dep[x]) + 1ll * (sze[x] - 1) * min(k, dep[x] - 1);

    if (!keep)
        for (int i = dfn[x]; i < dfn[x] + sze[x]; ++i)
            add(dep[rev[i]], 1 - sze[rev[i]]);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
    }

    for (int i = 1; i <= q; ++i) {
        int p, k;
        cin >> p >> k;
        qs[p].push_back({k, i});
    }

    preprocess(1, 0);
    solve(1, 0, true);

    for (int i = 1; i <= q; ++i)
        cout << ans[i] << endl;

    return 0;
}