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

} // namespace IO

typedef long long ll;

constexpr int maxn = 1e7 + 10;

int t, n;
int miu[maxn], prime[maxn], notprime[maxn], tot;
ll f[maxn], g[maxn];

void get(int n) {
    g[1] = f[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!notprime[i]) {
            notprime[i] = 1;
            prime[++tot] = i;
            g[i] = i + 1;
            f[i] = i + 1;
        }
        for (int j = 1; j <= tot && i <= n / prime[j]; ++j) {
            notprime[prime[j] * i] = 1;
            if (i % prime[j] == 0) {
                g[i * prime[j]] = g[i] * prime[j] + 1;
                f[i * prime[j]] = f[i] / g[i] * g[i * prime[j]];
                break;
            } else {
                f[i * prime[j]] = f[i] * f[prime[j]];
                g[i * prime[j]] = 1 + prime[j];
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        f[i] += f[i - 1];
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("treatment.in", "r", stdin);
    freopen("treatment.out", "w", stdout);
#endif
    using namespace IO;
    get(10000000);
    t = read<int>();
    while (t--) {
        n = read<int>();
        writeln(1LL * n * n - f[n]);
    }
    return 0;
}
