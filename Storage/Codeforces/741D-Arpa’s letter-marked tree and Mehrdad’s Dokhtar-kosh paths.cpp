#include <iostream>
#include <vector>
using namespace std;

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();

    for (; c < '0' || '9' < c; c = getchar())
        if (c == '-')
            s = -1;

    for (; '0' <= c && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + c - '0';

    return x * s;
}

template <typename T> void write(T x, char sep = '\n') {
    if (x == 0) {
        putchar('0');
        putchar(sep);
        return;
    }

    static int st[21];
    int top = 0;

    while (x) {
        st[++top] = x % 10;
        x /= 10;
    }

    while (top)
        putchar(st[top--] + '0');

    putchar(sep);
}

constexpr int maxn = 5e5 + 10;

int n;
vector<pair<int, int>> tree[maxn];
int timer, dfn[maxn], rev[maxn], sze[maxn], dep[maxn], son[maxn], dis[maxn];
int mx[1 << 22], ans[maxn];

void link(int x, int y, int c) {
    tree[x].push_back({y, c});
    tree[y].push_back({x, c});
}

void preprocess(int x, int fa) {
    dfn[x] = ++timer;
    rev[timer] = x;
    sze[x] = 1;
    dep[x] = dep[fa] + 1;

    for (auto [y, c] : tree[x]) {
        if (y == fa)
            continue;

        dis[y] = (dis[x] ^ (1 << c));
        preprocess(y, x);
        sze[x] += sze[y];

        if (sze[son[x]] < sze[y])
            son[x] = y;
    }
}

void calc(int rt, int x) {
    for (int i = 0; i < 22; ++i) {
        int o = (dis[x] ^ (1 << i));
        
        if (mx[o])
            ans[rt] = max(ans[rt], dep[x] + mx[o] - 2 * dep[rt]);
    }

    if (mx[dis[x]])
        ans[rt] = max(ans[rt], dep[x] + mx[dis[x]] - 2 * dep[rt]);
}

void solve(int x, int fa, bool keep) {
    for (auto [y, l] : tree[x]) {
        if (y == fa || y == son[x])
            continue;

        solve(y, x, false);
        ans[x] = max(ans[x], ans[y]);
    }

    if (son[x]) {
        solve(son[x], x, true);
        ans[x] = max(ans[x], ans[son[x]]);
    }

    calc(x, x);
    mx[dis[x]] = max(mx[dis[x]], dep[x]);

    for (auto [y, l] : tree[x]) {
        if (y == fa || y == son[x])
            continue;

        for (int i = dfn[y]; i <= dfn[y] + sze[y] - 1; ++i)
            calc(x, rev[i]);

        for (int i = dfn[y]; i <= dfn[y] + sze[y] - 1; ++i)
            mx[dis[rev[i]]] = max(mx[dis[rev[i]]], dep[rev[i]]);
    }

    if (!keep)
        for (int i = dfn[x]; i <= dfn[x] + sze[x] - 1; ++i)
            mx[dis[rev[i]]] = 0;
}


int main() {
    n = read();

    for (int i = 2; i <= n; ++i) {
        int f = read();
        char c = getchar();

        while (c < 'a' || c > 'v')
            c = getchar();

        link(i, f, c - 'a');
    }

    preprocess(1, 0);
    solve(1, 0, true);

    for (int i = 1; i <= n; ++i)
        write(ans[i], ' ');
    
    return 0;
}