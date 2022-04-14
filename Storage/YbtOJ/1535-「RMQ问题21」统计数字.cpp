#include <bits/stdc++.h>
using namespace std;


namespace IO {

inline char mygetchar() {
    // static char ff[10000], *A = ff, *B = ff;
    // return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
    //            ? EOF
    //            : *A++;
    return getchar();
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

} // namespace IO

constexpr int maxn = 100000 + 2;

int n, m, p, a[maxn], bid[maxn], bsize, bcnt, lastans, logval[maxn];
bitset<maxn> st[65][9], ans;
int k, l, r;

inline void calc() {
    logval[1] = 0;
    logval[2] = 1;
    for (int i = 3; i < maxn; ++i) {
        logval[i] = logval[i / 2] + 1;
    }
}

inline bitset<maxn> query(int l, int r) {
    int s = logval[r - l + 1];
    return (st[l][s] | st[r - (1 << s) + 1][s]);
}

inline bitset<maxn> getans(int l, int r) {
    int lid = bid[l], rid = bid[r];
    bitset<maxn> res;
    res.reset();
    if (lid + 1 <= rid - 1) {
        res = query(lid + 1, rid - 1);
        for (int i = l, e = bsize * lid; i <= e; ++i)
            res.set(a[i], true);
        for (int i = bsize * (rid - 1) + 1; i <= r; ++i)
            res.set(a[i], true);
    } else {
        for (int i = l; i <= r; ++i)
            res.set(a[i], true);
    }
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("interval.in", "r", stdin);
    freopen("interval.out", "w", stdout);
#endif
    calc();
    n = IO::read(), m = IO::read(), p = IO::read();
    bsize = ceil(1.0 * n / 64);
    for (int i = 1; i <= n; ++i) {
        a[i] = IO::read();
        bid[i] = ceil(1.0 * i / bsize);
        bcnt = max(bid[i], bcnt);
    }
    for (int i = 1; i <= n; ++i)
        st[bid[i]][0].set(a[i], true);
    for (int j = 1; j <= 8; ++j)
        for (int i = 1, e = bcnt - (1 << j) + 1; i <= e; ++i)
            st[i][j] = st[i][j - 1] | st[i + (1 << (j - 1))][j - 1];
    for (int i = 1; i <= m; ++i) {
        ans.reset();
        k = IO::read();
        for (int j = 1; j <= k; ++j) {
            l = IO::read(), r = IO::read();
            if (p == 1 && i != 1) {
                l = (l ^ lastans) % n + 1;
                r = (r ^ lastans) % n + 1;
                if (l > r)
                    swap(l, r);
            }
            ans |= getans(l, r);
        }
        IO::writeln(lastans = ans.count());
    }
    return 0;
}
