#include <bits/stdc++.h>
using namespace std;

template <typename T = int>
T read() {
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

struct node {
    int sum;
};

constexpr int maxn = 500000 + 10;
node tree[maxn * 4];
int t, n, arr[maxn];

void pushup(int x) {
    tree[x].sum = tree[x * 2].sum + tree[x * 2 + 1].sum;
}

void build(int x, int l, int r) {
    if (l == r) {
        tree[x].sum = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
    pushup(x);
}

void modify(int x, int l, int r, int p, int v) {
    if (l == r && r == p) {
        tree[x].sum += v;
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
        return tree[x].sum;
    int mid = (l + r) / 2, res = 0;
    if (ql <= mid)
        res += query(x * 2, l, mid, ql, qr);
    if (mid < qr)
        res += query(x * 2 + 1, mid + 1, r, ql, qr);
    return res;
        
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    t = read();
    int cnt = 0;
    while (t--) {
        n = read();
        for (int i = 1; i <= n; ++i)
            arr[i] = read();
        build(1, 1, n);
        char op[10];
        int x, y;
        printf("Case %d:\n", ++cnt);
        while (scanf("%s", op), op[0] != 'E') {
            scanf("%d%d", &x, &y);
            if (op[0] == 'A')
                modify(1, 1, n, x, y);
            if (op[0] == 'S')
                modify(1, 1, n, x, -y);
            if (op[0] == 'Q')
                printf("%d\n", query(1, 1, n, x, y));
        }
    }
    return 0;
}