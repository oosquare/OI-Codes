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

constexpr int mod = 20101009;
constexpr int maxv = 1e7 + 10;

int miu[maxv], prime[maxv], notprime[maxv], miusum[maxv];
int n, m, t, ans;

void getmiu() {
    miu[1] = 1;
    notprime[0] = notprime[1] = true;
    for (int i = 2; i <= maxv - 10; ++i) {
        if (!notprime[i]) {
            prime[++t] = i;
            miu[i] = -1;
        }
        for (int j = 1; j <= t; ++j) {
            if (i * prime[j] > maxv)
                break;
            notprime[i * prime[j]] = true;
            miu[i * prime[j]] = i % prime[j] ? -miu[i] : 0;
            if (i % prime[j] == 0)
                break;
        }
    }
    for (int i = 1; i <= maxv - 10; ++i)
        miusum[i] = (miusum[i - 1] + 1LL * miu[i] * (1LL * i * i % mod) + mod) % mod;
}

int calc(int x) {
    return (1LL * x * (x + 1) / 2) % mod;
}

int calc(int n, int m) {
    int res = 0;
    for (int l = 1, r; l <= min(n, m); l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        res = (1LL * res + (1LL * miusum[r] - miusum[l - 1] + mod) % mod * calc(n / l) % mod * calc(m / l) % mod) % mod;
    }
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    using namespace IO;
    n = read(), m = read();
    getmiu();
    for (int i = 1; i <= min(n, m); ++i)
        ans = (ans + 1LL * i * calc(n / i, m / i) % mod) % mod;
    writeln(ans);
    return 0;
}