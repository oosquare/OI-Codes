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

constexpr int maxn = 6e3 + 10;
constexpr int oo = 0x3f3f3f3f;

int t1[maxn], t2[maxn], t3[maxn], limit[maxn], f[2][maxn * 5];
int n, ans = oo;

int main() {
    using namespace IO;
    n = read();
    for (int i = 1; i <= n; ++i) {
        t1[i] = read(), t2[i] = read(), t3[i] = read();
        limit[i] = limit[i - 1] + max(t1[i], t3[i]);
    }
    for (int i = 1; i <= n; ++i) {
        int now = i % 2, pre = (i + 1) % 2;
        // int now = i, pre = i - 1;
        for (int j = 0; j <= limit[i]; ++j) {
            f[now][j] = oo;
            if (t1[i] && j >= t1[i] && j - t1[i] <= limit[i - 1]) {
                f[now][j] = f[pre][j - t1[i]];
            }
            if (t2[i] && j <= limit[i - 1]) {
                if (f[now][j] > f[pre][j] + t2[i]) {
                    f[now][j] = f[pre][j] + t2[i];
                }
            }
            if (t3[i] && j >= t3[i] && j - t3[i] <= limit[i - 1]) {
                if (f[now][j] > f[pre][j - t3[i]] + t3[i]) {
                    f[now][j] = f[pre][j - t3[i]] + t3[i];
                }
            }
        }
    }
    for (int i = 1, now = n % 2, v; i <= limit[n]; ++i) {
        v = max(i, f[now][i]);
        if (ans > v)
            ans = v;
    }
    writeln(ans);
    // cout << endl;
    // for (int i = 0; i <= n; ++i) {
    //     cout << i << " : ";
    //     for (int j = 0; j <= limit[i]; ++j) {
    //         cout << f[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    return 0;
}