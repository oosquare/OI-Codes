#include <bits/stdc++.h>
using namespace std;

struct node {
    double max;
    int len;
};

constexpr int maxn = 100000+10;
node tree[maxn << 2];
double s[maxn];
int n, m;

inline void pushup1(int x) {
    tree[x].max = max(tree[x << 1].max, tree[x << 1 | 1].max);
}

int pushup2(double mx, int x, int l, int r) {
    if (tree[x].max <= mx)
        return 0;
    if (s[l] > mx)
        return tree[x].len;
    if (l == r)
        return s[l] > mx;
    int mid = (l + r) >> 1;
    if (tree[x << 1].max <= mx)
        return pushup2(mx, x << 1 | 1, mid + 1, r);
    else
        return pushup2(mx, x << 1, l, mid) + tree[x].len - tree[x << 1].len;
}

inline void pushup(int x, int l, int r) {
    pushup1(x);
    int mid = (l + r) >> 1;
    tree[x].len =
        tree[x << 1].len + pushup2(tree[x << 1].max, x << 1 | 1, mid + 1, r);
}

void modify(int x, int l, int r, int p, double v) {
    if (l == r && r == p) {
        tree[x].max = v;
        tree[x].len = 1;
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid)
        modify(x << 1, l, mid, p, v);
    else
        modify(x << 1 | 1, mid + 1, r, p, v);
    pushup(x, l, r);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        s[x] = 1.0 * y / x;
        modify(1, 1, n, x, s[x]);
        printf("%d\n", tree[1].len);
    }
    return 0;
}