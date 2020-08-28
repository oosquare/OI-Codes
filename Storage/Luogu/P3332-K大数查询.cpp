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

struct operation {
    int type, id, l, r;
    ll k;
};

struct node {
    ll sum, add;
};

constexpr int maxn = 2e5 + 10;
constexpr int oo = 0x7fffffff;

operation q[maxn], q1[maxn], q2[maxn];
node tree[maxn * 4];
int n, m, t;
ll ans[maxn];

void pushup(int x) {
    tree[x].sum = tree[x * 2].sum + tree[x * 2 + 1].sum;
}

void update(int x, int l, int r, ll v) {
    tree[x].add += v;
    tree[x].sum += (r - l + 1) * v;
}

void pushdown(int x, int l, int r, int mid) {
    if (tree[x].add == 0)
        return;
    update(x * 2, l, mid, tree[x].add);
    update(x * 2 + 1, mid + 1, r, tree[x].add);
    tree[x].add = 0;
}

void modify(int x, int l, int r, int ml, int mr, ll v) {
    if (ml <= l && r <= mr) {
        update(x, l, r, v);
        return;
    }
    int mid = (l + r) / 2;
    pushdown(x, l, r, mid);
    if (ml <= mid)
        modify(x * 2, l, mid, ml, mr, v);
    if (mid < mr)
        modify(x * 2 + 1, mid + 1, r, ml, mr, v);
    pushup(x);
}

ll query(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return tree[x].sum;
    int mid = (l + r) / 2;
    pushdown(x, l, r, mid);
    ll res = 0;
    if (ql <= mid)
        res += query(x * 2, l, mid, ql, qr);
    if (mid < qr)
        res += query(x * 2 + 1, mid + 1, r, ql, qr);
    return res;
}

void BinarySolve(int ql, int qr, ll l, ll r) {
    if (ql > qr)
        return;
    if (l == r) {
        for (int i = ql; i <= qr; ++i)
            ans[q[i].id] = l;
        return;
    }
    ll mid = (l + r) / 2;
    int len1 = 0, len2 = 0, len = ql - 1;
    for (int i = ql; i <= qr; ++i) {
        if (q[i].type == 1) {
            
            if (q[i].k > mid) {
                modify(1, 1, n, q[i].l, q[i].r, 1);
                q1[++len1] = q[i];
            } else {
                q2[++len2] = q[i];
            }
        }
        if (q[i].type == 2) {
            ll t = query(1, 1, n, q[i].l, q[i].r);
            if (q[i].k <= t) {
                q1[++len1] = q[i];
            } else {
                q2[++len2] = q[i];
                q2[len2].k -= t;
            }
        }
    }
    for (int i = 1; i <= len1; ++i)
        q[++len] = q1[i];
    for (int i = 1; i <= len2; ++i)
        q[++len] = q2[i];
    for (int i = 1; i <= len1; ++i)
        if (q1[i].type == 1)
            modify(1, 1, n, q1[i].l, q1[i].r, -1);
    BinarySolve(ql + len1, qr, l, mid);
    BinarySolve(ql, ql + len1 - 1, mid + 1, r);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    using namespace IO;
    n = read(), m = read();
    for (int i = 1; i <= m; ++i) {
        int o = read(), l = read(), r = read();
        ll c = read<ll>();
        if (o == 1)
            q[i] = {1, 0, l, r, c};
        else
            q[i] = {2, ++t, l, r, c};
    }
    BinarySolve(1, m, 1, oo);
    for (int i = 1; i <= t; ++i)
        writeln(ans[i]);
    return 0;
}