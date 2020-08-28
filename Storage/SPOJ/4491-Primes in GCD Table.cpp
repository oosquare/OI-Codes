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

#define int long long
constexpr int maxv = 1e7 + 10;

int prime[maxv], notprime[maxv], miu[maxv];
int n, m, t, l;

void get() {
    notprime[0] = notprime[1] = true;
    miu[1] = 1;
    for (int i = 2; i < maxv; ++i) {
        if (!notprime[i]) {
            prime[++l] = i;
            miu[i] = -1; 
        }
        for (int j = 1; j <= l; ++j) {
            if (i * prime[j] > maxv - 1)
                break;
            notprime[i * prime[j]] = true;
            miu[i * prime[j]] = i % prime[j] ? -miu[i] : 0;
            if (i % prime[j] == 0)
                break;
        }
    }
    for (int i = 2; i < maxv; ++i)
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

signed main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    using namespace IO;
    get();
    t = read();
    for (int casenum = 1; casenum <= t; ++casenum) {
        n = read(), m = read();
        int res = 0;
        for (int i = 1; prime[i] <= min(n, m) && i <= l; ++i)
            res += calc(n / prime[i], m / prime[i]);
        writeln(res);
    }
    return 0;
}