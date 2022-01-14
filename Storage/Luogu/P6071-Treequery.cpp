#include <iostream>
#include <vector>
using namespace std;

constexpr int maxn = 2e5 + 10;

struct Node {
    int ls, rs;
    int sum;
};

int n, q, ans;
vector<pair<int, int>> tree[maxn];
int timer, sze[maxn], dfn[maxn], rev[maxn], dep[maxn], dis[maxn], step[maxn][19];
Node seg[maxn * 50];
int uuid, root[maxn];

void modify(int &x, int y, int l, int r, int p) {
    x = ++uuid;
    seg[x] = seg[y];
    ++seg[x].sum;

    if (l == r)
        return;

    int mid = (l + r) / 2;

    if (p <= mid)
        modify(seg[x].ls, seg[y].ls, l, mid, p);
    else
        modify(seg[x].rs, seg[y].rs, mid + 1, r, p);
}

int query(int x, int y, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return seg[x].sum - seg[y].sum;

    int mid = (l + r) / 2, res = 0;

    if (ql <= mid)
        res += query(seg[x].ls, seg[y].ls, l, mid, ql, qr);

    if (mid < qr)
        res += query(seg[x].rs, seg[y].rs, mid + 1, r, ql, qr);

    return res;
}

void link(int x, int y, int l) {
    tree[x].push_back({y, l});
    tree[y].push_back({x, l});
}

void dfs(int x, int fa) {
    sze[x] = 1;
    dfn[x] = ++timer;
    rev[timer] = x;
    dep[x] = dep[fa] + 1;

    for (int i = 1; i <= 18; ++i)
        step[x][i] = step[step[x][i - 1]][i - 1];

    for (auto [y, l] : tree[x]) {
        if (y == fa)
            continue;

        dis[y] = dis[x] + l;
        step[y][0] = x;
        dfs(y, x);
        sze[x] += sze[y];
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);

    for (int i = 18; i >= 0; --i)
        if (dep[step[x][i]] >= dep[y])
            x = step[x][i];

    if (x == y)
        return x;

    for (int i = 18; i >= 0; --i) {
        if (step[x][i] != step[y][i]) {
            x = step[x][i];
            y = step[y][i];
        }
    }

    return step[x][0];
}

inline int query(int x, int l, int r) {
    if (x == 0)
        return 0;

    return query(root[dfn[x] + sze[x] - 1], root[dfn[x] - 1], 1, n, l, r);
}

int solve(int p, int l, int r) {
    int lc = lca(p, l), x = p, res = 0;

    if (x != lc) {
        for (int i = 18; i >= 0; --i)
            if (dep[step[x][i]] > dep[lc] && query(step[x][i], l, r) == 0)
                x = step[x][i];

        if (query(x, l, r) == 0)
            res += dis[p] - dis[step[x][0]];

        if (step[x][0] != lc)
            return res;
    }

    x = l;

    if (x != lc) {
        for (int i = 18; i >= 0; --i)
            if (dep[step[x][i]] >= dep[lc] && query(step[x][i], l, r) != r - l + 1)
                x = step[x][i];

        if (x != lc && query(x, l, r) != r - l + 1)
            x = step[x][0];

        res += dis[x] - dis[lc];
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;

    for (int i = 1; i < n; ++i) {
        int x, y, l;
        cin >> x >> y >> l;
        link(x, y, l);
    }

    dfs(1, 0);

    for (int i = 1; i <= n; ++i)
        modify(root[i], root[i - 1], 1, n, rev[i]);

    for (int i = 1; i <= q; ++i) {
        int x, l, r;
        cin >> x >> l >> r;
        x ^= ans;
        l ^= ans;
        r ^= ans;
        ans = (l <= x && x <= r ? 0 : solve(x, l, r));
        cout << ans << endl;
    }

    return 0;
}