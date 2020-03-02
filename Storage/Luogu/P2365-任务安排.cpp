#include <bits/stdc++.h>
using namespace std;

const int maxn = 5002;
int n, s, t[maxn], c[maxn], f[maxn];

int main() {
    scanf("%d%d", &n, &s);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &t[i], &c[i]);
        t[i] += t[i - 1];
        c[i] += c[i - 1];
    }
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            f[i] = min(f[i], f[j] + t[i] * (c[i] - c[j]) + s * (c[n] - c[j]));
        }
    }
    printf("%d\n", f[n]);
    return 0;
}