#include <bits/stdc++.h>
using namespace std;

struct edge {
    int to, nxt, weight;
};

const int maxn = 4e6 + 10;

edge tree[2 * maxn];
int head[maxn], tot;
int f[maxn], sze[maxn], vis[maxn], cnt[maxn], dis[maxn], tmp[maxn];
int root, sum, timer, n, ans, k;

void link(int x, int y, int w) {
    tree[++tot] = (edge){y, head[x], w};
    head[x] = tot;
    tree[++tot] = (edge){x, head[y], w};
    head[y] = tot;
}

void getroot(int x, int fa) {
    sze[x] = 1;
    f[x] = 0;
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].nxt) {
        if (vis[y] || y == fa)
            continue;
        getroot(y, x);
        sze[x] += sze[y];
        f[x] = max(f[x], sze[y]);
    }
    f[x] = max(f[x], sum - sze[x]);
    root = f[x] < f[root] ? x : root;
}

void calc(int x, int fa) {
    if (dis[x] <= k)
        ans = min(ans, tmp[k - dis[x]] + cnt[x]);
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].nxt) {
        if (vis[y] || y == fa)
            continue;
        dis[y] = dis[x] + tree[i].weight;
        cnt[y] = cnt[x] + 1;
        calc(y, x);
    }
}

void update(int x, int fa, int type) {
    if (dis[x] <= k) {
        if (type == 1)
            tmp[dis[x]] = min(tmp[dis[x]], cnt[x]);
        else
            tmp[dis[x]] = 0x3f3f3f3f;
    }
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].nxt) {
        if (vis[y] || y == fa)
            continue;
        update(y, x, type);
    }
}

void solve(int x) {
    vis[x] = 1;
    tmp[0] = 0;
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].nxt) {
        if (vis[y])
            continue;
        cnt[y] = 1;
        dis[y] = tree[i].weight;
        calc(y, 0);
        update(y, 0, 1);
    }
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].nxt)
        if (!vis[y])
            update(y, 0, 0);
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].nxt) {
        if (vis[y])
            continue;
        sum = sze[y];
        root = 0;
        getroot(y, 0);
        solve(root);
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; ++i) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        link(x + 1, y + 1, w);
    }
    ans = 0x3f3f3f3f;
    sum = n;
    f[0] = n;
    for (int i = 1; i <= k; ++i)
        tmp[i] = 0x3f3f3f3f;
    getroot(1, 0);
    solve(root);
    if (ans != 0x3f3f3f3f)
        printf("%d\n", ans);
    else
        printf("-1\n");
    return 0;
}