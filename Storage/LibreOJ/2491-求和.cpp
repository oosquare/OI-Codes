#include <bits/stdc++.h>
using namespace std;

struct node {
    int to, next;
};

constexpr int maxn = 300000 + 5;
constexpr int maxk = 50 + 1;
constexpr int mod = 998244353;

node tree[maxn << 2];
int uuid, n, m, head[maxn], dep[maxn], f[maxn][20];
int sum[maxn][maxk];
int tmp[maxn][maxk];

inline int read() {
    int x = 0, s = 1;
    char c = getchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * s;
}

inline int power(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1)
            res = 1LL * res * a % mod;
        a = 1LL * a * a % mod;
        b >>= 1;
    }
    return res % mod;
}

void preprocess(int x, int fa) {
    dep[x] = dep[fa] + 1;
    for (int i = 1; i < 20; ++i)
        f[x][i] = f[f[x][i - 1]][i - 1];
    for (int i = 1; i <= 50; ++i) {
        if (!tmp[dep[x]][i]) {
            sum[x][i] = tmp[dep[x]][i] = power(dep[x], i);
            sum[x][i] = (1LL * sum[x][i] + sum[fa][i]) % mod;
        } else {
            sum[x][i] = (1LL * tmp[dep[x]][i] + sum[fa][i]) % mod;
        }
    }
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next) {
        if (y == fa)
            continue;
        f[y][0] = x;
        preprocess(y, x);
    }
}

inline void myswap(int &x, int &y) { x ^= y ^= x ^= y; }

int LCA(int x, int y) {
    if (dep[x] < dep[y])
        myswap(x, y);
    for (int i = 19; i >= 0; --i) {
        if (dep[f[x][i]] >= dep[y])
            x = f[x][i];
        if (x == y)
            return x;
    }
    for (int i = 19; i >= 0; --i) {
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}

inline int query(int x, int y, int k) {
    int lca = LCA(x, y);
    return (1LL * sum[x][k] + sum[y][k] - sum[lca][k] - sum[f[lca][0]][k] +
            2 * mod) %
           mod;
}

inline void link(int x, int y) { tree[++uuid] = {y, head[x]}, head[x] = uuid; }

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    n = read();
    for (int i = 1; i < n; ++i) {
        int x = read(), y = read();
        link(x, y);
        link(y, x);
    }
    dep[0] = -1;
    preprocess(1, 0);
    m = read();
    while (m--) {
        int x = read(), y = read(), z = read();
        printf("%d\n", query(x, y, z));
    }
    return 0;
}