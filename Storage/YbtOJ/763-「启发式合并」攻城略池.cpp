#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

namespace IO {

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = mygetchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = mygetchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = mygetchar();
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

typedef long long ll;

constexpr int maxn = 1e6 + 10;

struct node {
    ll key, sum, add;
    int l, r, size;
    unsigned priority;
};

struct edge {
    int to, next, weight;
};

node tree[maxn * 10];
int uuid, root[maxn];
edge graph[maxn];
int uuid2, head[maxn];
unsigned seed;
int f[maxn], d[maxn];
int n, ans;

inline int &ls(int x) {
    return tree[x].l;
}

inline int &rs(int x) {
    return tree[x].r;
}

inline unsigned myrandom() {
    return seed = (1LL * (seed + 3) * 53417 + 41212);
}

inline void pushup(int x) {
    tree[x].size = tree[ls(x)].size + tree[rs(x)].size + 1;
    tree[x].sum = tree[ls(x)].sum + tree[rs(x)].sum + tree[x].key;
}

inline void update(int x, ll v) {
    tree[x].key += v;
    tree[x].add += v;
    tree[x].sum += v * tree[x].size;
}

inline void pushdown(int x) {
    if (!tree[x].add)
        return;
    if (ls(x)) 
        update(ls(x), tree[x].add);
    if (rs(x))
        update(rs(x), tree[x].add);
    tree[x].add = 0;
}

void splitv(int root, int val, int &x, int &y) {
    if (!root) {
        x = y = 0;
        return;
    }
    pushdown(root);
    if (tree[root].key <= val) {
        x = root;
        splitv(rs(x), val, rs(x), y);
        pushup(x);
    } else {
        y = root;
        splitv(ls(y), val, x, ls(y));
        pushup(y);
    }
}

void splits(int root, int sze, int &x, int &y) {
    if (!root) {
        x = y = 0;
        return;
    }
    pushdown(root);
    if (tree[ls(root)].size + 1 <= sze) {
        x = root;
        splits(rs(x), sze - tree[ls(root)].size - 1, rs(x), y);
        pushup(x);
    } else {
        y = root;
        splits(ls(y), sze, x, ls(y));
        pushup(y);
    }
}

int merge(int x, int y) {
    if (!x || !y)
        return x + y;
    if (tree[x].priority > tree[y].priority) {
        pushdown(x);
        rs(x) = merge(rs(x), y);
        pushup(x);
        return x;
    } else { 
        pushdown(y);
        ls(y) = merge(x, ls(y));
        pushup(y);
        return y;
    }
}

int merge2(int x, int y) {
    if (!x || !y)
        return x + y;
    pushdown(x);
    pushdown(y);
    if (tree[x].priority <= tree[y].priority)
        swap(x, y);
    int rt1, rt2;
    splitv(y, tree[x].key, rt1, rt2);
    ls(x) = merge2(ls(x), rt1);
    rs(x) = merge2(rs(x), rt2);
    return x;
}

int create(ll v) {
    tree[++uuid] = {v, v, 0, 0, 0, 1, myrandom()};
    return uuid;
}

void insert(int &x, int v) {
    int rt1, rt2;
    splitv(x, v, rt1, rt2);
    x = merge(merge(rt1, create(v)), rt2);
}

void link(int x, int y, int w) {
    graph[++uuid] = {y, head[x], w};
    head[x] = uuid;
}

void DFS(int x, int fa) {
    for (register int i = head[x], y, w; y = graph[i].to, w = graph[i].weight, i; i = graph[i].next) {
        if (y == fa)
            continue;
        DFS(y, x);
        update(root[y], w);
        root[x] = merge2(root[x], root[y]);
        insert(root[x], f[y] + w);
    }
    if (d[x] == 0)
        return;
    int l = 1, r = 0x3f3f3f3f, res = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        int rt1, rt2;
        splitv(root[x], mid - 1, rt1, rt2);
        if (1LL * tree[rt1].size * mid - tree[rt1].sum >= d[x]) {
            r = mid - 1;
            res = mid;
        } else {
            l = mid + 1;
        }
        root[x] = merge(rt1, rt2);
    }
    f[x] = res;
    ans = max(ans, res);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("conquer.in", "r", stdin);
    freopen("conquer.out", "w", stdout);
#endif
    using namespace IO;
    n = read();
    for (register int i = 1; i <= n; ++i)
        d[i] = read();
    for (register int i = 1; i < n; ++i) {
        int x = read(), y = read(), l = read();
        link(x, y, l);
        link(y, x, l);
    }
    DFS(1, 0);
    writeln(ans);
    return 0;
}
