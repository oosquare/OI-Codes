#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>
#include <vector>
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

using ll = long long;

constexpr int maxn = 80000 + 10;

int n, q, mod, mi, mx;
ll d[maxn], s[maxn];

int main() {
    using namespace IO;
    n = read(), q = read(), mod = read(), mi = read(), mx = read();

    for (int i = 1; i <= q; ++i) {
        char c = mygetchar();

        while (c != 'A' && c != 'Q')
            c = mygetchar();

        if (c == 'A') {
            int l = read(), r = read(), x = read();
            d[l] += x;
            d[r + 1] -= x;
        } else {
            int ans = 0;
            int l = read(), r = read();

            for (int j = 1; j <= n; ++j)
                s[j] = s[j - 1] + d[j];

            for (int j = l; j <= r; ++j)
                if (mi <= s[j] * j % mod && s[j] * j % mod <= mx)
                    ++ans;

            writeln(ans);
        }
    }

    for (int i = 1; i <= n; ++i)
        d[i] += d[i - 1];

    for (int i = 1; i <= n; ++i)
        s[i] = s[i - 1] + (mi <= d[i] * i % mod && d[i] * i % mod <= mx);

    q = read();

    for (int i = 1; i <= q; ++i) {
        int l = read(), r = read();
        writeln(s[r] - s[l - 1]);
    }

    return 0;
}