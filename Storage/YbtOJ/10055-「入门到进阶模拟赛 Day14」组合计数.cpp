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

int n, m, a[101], sum, ans = 1;

ll power(ll x, ll k) {
    ll res = 1;
    while (k) {
        if (k % 2)
            res = res * x % 10007;
        x = x * x % 10007;
        k /= 2;
    }
    return res % 10007;
}

ll C(int n, int m) {
    ll a = 1, b = 1;
    for (int i = n - m + 1; i <= n; ++i)
        a = a * i % 10007;
    for (int i = 1; i <= m; ++i)
        b = b * i % 10007;
    return a * power(b, 10005) % 10007; 
}

int main() {
    freopen("poker.in", "r", stdin);
    freopen("poker.out", "w", stdout);
    using namespace IO;
    n = read();
    m = read();
    for (int i = 1; i <= m; ++i) {
        a[i] = read();
        sum += a[i];
    }
    if (sum > n) {
        writeln(0);
        return 0;
    }
    for (int i = 1; i <= m; ++i) {
        ans = 1ll * ans * C(n, a[i]) % 10007;
        n -= a[i];
    }
    writeln(ans);
    return 0;
}
