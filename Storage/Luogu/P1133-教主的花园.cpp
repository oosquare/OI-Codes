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

constexpr int maxn = 100000 + 5;
int n, val[maxn][3], f[maxn][3][2], ans;

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read();
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < 3; ++j)
            val[i][j] = read();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
            for (int k = 0; k < 2; ++k)
                f[1][j][k] = 0;
        f[1][i][0] = f[1][i][1] = val[1][i];
        for (int j = 2; j <= n; ++j) {
            f[j][0][0] = val[j][0] + max(f[j - 1][1][1], f[j - 1][2][1]);
            f[j][1][1] = val[j][1] + f[j - 1][0][0];
            f[j][1][0] = val[j][1] + f[j - 1][2][1];
            f[j][2][1] = val[j][2] + max(f[j - 1][0][0], f[j - 1][1][0]);
        }
        if (i == 0)
            ans = max(ans, max(f[n][1][1], f[n][2][1]));
        if (i == 1)
            ans = max(ans, max(f[n][0][0], f[n][2][1]));
        if (i == 2)
            ans = max(ans, max(f[n][0][0], f[n][1][0]));
    }
    printf("%d\n", ans);
    return 0;
}