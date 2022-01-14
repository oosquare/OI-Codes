#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int maxn = 1e5 + 10;

int n, l, w;
vector<pair<int, int>> tree[maxn];
int arr[maxn];
int sze[maxn], sze2[maxn];
bool vis[maxn];
pair<int, int> dis[maxn];
int root, tot, cnt;
long long ans;

inline int lowbit(int x) {
    return x & (-x);
}

void add(int p, int v) {
    ++p;

    for (; p <= n + 1; p += lowbit(p))
        arr[p] += v;
}

int query(int p) {
    int res = 0;
    ++p;

    for (; p; p -= lowbit(p))
        res += arr[p];

    return res;
}

void clear(int p) {
    ++p;

    for (; p <= n + 1; p += lowbit(p))
        if (arr[p])
            arr[p] = 0;
        else
            return;
}

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

void getDistance(int x, int fa, int l0, int w0) {
    dis[++cnt] = {w0, l0};

    for (auto [y, w] : tree[x]) {
        if (y == fa || vis[y])
            continue;

        getDistance(y, x, l0 + 1, w0 + w);
    }
}

void calc(int x, int l0, int w0, int d) {
    cnt = 0;
    getDistance(x, 0, l0, w0);
    sort(dis + 1, dis + 1 + cnt);

    for (int i = 1; i <= cnt; ++i)
        add(dis[i].second, 1);

    for (int i = 1, j = cnt;; add(dis[i].second, -1), ++i) {
        while (j && dis[i].first + dis[j].first > w) {
            add(dis[j].second, -1);
            --j;
        }

        if (j < i)
            break;

        if (l - dis[i].second >= 0)
            ans += d * query(l - dis[i].second);
    }

    for (int i = 1; i <= cnt; ++i)
        clear(dis[i].second);
}

void solve(int x) {
    calc(x, 0, 0, 1);
    vis[x] = true;

    for (auto [y, w] : tree[x]) {
        if (vis[y])
            continue;

        calc(y, 1, w, -1);
        root = 0;
        tot = sze[y];
        getRoot(y, x);
        solve(root);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> l >> w;

    for (int i = 2; i <= n; ++i) {
        int p, w;
        cin >> p >> w;
        link(i, p, w);
    }

    tot = n;
    getRoot(1, 0);
    solve(root);
    cout << ans - n << endl;
    return 0;
}