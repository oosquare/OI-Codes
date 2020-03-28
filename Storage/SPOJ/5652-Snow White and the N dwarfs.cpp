#include <bits/stdc++.h>
using namespace std;

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T = int>
T read() {
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

struct node {
    int sum, l, r;
};

constexpr int maxn = 300000 + 10;
node tree[(maxn << 5) + 5];
int uuid, root[maxn];
int n, c, m, len;

void build(int &x, int l, int r) {
    x = ++uuid;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(tree[x].l, l, mid);
    build(tree[x].r, mid + 1, r);
}

void insert(int &x, int y, int l, int r, int v) {
    tree[x = ++uuid] = tree[y];
    ++tree[x].sum;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (v <= mid)
        insert(tree[x].l, tree[y].l, l, mid, v);
    else
        insert(tree[x].r, tree[y].r, mid + 1, r, v);
}

int query(int x, int y, int l, int r, int k) {
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    if (tree[tree[y].l].sum - tree[tree[x].l].sum > k)  
        return query(tree[x].l, tree[y].l, l, mid, k);
    if (tree[tree[y].r].sum - tree[tree[x].r].sum > k)
        return query(tree[x].r, tree[y].r, mid + 1, r, k);
    return 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    n = read(), c = read();
    build(root[0], 1, c);
    for (int i = 1; i <= n; ++i)
        insert(root[i], root[i - 1], 1, c, read());
    m = read();
    while (m--) {
        int x = read(), y = read();
        int ans = query(root[x - 1], root[y], 1, c, (y - x + 1) >> 1);
        if (ans)
            printf("yes %d\n", ans);
        else
            printf("no\n");
    }
    return 0;
}