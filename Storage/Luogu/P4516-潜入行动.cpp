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

constexpr int maxn = 1e5 + 10;
constexpr int maxk = 100 + 10;
constexpr int mod = 1e9 + 7;

vector<int> tree[maxn];
int n, k;
/** f[x][i][0/1][0/1] : 在 x 子树放了 i 个装置，x 安装/不安装，当前子树内 x 被覆盖/不被覆盖 */
int f[maxn][maxk][2][2], tmp[maxk][2][2], sze[maxn];

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void Dp(int x, int fa, int dep) {
    if (dep > k + 2) {
        IO::writeln(0);
        exit(0);
    }
    sze[x] = 1;
    f[x][0][1][1] = f[x][1][0][1] = 1;
    for (int y : tree[x]) {
        if (y == fa) continue;
        Dp(y, x, dep + 1);
        sze[x] += sze[y];
        for (int i = 0; i <= min(sze[x], k); ++i) {
            tmp[i][0][0] = exchange(f[x][i][0][0], 0);
            tmp[i][0][1] = exchange(f[x][i][0][1], 0);
            tmp[i][1][0] = exchange(f[x][i][1][0], 0);
            tmp[i][1][1] = exchange(f[x][i][1][1], 0);
        }
        for (int i = 0, e1 = min(sze[x], k); i <= e1; ++i) {
            for (int j = 0, e2 = min(sze[y], i); j <= e2; ++j) {
                f[x][i][0][0] = (f[x][i][0][0] +
                    (1LL * tmp[i - j][0][0] * 
                        (1LL * f[y][j][0][0] + f[y][j][0][1] + 
                        f[y][j][1][0] + f[y][j][1][1]) % mod +
                    1LL * tmp[i - j][0][1] *
                        (f[y][j][0][0] + f[y][j][0][1]) % mod) % mod) % mod;
                f[x][i][1][0] = (f[x][i][1][0] +
                    (1LL * f[y][j][0][0] * (tmp[i - j][1][0] + tmp[i - j][1][1]) % mod +
                    1LL * f[y][j][1][0] * tmp[i - j][1][0] % mod) % mod) % mod;
                f[x][i][0][1] = (f[x][i][0][1] +
                    1LL * (f[y][j][1][0] + f[y][j][1][1]) * tmp[i - j][0][1] % mod) % mod;
                f[x][i][1][1] = (f[x][i][1][1] +
                    1LL * f[y][j][1][0] * tmp[i - j][1][1] % mod) % mod;
            }
        }
    }
}

int main() {
    using namespace IO;
    n = read(), k = read();
    for (int i = 1; i < n; ++i) {
        int a = read(), b = read();
        link(a, b);
    }
    Dp(1, 0, 1);
    writeln((f[1][k][0][0] + f[1][k][1][0]) % mod);

    // for (int i = 1; i <= n; ++i) {
    //     cout << i << " : ";
    //     for (int j = 0; j <= k; ++j) {
    //         cout << f[i][j][0][0] << " ";
    //     }
    //     cout << endl;
    // }
    return 0;
}