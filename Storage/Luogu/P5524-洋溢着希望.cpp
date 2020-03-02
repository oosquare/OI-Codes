#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct node {
    double sin, cos;
    ll add;
};

constexpr int maxn = 2e5 + 10;
node tree[maxn << 4];
int a[maxn];
int n, m;

inline void pushup(int x) {
    tree[x].sin = tree[x << 1].sin + tree[x << 1 | 1].sin;
    tree[x].cos = tree[x << 1].cos + tree[x << 1 | 1].cos;
}

inline void update(int x, double sinv, double cosv, ll addv) {
    tree[x].add += addv;
    double sint = tree[x].sin, cost = tree[x].cos;
    tree[x].sin = sint * cosv + cost * sinv;
    tree[x].cos = cost * cosv - sint * sinv;
}

inline void pushdown(int x) {
    if (tree[x].add == 0)
        return;
    double sinv = sin(tree[x].add), cosv = cos(tree[x].add);
    update(x << 1, sinv, cosv, tree[x].add);
    update(x << 1 | 1, sinv, cosv, tree[x].add);
    tree[x].add = 0;
}

void modify(int x, int l, int r, int ml, int mr, ll v) {
    if (ml <= l && r <= mr) {
        double sinv = sin(v), cosv = cos(v);
        update(x, sinv, cosv, v);
        return;
    }
    pushdown(x);
    int mid = (l + r) >> 1;
    if (ml <= mid)
        modify(x << 1, l, mid, ml, mr, v);
    if (mid < mr)
        modify(x << 1 | 1, mid + 1, r, ml, mr, v);
    pushup(x);
}

void build(int x, int l, int r) {
    if (l == r) {
        tree[x].sin = sin(a[l]);
        tree[x].cos = cos(a[l]);
        return;
    }
    int mid = (l + r) >> 1;
    build(x << 1, l, mid);
    build(x << 1 | 1, mid + 1, r);
    pushup(x);
}

double query(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return tree[x].sin;
    pushdown(x);
    int mid = (l + r) >> 1;
    double res = 0.0;
    if (ql <= mid)
        res += query(x << 1, l, mid, ql, qr);
    if (mid < qr)
        res += query(x << 1 | 1, mid + 1, r, ql, qr);
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    build(1, 1, n);
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {
        int op, l, r;
        ll v;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1) {
            scanf("%lld", &v);
            modify(1, 1, n, l, r, v);
        } else {
            printf("%.1lf\n", query(1, 1, n, l, r));
        }
    }
    return 0;
}