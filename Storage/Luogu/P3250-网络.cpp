#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();

    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            s = -1;

    for (; '0' <= c && c <= '9'; c = getchar())
        x = x * 10 + c - '0';

    return x * s;
}

template <typename T> void write(T x, char sep = '\n') {
    if (x == 0) {
        putchar(x);
        putchar(sep);
        return;
    }

    static int st[50];
    int top = 0;

    if (x < 0) {
        putchar('-');
        x = -x;
    }

    while (x) {
        st[++top] = x % 10;
        x /= 10;
    }

    while (top)
        putchar(st[top--] + '0');

    putchar(sep);
}

constexpr int maxn = 2e5 + 10;

struct Query {
    int type, a, b, v, d, id;
};

int n, m;
vector<int> tree[maxn];
int dep[maxn], sze[maxn], son[maxn], fa[maxn], top[maxn];
int timer, dfn[maxn], rev[maxn];
int arr[maxn];
Query qs[maxn], tmp1[maxn], tmp2[maxn];
int qsc, mx, ans[maxn];

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void dfs1(int x) {
    sze[x] = 1;
    dep[x] = dep[fa[x]] + 1;

    for (int y : tree[x]) {
        if (y == fa[x])
            continue;

        fa[y] = x;
        dfs1(y);
        sze[x] += sze[y];

        if (sze[son[x]] < sze[y])
            son[x] = y;
    }
}

void dfs2(int x, int tp) {
    dfn[x] = ++timer;
    rev[timer] = x;
    top[x] = tp;

    if (son[x])
        dfs2(son[x], top[x]);

    for (int y : tree[x]) {
        if (y == fa[x] || y == son[x])
            continue;

        dfs2(y, y);
    }
}

inline int lowbit(int x) {
    return x & (-x);
}

void add(int p, int v) {
    for (; p <= n; p += lowbit(p))
        arr[p] += v;
}

int query(int p) {
    int res = 0;

    for (; p; p -= lowbit(p))
        res += arr[p];

    return res;
}

int lca(int u, int v) {
    int x = top[u], y = top[v];

    while (x != y) {
        if (dep[x] > dep[y])
            x = top[u = fa[x]];
        else
            y = top[v = fa[y]];
    }

    return dep[u] < dep[v] ? u : v;
}

void add(int x, int y, int v) {
    int l = lca(x, y);
    add(dfn[x], v);
    add(dfn[y], v);
    add(dfn[l], -v);

    if (fa[l])
        add(dfn[fa[l]], -v);
}

void solve(int l, int r, int al, int ar) {
    if (al == ar) {
        for (int i = l; i <= r; ++i)
            if (qs[i].type == 2)
                ans[qs[i].id] = al;

        return;
    }
    
    int mid = (al + ar) >> 1;
    int it1 = 0, it2 = 0, cnt = 0;

    for (int i = l; i <= r; ++i) {
        if (qs[i].type == 1) {
            if (qs[i].v > mid) {
                add(qs[i].a, qs[i].b, qs[i].d);
                cnt += qs[i].d;
                tmp2[++it2] = qs[i];
            } else {
                tmp1[++it1] = qs[i];
            }
        } else {
            int c = query(dfn[qs[i].a] + sze[qs[i].a] - 1) - query(dfn[qs[i].a] - 1);

            if (c < cnt) {
                tmp2[++it2] = qs[i];
            } else {
                tmp1[++it1] = qs[i];
            }
        }
    }

    for (int i = l; i <= r; ++i)
        if (qs[i].type == 1 && qs[i].v > mid)
            add(qs[i].a, qs[i].b, -qs[i].d);

    for (int i = l; i <= l + it1 - 1; ++i)
        qs[i] = tmp1[i - l + 1];

    for (int i = l + it1; i <= r; ++i)
        qs[i] = tmp2[i - l - it1 + 1];

    if (it1) 
        solve(l, l + it1 - 1, al, mid);

    if (it2)
        solve(l + it1, r, mid + 1, ar);
}

int main() {
    n = read(), m = read();

    for (int i = 1; i < n; ++i) {
        int x = read(), y = read();
        link(x, y);
    }

    for (int i = 1; i <= m; ++i) {
        auto &[type, a, b, v, d, id] = qs[i];
        type = read();

        if (type == 0) {
            a = read(), b = read(), v = read();
            mx = max(mx, v);
            type = 1;
            d = 1;
        } else if (type == 1) {
            int tmp = read();
            a = qs[tmp].a, b = qs[tmp].b, v = qs[tmp].v;
            d = -1;
        } else {
            a = read();
            id = ++qsc;
        }
    }

    dfs1(1);
    dfs2(1, 1);
    solve(1, m, -1, mx);

    for (int i = 1; i <= qsc; ++i)
        write(ans[i]);

    return 0;
}