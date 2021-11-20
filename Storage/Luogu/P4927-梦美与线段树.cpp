#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

namespace IO {

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T = long long> T read() {
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

template <typename T = long long> void writeln(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[200];
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

} // namespace IO

#define ll __int128 
#define int __int128

constexpr int maxn = 5e5 + 10;
constexpr int mod = 998244353;

struct Node {
    int left, right;
    __int128 sum, sqr, suml, len2, add;

    int length() const {
        return right - left + 1;
    }
};

int n, m, a[maxn];
Node tree[maxn * 4];

ll power(ll x, ll y) {
    ll res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = 1ll * res * x % mod;

        x = 1ll * x * x % mod;
    }

    return res;
}

ll square(ll x) {
    return x * x;
}

void pushup(int x) {
    tree[x].sum = (tree[x * 2].sum + tree[x * 2 + 1].sum);
    tree[x].sqr = ((tree[x * 2].sqr + tree[x * 2 + 1].sqr) + square(tree[x].sum));
    tree[x].suml = ((tree[x * 2].suml + tree[x * 2 + 1].suml) +
        1ll * tree[x].sum * tree[x].length());
}

void update(int x, int v) {
    tree[x].add = (tree[x].add + v);
    tree[x].sqr = (tree[x].sqr + 2ll * tree[x].suml * v + 1ll * tree[x].len2 * square(v));
    tree[x].suml = (tree[x].suml + 1ll * v * tree[x].len2);
    tree[x].sum = (tree[x].sum + 1ll * v * tree[x].length());
}

void pushdown(int x) {
    if (tree[x].add == 0)
        return;

    update(x * 2, tree[x].add);
    update(x * 2 + 1, tree[x].add);
    tree[x].add = 0;
}

void build(int x, int l, int r) {
    tree[x].left = l;
    tree[x].right = r;

    if (l == r) {
        tree[x].sum = a[l];
        tree[x].sqr = square(a[l]);
        tree[x].suml = a[l];
        tree[x].len2 = 1;
        return;
    }

    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
    tree[x].len2 = ((tree[x * 2].len2 + tree[x * 2 + 1].len2) + square(tree[x].length()));
    pushup(x);
}

void modify(int x, int l, int r, ll v) {
    if (l <= tree[x].left && tree[x].right <= r) {
        update(x, v);
        return;
    }

    int mid = (tree[x].left + tree[x].right) / 2;
    pushdown(x);

    if (l <= mid)
        modify(x * 2, l, r, v);

    if (mid < r)
        modify(x * 2 + 1, l, r, v);

    pushup(x);
}

ll query() {
    pushdown(1);
    __int128 x = tree[1].sqr;
    __int128 y = tree[1].sum;

    while (y % mod == 0) {
        x /= mod;
        y /= mod;
    }

    x %= mod;
    y %= mod;

    return x * power(y, mod - 2) % mod;
}

signed main() {
    using namespace IO;
    n = read(), m = read();

    for (int i = 1; i <= n; ++i)
        a[i] = read();

    build(1, 1, n);

    for (int i = 1; i <= m; ++i) {
        int op = read();

        if (op == 1) {
            int l = read(), r = read(), v = read();
            modify(1, l, r, v);
        } else {
            writeln(query());
        }
    }

    return 0;
}