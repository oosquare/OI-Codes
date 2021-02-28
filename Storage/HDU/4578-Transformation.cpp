#include <bits/stdc++.h>
using namespace std;

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T>
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

typedef long long ll;

struct node {
    ll sum[3], add, mul, assign;    
};

constexpr int maxn = 100000 + 10;
constexpr ll mod = 10007;
constexpr ll nexist = -0x3f3f3f3f3f3f3f3f;
node tree[maxn * 4];
int n, m;

#define ls(x) ((x) * 2)
#define rs(x) ((x) * 2 + 1)

void pushup(int x) {
    for (int i = 0; i < 3; ++i)
        tree[x].sum[i] = (tree[ls(x)].sum[i] + tree[rs(x)].sum[i]) % mod;
}

void updateAdd(int x, int l, int r, ll v) {
    if (tree[x].assign != nexist)
        tree[x].assign = (tree[x].assign + v) % mod;
    tree[x].add = (tree[x].add + v) % mod;
    tree[x].sum[2] = (tree[x].sum[2] + 3 * v * tree[x].sum[1] % mod + 3 * v * v * tree[x].sum[0] % mod + v * v * v * (r - l + 1) % mod) % mod;
    tree[x].sum[1] = (tree[x].sum[1] + 2 * v * tree[x].sum[0] % mod + v * v * (r - l + 1) % mod) % mod;
    tree[x].sum[0] = (tree[x].sum[0] + (r - l + 1) * v % mod) % mod;
}

void updateMul(int x, ll v) {
    if (tree[x].assign != nexist)
        tree[x].assign = tree[x].assign * v % mod;
    tree[x].mul = tree[x].mul * v % mod;
    tree[x].add = tree[x].add * v % mod;
    tree[x].sum[0] = tree[x].sum[0] * v % mod;
    tree[x].sum[1] = tree[x].sum[1] * v * v % mod;
    tree[x].sum[2] = tree[x].sum[2] * v * v * v % mod;
}

void updateAssign(int x, int l, int r, ll v) {
    tree[x].assign = v;
    tree[x].add = 0;
    tree[x].mul = 1;
    tree[x].sum[0] = v * (r - l + 1) % mod;
    tree[x].sum[1] = v * v * (r - l + 1) % mod;
    tree[x].sum[2] = v * v * v * (r - l + 1) % mod;
}

void pushdown(int x, int l, int r) {
    int mid = (l + r) / 2;
    if (tree[x].assign != nexist) {
        updateAssign(ls(x), l, mid, tree[x].assign);
        updateAssign(rs(x), mid + 1, r, tree[x].assign);
        tree[x].assign = nexist;
        tree[x].add = 0;
        tree[x].mul = 1;
    }
    if (tree[x].mul != 1) {
        updateMul(ls(x), tree[x].mul);
        updateMul(rs(x), tree[x].mul);
        tree[x].mul = 1;
    }
    if (tree[x].add) {
        updateAdd(ls(x), l, mid, tree[x].add);
        updateAdd(rs(x), mid + 1, r, tree[x].add);
        tree[x].add = 0;
    }
}

void modifyAdd(int x, int l, int r, int ml, int mr, ll v) {
    if (ml <= l && r <= mr) {
        updateAdd(x, l, r, v);
        return;
    }
    int mid = (l + r) / 2;
    pushdown(x, l, r);
    if (ml <= mid)
        modifyAdd(ls(x), l, mid, ml, mr, v);
    if (mid < mr)
        modifyAdd(rs(x), mid + 1, r, ml, mr, v);
    pushup(x);
}

void modifyMul(int x, int l, int r, int ml, int mr, ll v) {
    if (ml <= l && r <= mr) {
        updateMul(x, v);
        return;
    }
    int mid = (l + r) / 2;
    pushdown(x, l, r);
    if (ml <= mid)
        modifyMul(ls(x), l, mid, ml, mr, v);
    if (mid < mr)
        modifyMul(rs(x), mid + 1, r, ml, mr, v);
    pushup(x);
}

void modifyAssign(int x, int l, int r, int ml, int mr, ll v) {
    if (ml <= l && r <= mr) {
        updateAssign(x, l, r, v);
        return;
    }
    int mid = (l + r) / 2;
    pushdown(x, l, r);
    if (ml <= mid)
        modifyAssign(ls(x), l, mid, ml, mr, v);
    if (mid < mr)
        modifyAssign(rs(x), mid + 1, r, ml, mr, v);
    pushup(x);
}

ll query(int x, int l, int r, int ql, int qr, int p) {
    if (ql <= l && r <= qr)
        return tree[x].sum[p - 1];
    ll res = 0;
    int mid = (l + r) / 2;
    pushdown(x, l, r);
    if (ql <= mid)
        res = (res + query(ls(x), l, mid, ql, qr, p)) % mod;
    if (mid < qr)
        res = (res + query(rs(x), mid + 1, r, ql, qr, p)) % mod;
    return res;
}

void init(int x, int l, int r) {
    tree[x].sum[0] = tree[x].sum[1] = tree[x].sum[2] = 0;
    tree[x].add = 0;
    tree[x].mul = 1;
    tree[x].assign = nexist;
    if (l == r)
        return;
    int mid = (l + r) / 2;
    init(ls(x), l, mid);
    init(rs(x), mid + 1, r);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    while (true) {
        n = read<int>();
        m = read<int>();
        if (n == 0 && m == 0)
            break;
        init(1, 1, n);
        while (m--) {
            int o = read<int>(), x = read<int>(), y = read<int>(), c = read<int>();
            switch (o) {
            case 1:
                modifyAdd(1, 1, n, x, y, c);
                break;
            case 2:
                modifyMul(1, 1, n, x, y, c);
                break;
            case 3:
                modifyAssign(1, 1, n, x, y, c);
                break;
            case 4:
                printf("%lld\n", query(1, 1, n, x, y, c));
                break;
            }
        }
    }   
    return 0;
}