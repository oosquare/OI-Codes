#include <bits/stdc++.h>
using namespace std;

template <typename T = int> T read() {
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

int f[21][(1 << 20) + 10], graph[21][21], n;

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            graph[i][j] = read();
    memset(f, 0x3f, sizeof(f));
    f[0][1] = 0;
    for (int j = 0; j < (1 << n); ++j) {
        for (int i = 0; i < n; ++i) {
            if (!(j & (1 << i)))
                continue;
            for (int k = 0; k < n; ++k) {
                if (!((j ^ (1 << i)) >> k & 1))
                    continue;
                f[i][j] = min(f[i][j], f[k][j ^ (1 << i)] + graph[i][k]);
            }
        }
    }
    int res = f[n - 1][(1 << n) - 1];
    printf("%d\n", res);
    return 0;
}