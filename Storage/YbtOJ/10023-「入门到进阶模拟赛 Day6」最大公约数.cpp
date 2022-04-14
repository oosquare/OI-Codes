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

int cnt[1000005], n, maxv;

int main() {
    freopen("gcd.in", "r", stdin);
    freopen("gcd.out", "w", stdout);
    n = read();
    for (int i = 1; i <= n; ++i) {
        int v = read();
        maxv = max(v, maxv);
        ++cnt[v];
    }
    for (int i = maxv; i >= 1; --i) {
        int t = 0;
        for (int j = i; j <= maxv; j += i) {
            t += cnt[j];
            if (t >= 2) {
                printf("%d\n", i);
                return 0;
            }
        }
    }
    return 0;
}
