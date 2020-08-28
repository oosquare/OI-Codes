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

constexpr int maxn = 40000 + 10;

int n, ans = 1;
bool isprime[maxn];
int t, prime[maxn], phi[maxn];

void getphi(int n) {
    t = 0;
    phi[1] = 1;
    memset(isprime, true, sizeof(isprime));
    isprime[0] = isprime[1] = false;
    for (int i = 2; i <= n; ++i) {
        if (isprime[i]) {
            prime[++t] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= t; ++j) {
            if (prime[j] * i > n)
                break;
            isprime[i * prime[j]] = false;
            phi[i * prime[j]] = phi[i] * (i % prime[j] ? prime[j] - 1 : prime[j]);
            if (i % prime[j] == 0)
                break;
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    using namespace IO;
    n = read();
    if (n == 1) {
        writeln(0);
        return 0;
    }
    getphi(n - 1);
    for (int i = 1; i <= n - 1; ++i)
        ans += 2 * phi[i];
    writeln(ans);
    return 0;
}