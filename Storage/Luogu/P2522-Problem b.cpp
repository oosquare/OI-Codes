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

constexpr int maxv = 5e4;

int n, t, miu[maxv + 10], prime[maxv + 10], notprime[maxv + 10];

void getmiu() {
    miu[1] = 1;
    notprime[1] = 1;
    for (int i = 1; i <= maxv; ++i) {
        if (!notprime[i]) {
            prime[++t] = i;
            miu[i] = -1;
        }
        for (int j = 1; j <= t; ++j) {
            if (i * prime[j] > maxv)
                break;
            notprime[i * prime[j]] = true;
            miu[i * prime[j]] = i % prime[j] == 0 ? 0 : -miu[i];
            if (i % prime[j] == 0)
                break;
        }
    }
    for (int i = 1; i <= maxv; ++i)
        miu[i] += miu[i - 1];
}

int calc(int n, int m) {
    int res = 0;
    for (int l = 1, r; l <= min(n, m); l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        res += (miu[r] - miu[l - 1]) * (n / l) * (m / l);
    }
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    using namespace IO;
    getmiu();
    n = read();
    for (int casenum = 1; casenum <= n; ++casenum) {
        int a = read(), b = read(), c = read(), d = read(), k = read();
        writeln(calc(b / k, d / k) - calc(b / k, (c - 1) / k) - calc((a - 1) / k, d / k) + calc((a - 1) / k, (c - 1) / k));
    }
    return 0;
}