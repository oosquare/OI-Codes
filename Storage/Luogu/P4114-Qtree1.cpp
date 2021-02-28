#include <bits/stdc++.h>
using namespace std;

namespace IO {
    
template <typename T = int> T read() {
    T x = 0, s = 1;
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

template <typename T = int> void writeln(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar('\n');
}

template <typename T = int> void writesp(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar(' ');
}

template <typename T = int> void write(T x, char blank[]) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar('\n');
    for (int i = 0; blank[i] != '\0'; ++i)
        putchar(blank[i]);
}

} // namespace IO

constexpr int maxn = 100000 + 10;

struct edge {
    int to, next, weight;
};

edge tree[maxn * 2];
int head[maxn], uuid;
int maxv[maxn * 4];
int sze[maxn], son[maxn], dep[maxn], father[maxn];
int dfn[maxn], rev[maxn], top[maxn], timer;
int ft[maxn][2];
int val[maxn];
int n;

void link(int x, int y, int w) {
    tree[++uuid] = {y, head[x], w};
    head[x] = uuid;
    ft[uuid][0] = x;
    ft[uuid][1] = y;
    tree[++uuid] = {x, head[y], w};
    head[y] = uuid;
    ft[uuid][0] = y;
    ft[uuid][1] = x;
}

void pushup(int x) {
    maxv[x] = max(maxv[x * 2], maxv[x * 2 + 1]);
}

void modify(int x, int l, int r, int p, int v) {
    if (l == r && r == p) {
        maxv[x] = v;
        return;
    }
    int mid = (l + r) / 2;
    if (p <= mid)
        modify(x * 2, l, mid, p, v);
    else
        modify(x * 2 + 1, mid + 1, r, p, v);
    pushup(x);
}

int query(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return maxv[x];
    int mid = (l + r) / 2;
    int res = 0;
    if (ql <= mid)
        res = max(res, query(x * 2, l, mid, ql, qr));
    if (mid < qr)
        res = max(res, query(x * 2 + 1, mid + 1, r, ql, qr));
    return res;
}

void build(int x, int l, int r) {
    if (l == r) {
        maxv[x] = val[rev[l]];
        return;
    }
    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
    pushup(x);
}

void DFS1(int x, int fa) {
    sze[x] = 1;
    dep[x] = dep[fa] + 1;
    father[x] = fa;
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next) {
        if (y == fa)
            continue;
        DFS1(y, x);
        val[y] = tree[i].weight;
        sze[x] += sze[y];
        if (sze[y] > sze[son[x]])
            son[x] = y;
    }
}

void DFS2(int x) {
    if (son[x]) {
        top[son[x]] = top[x];
        dfn[son[x]] = ++timer;
        rev[timer] = son[x];
        DFS2(son[x]);
    }
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next) {
        if (y == father[x] || y == son[x])
            continue;
        top[y] = y;
        dfn[y] = ++timer;
        rev[timer] = y;
        DFS2(y);
    }
}

void treeModify() {
    int i = IO::read() * 2, ti = IO::read();
    int x = ft[i][0], y = ft[i][1];
    if (father[y] == x)
        swap(x, y);
    modify(1, 1, n, dfn[x], ti);
}

void treeQuery() {
    int x = IO::read(), y = IO::read();
    if (x == y) {
        IO::writeln(0);
        return;
    }
    int res = 0;
    for (int fx = top[x], fy = top[y]; fx != fy; x = father[fx], fx = top[x]) {
        if (dep[fx] < dep[fy]) {
            swap(x, y);
            swap(fx, fy);
        }
        res = max(res, query(1, 1, n, dfn[fx], dfn[x]));
    }
    if (dep[x] > dep[y])
        swap(x, y);
    if (dfn[x] < dfn[y])
        res = max(res, query(1, 1, n, dfn[x] + 1, dfn[y]));
    IO::writeln(res);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    using namespace IO;
    int t = 1;
    while (t--) {
        n = read();
        memset(head, 0, sizeof(head));
        memset(sze, 0, sizeof(sze));
        memset(son, 0, sizeof(son));
        uuid = 0;
        dep[1] = 0;
        timer = 0;
        top[1] = 1;
        for (int i = 1; i < n; ++i) {
            int x = read(), y = read(), z = read();
            link(x, y, z);
        }
        DFS1(1, 0);
        DFS2(1);
        build(1, 1, n);
        while (1) {
            char str[10];
            scanf("%s", str);
            if (str[0] == 'C')
                treeModify();
            else if (str[0] == 'Q')
                treeQuery();
            else
                break;
        }
    }
    return 0;
}