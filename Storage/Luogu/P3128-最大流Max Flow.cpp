#include <bits/stdc++.h>
using namespace std;

struct edge {
    int to, next;
};

constexpr int maxn = 500000 + 10;
edge tree[maxn << 2];
int total, head[maxn << 2];
int dep[maxn], f[maxn][30];
int delta[maxn];
int n, k, ans;

void link(int x, int y) {
    tree[++total] = (edge){y, head[x]};
    head[x] = total;
    tree[++total] = (edge){x, head[y]};
    head[y] = total;
}

void DFS(int x, int fa) {
    dep[x] = dep[fa] + 1;
    for (int i = 1; (1 << i) <= dep[x]; ++i)
        f[x][i] = f[f[x][i - 1]][i - 1];
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next) {
        if (y == fa)
            continue;
        f[y][0] = x;
        DFS(y, x);
    }
}

int LCA(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 20; i >= 0; --i) {
        if (dep[f[x][i]] >= dep[y])
            x = f[x][i];
        if (x == y)
            return x;
    }
    for (int i = 20; i >= 0; --i) {
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}

int statistics(int x, int fa) {
    int val = delta[x];
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next) {
        if (y == fa)
            continue;
        val += statistics(y, x);
    }
    if (val > ans)
        ans = val;
    return val;
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        link(x, y);
    }
    DFS(1, 0);
    for (int i = 1; i <= k; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        int lca = LCA(x, y);
        ++delta[x];
        ++delta[y];
        --delta[lca];
        --delta[f[lca][0]];
    }
    statistics(1, 0);
    printf("%d\n", ans);
    return 0;
}