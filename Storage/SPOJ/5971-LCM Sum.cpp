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

constexpr int maxn = 1e6;

ll prime[maxn + 10], phi[maxn + 10], ans[maxn + 10];
bool notprime[maxn + 10];
int t, l;

void getphi(int n) {
    notprime[0] = notprime[1] = true;
    for (int i = 2; i <= n; ++i) {
        if (!notprime[i]) {
            prime[++l] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= l; ++j) {
            if (i * prime[j] > n)
                break;
            notprime[i * prime[j]] = true;
            phi[i * prime[j]] = phi[i] * (i % prime[j] ? prime[j] - 1 : prime[j]);
            if (i % prime[j] == 0)
                break;
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    using namespace IO;
    getphi(maxn);
    for (int i = 1; i <= maxn; ++i)
        for (int j = 1; i * j <= maxn; ++j)
            ans[i * j] += i * phi[i] / 2;
    for (int i = 1; i <= maxn; ++i)
        ans[i] = i * ans[i] + i;
    t = read();
    while (t--)
        writeln(ans[read()]);
    return 0;
}