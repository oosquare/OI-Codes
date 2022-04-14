#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 200000 + 10;

typedef long long ll;

struct Node {
    long long sum, base, add;
};

struct Edge {
    int to, next;
    ll weight;
};

Edge tree[maxn * 2];
int uuid, head[maxn];
int sze[maxn], fa[maxn], son[maxn], dep[maxn];
int timer, dfn[maxn], rev[maxn], top[maxn];
ll tmp[maxn], sum[maxn], sumdep, cnt;
Node seg[maxn * 4];
int n, m;

void pushup(int x) {
    seg[x].sum = seg[x * 2].sum + seg[x * 2 + 1].sum;
}

void update(int x, ll v) {
    seg[x].sum += seg[x].base * v;
    seg[x].add += v;
}

void pushdown(int x) {
    if (seg[x].add == 0) return;
    update(x * 2, seg[x].add);
    update(x * 2 + 1, seg[x].add);
    seg[x].add = 0;
}

void build(int x, int l, int r) {
    if (l == r) {
        seg[x].base = tmp[rev[l]];
        return;
    }
    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
    pushup(x);
    seg[x].base = seg[x * 2].base + seg[x * 2 + 1].base;
}

void modify(int x, int l, int r, int ml, int mr, ll v) {
    if (ml <= l && r <= mr) {
        update(x, v);
        return;
    }
    int mid = (l + r) / 2;
    pushdown(x);
    if (ml <= mid) modify(x * 2, l, mid, ml, mr, v);
    if (mid < mr) modify(x * 2 + 1, mid + 1, r, ml, mr, v);
    pushup(x);
}

ll query(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return seg[x].sum;
    int mid = (l + r) / 2;
    ll res = 0;
    pushdown(x);
    if (ql <= mid) res += query(x * 2, l, mid, ql, qr);
    if (mid < qr) res += query(x * 2 + 1, mid + 1, r, ql, qr);
    return res;
}

void link(int x, int y, ll w) {
    tree[++uuid] = {y, head[x], w};
    head[x] = uuid;
}

void DFS1(int x) {
    dep[x] = dep[fa[x]] + 1;
    sze[x] = 1;
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next) {
        if (y == fa[x]) continue;
        fa[y] = x;
        sum[y] = sum[x] + tree[i].weight;
        tmp[y] = tree[i].weight;
        DFS1(y);
        sze[x] += sze[y];
        if (sze[y] > sze[son[x]]) son[x] = y;
    }
}

void DFS2(int x) {
    dfn[x] = ++timer;
    rev[timer] = x;
    if (son[x]) {
        top[son[x]] = top[x];
        DFS2(son[x]);
    }
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next) {
        if (y == fa[x] || y == son[x]) continue;
        top[y] = y;
        DFS2(y);
    }
}

void init() {
    top[1] = 1;
    DFS1(1);
    DFS2(1);
    build(1, 1, n);
}

void modify(int x) {
    int tx = top[x];
    while (x != 0) {
        modify(1, 1, n, dfn[tx], dfn[x], 1);
        x = fa[tx];
        tx = top[x];
    }
}

ll query(int x) {
    int tx = top[x];
    ll res = 0;
    while (x != 0) {
        res += query(1, 1, n, dfn[tx], dfn[x]);
        x = fa[tx];
        tx = top[x];
    }
    return res;
}

int main() {
    freopen("express.in", "r", stdin);
    freopen("express.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        link(x, y, w);
        link(y, x, w);
    }

    init();
    while (m--) {
        int opt, u;
        cin >> opt >> u;
        if (opt == 1) {
            ++cnt;
            sumdep += sum[u];
            modify(u);
        } else {
            cout << sumdep + cnt * sum[u] - 2 * query(u) << endl;
        }
    }
    return 0;
}
