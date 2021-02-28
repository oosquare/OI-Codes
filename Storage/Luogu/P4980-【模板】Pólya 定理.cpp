#include <cstdio>
using namespace std;

namespace IO {
    
inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T> T read() {
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

template <typename T> void writeln(T x) {
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

int x, n, p, res;

int phi(int x) {
    int res = x;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i)
            continue;
        res = res / i * (i - 1);
        while (x % i == 0)
            x /= i;
    }
    if (x > 1)
        res = res / x * (x - 1);
    return res;
}

int power(int x, int y) {
    int res = 1;
    while (y) {
        if (y & 1)
            res = 1LL * res * x % p;
        x = 1LL * x * x % p;
        y /= 2;
    }
    return res % p;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    using namespace IO;
    x = read<int>();
    for (int casenum = 1; casenum <= x; ++casenum) {
        n = read<int>(), p = 1e9 + 7;
        res = 0;
        int i;
        for (i = 1; i * i < n; ++i)
            if (n % i == 0)
                res = (res + 1LL * power(n, i - 1) * phi(n / i) % p + 1LL * power(n, (n / i) - 1) * phi(i) % p) % p;
        if (i * i == n)
            res = (res + 1LL * power(n, i - 1) * phi(i) % p) % p;
        writeln<int>(res);
    }
    return 0;
}