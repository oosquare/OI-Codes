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

constexpr int maxn = 100000 + 10;
constexpr int mod = 19961993;
constexpr ll prime[] = {
    2,   3,   5,   7,   11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,
    53,  59,  61,  67,  71,  73,  79,  83,  89,  97,  101, 103, 107, 109, 113,
    127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197,
    199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281
};
constexpr ll inv[] = {
    9980997,  6653998,  11977196, 8555140,  5444180,  1535538,  10568114,
    14708837, 3471651,  11701858, 17386252, 1618540,  16066970, 2321162,
    18263100, 16948862, 12518538, 15380552, 10725847, 1686929,  13399146,
    17182475, 12025297, 15924736, 13582387, 395287,   6395590,  15857658,
    16299242, 6359573,  3300802,  18742940, 6702567,  10914471, 16210746,
    11765678, 5340151,  18247466, 7769638,  8077107,  11932588, 6506948,
    1985748,  6619521,  5877135,  4413707,  9744480,  10115270, 14597757,
    16475182, 18334191, 5011379,  18885205, 7555336,  621385,   11309266,
    12170137, 12006660, 18304499, 11153142
};

struct node {
    ll product, status;
};

node tree[maxn * 4];
ll a[maxn];
int n;

void pushup(int x) {
    tree[x].product = tree[x * 2].product * tree[x * 2 + 1].product % mod;
    tree[x].status = tree[x * 2].status | tree[x * 2 + 1].status;
}

void modify(int x, int l, int r, int p, ll v, ll s) {
    if (l == r) {
        tree[x].product = v;
        tree[x].status ^= s;
        return;
    }
    int mid = (l + r) / 2;
    if (p <= mid)
        modify(x * 2, l, mid, p, v, s);
    else
        modify(x * 2 + 1, mid + 1, r, p, v, s);
    pushup(x);
}

node query(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return tree[x];
    int mid = (l + r) / 2;
    node res = {1, 0};
    if (ql <= mid) {
        node t = query(x * 2, l, mid, ql, qr);
        res.product = res.product * t.product % mod;
        res.status |= t.status;
    }
    if (mid < qr) {
        node t = query(x * 2 + 1, mid + 1, r, ql, qr);
        res.product = res.product * t.product % mod;
        res.status |= t.status;
    }
    return res;
}

void build(int x, int l, int r, ll v, ll s) {
    if (l == r) {
        tree[x].product = v;
        tree[x].status = s;
        return;
    }
    int mid = (l + r) / 2;
    build(x * 2, l, mid, v, s);
    build(x * 2 + 1, mid + 1, r, v, s);
    pushup(x);
}

ll getstatus(ll x) {
    ll st = 0;
    for (int i = 0; i < 60; ++i)
        if (x % prime[i] == 0)
            st |= (1LL << i);
    return st;
}

ll phi(node nd) {
    ll x = nd.product, s = nd.status;
    ll res = x;
    for (int i = 0; i < 60; ++i)
        if (s & (1LL << i))
            res = res * inv[i] % mod * (prime[i] - 1) % mod;
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    using namespace IO;
    n = read();
    for (int i = 1; i <= 100000; ++i)
        a[i] = 3;
    build(1, 1, 100000, 3, 1 << 1);
    for (int i = 1; i <= n; ++i) {
        ll op = read<ll>(), x = read<ll>(), y = read<ll>();
        if (op == 0)
            writeln(phi(query(1, 1, 100000, x, y)));
        else
            modify(1, 1, 100000, x, a[x], getstatus(a[x])),
            modify(1, 1, 100000, x, a[x] = y, getstatus(y));
    }
    return 0;
}