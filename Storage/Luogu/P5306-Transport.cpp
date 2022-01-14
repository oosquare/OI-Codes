#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int maxn = 1e5 + 10;

int n, a[maxn];
vector<pair<int, int>> tree[maxn];
int sze[maxn], sze2[maxn], root, tot;
long long in[maxn], out[maxn];
int icnt, ocnt;
bool vis[maxn];
long long ans;

void link(int x, int y, int w) {
    tree[x].push_back({y, w});
    tree[y].push_back({x, w});
}

void getRoot(int x, int fa) {
    sze[x] = 1;
    sze2[x] = 0;

    for (auto [y, w] : tree[x]) {
        if (y == fa || vis[y])
            continue;

        getRoot(y, x);
        sze[x] += sze[y];
        sze2[x] = max(sze2[x], sze[y]);
    }

    sze2[x] = max(sze2[x], tot - sze[x]);

    if (!root || sze2[x] < sze2[root])
        root = x;
}

void getIn(int x, int fa, long long extra, long long remain) {
    if (extra == 0)
        in[++icnt] = remain;

    for (auto [y, w] : tree[x]) {
        if (y == fa || vis[y])
            continue;

        getIn(y, x, max(extra + w - a[y], 0ll), remain + max(a[y] - extra - w, 0ll));
    }
}

void getOut(int x, int fa, long long extra, long long remain) {
    out[++ocnt] = extra;

    for (auto [y, w] : tree[x]) {
        if (y == fa || vis[y])
            continue;

        getOut(y, x, extra + max(w - remain - a[x], 0ll), max(remain + a[x] - w, 0ll));
    }
}

void calc(int x, int e1, long long r1, long long e2, long long r2, long long k) {
    icnt = ocnt = 0;
    getIn(x, 0, e1, r1);
    getOut(x, 0, e2, r2);

    sort(out + 1, out + 1 + ocnt);

    for (int i = 1; i <= icnt; ++i) {
        int j = upper_bound(out, out + 1 + ocnt, in[i]) - out;

        if (j != 0)
            ans += k * (j - 1);
    }
}

void solve(int x) {
    vis[x] = true;
    calc(x, 0, 0, 0, 0, 1);

    for (auto [y, w] : tree[x]) {
        if (vis[y])
            continue;

        calc(y, max(w - a[y], 0), max(a[y] - w, 0), max(w - a[x], 0), max(a[x] - w, 0), -1);
        root = 0;
        tot = sze[y];
        getRoot(y, 0);
        solve(root);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    for (int i = 1; i < n; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        link(x, y, w);
    }

    tot = n;
    getRoot(1, 0);
    solve(root);
    cout << ans - n << endl;
    return 0;
}