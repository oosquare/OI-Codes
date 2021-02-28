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

constexpr int maxn = 30000 + 10;

struct node {
    int l, r, sum;
};

node tree[maxn * 50];
int uuid, root[maxn];
int n, q, a[maxn], maxv, ans;

int &ls(int x) { return tree[x].l; }

int &rs(int x) { return tree[x].r; }

void pushup(int x) {
    tree[x].sum = tree[ls(x)].sum + tree[rs(x)].sum;
}

void insert(int &x, int y, int l, int r, int v) {
    tree[x = ++uuid] = tree[y];
    ++tree[x].sum;
    if (l == r && r == v)
        return;
    int mid = (l + r) / 2;
    if (v <= mid)
        insert(ls(x), ls(y), l, mid, v);
    else
        insert(rs(x), rs(y), mid + 1, r, v);
    pushup(x);
}

int query(int x, int l, int r, int ql, int qr) {
    if (!x)
        return 0;
    if (ql <= l && r <= qr)
        return tree[x].sum;
    int mid = (l + r) / 2, res = 0;
    if (ql <= mid)
        res += query(ls(x), l, mid, ql, qr);
    if (mid < qr)
        res += query(rs(x), mid + 1, r, ql, qr);
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    using namespace IO;
    n = read();
    for (int i = 1; i <= n; ++i)
        maxv = max(maxv, a[i] = read());
    for (int i = 1; i <= n; ++i)
        insert(root[i], root[i - 1], 1, maxv, a[i]);
    q = read();
    for (int i = 1; i <= q; ++i) {
        int x = max(1, read() ^ ans), y = min(n, read() ^ ans), k = read() ^ ans;
        if (x > y) {
            ans = 0;
        } else {
            int lans = query(root[x - 1], 1, maxv, k + 1, maxv);
            int rans = query(root[y], 1, maxv, k + 1, maxv);
            ans = rans - lans;
        }
        writeln(ans);
    }
    return 0;
}