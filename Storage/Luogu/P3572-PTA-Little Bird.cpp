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

constexpr int maxn = 1000000 + 10;
int n, q, k, d[maxn];
int que[maxn], f[maxn];

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read();
    for (int i = 1; i <= n; ++i)
        d[i] = read();
    q = read();
    while (q--) {
        k = read();
        int l = 1, r = 1;
        que[r] = 1;
        for (int i = 2; i <= n; ++i) {
            while (l <= r && i - que[l] > k)
                ++l;
            if (d[que[l]] <= d[i])
                f[i] = f[que[l]] + 1;
            else
                f[i] = f[que[l]];
            while (l <= r && (f[que[r]] > f[i] || (f[que[r]] == f[i] && d[que[r]] <= d[i])))
                --r;
            que[++r] = i;
        }
        printf("%d\n", f[n]);
    }
    return 0;
}