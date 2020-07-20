#include <bits/stdc++.h>
using namespace std;

typedef long long __int258;

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

typedef __int258 ll;

constexpr int maxn = 4e7 + 10;
constexpr ll maxa = numeric_limits<ll>::max();

struct node {
    ll sum, add;
    int l, r;
};

node tree[maxn];
int uuid, n, m, root;
map<ll, ll> s;

inline int &ls(int x) { return tree[x].l; }

inline int &rs(int x) { return tree[x].r; }

void update(int &x, ll l, ll r, ll v) {
    if (!x)
        x = ++uuid;
    tree[x].sum += (r - l + 1) * v;
    tree[x].add += v;
}

void pushup(int x) {
    tree[x].sum = tree[ls(x)].sum + tree[rs(x)].sum;
}

void pushdown(int x, ll l, ll r) {
    if (tree[x].add) {
        ll mid = (l + r) / 2;
        update(ls(x), l, mid, tree[x].add);
        update(rs(x), mid + 1, r, tree[x].add);
        tree[x].add = 0;
    }
}

void modify(int &x, ll l, ll r, ll ml, ll mr, ll v) {
    if (!x)
        x = ++uuid;
    if (ml <= l && r <= mr) {
        update(x, l, r, v);
        return;
    }
    ll mid = (l + r) / 2;
    pushdown(x, l, r);
    if (ml <= mid)
        modify(ls(x), l, mid, ml, mr, v);
    if (mid < mr)
        modify(rs(x), mid + 1, r, ml, mr, v);
    pushup(x);
}

ll query(int &x, ll l, ll r, ll ql, ll qr) {
    if (!x)
        return 0;
    if (ql <= l && r <= qr)
        return tree[x].sum;
    ll mid = (l + r) / 2, res = 0;
    pushdown(x, l, r);
    if (ql <= mid)
        res += query(ls(x), l, mid, ql, qr);
    if (mid < qr)
        res += query(rs(x), mid + 1, r, ql, qr);
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    // 帕秋莉, GO!
    using namespace IO;
    n = read();
    m = read();
    for (int i = 1; i <= n; ++i) {
        ll a = read<ll>(), w = read<ll>();
        s[a] += w;
    }
    for (auto p : s)
        modify(root, 1, maxa, p.first, maxa, p.second);
    while (m--) {
        int t = read();
        ll x = read<ll>(), y = read<ll>();
        if (t == 1) {
            ll res = query(root, 1, maxa, x, y);
            printf("%.4lf\n", (double) res / (y - x + 1));
        } else {
            modify(root, 1, maxa, x, maxa, y);
        }
    }
    return 0;
}