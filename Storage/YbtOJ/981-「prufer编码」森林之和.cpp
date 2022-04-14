#include <cstdio>
using namespace std;

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();

    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            s = -1;

    for (; '0' <= c && c <= '9'; c = getchar())
        x = x * 10 + c - '0';

    return x * s;
}

template <typename T> void write(T x, char sep = '\n') {
    if (x == 0) {
        putchar('0');
        putchar(sep);
        return;
    }

    static int st[50];
    int top = 0;

    if (x < 0) {
        putchar('-');
        x = -x;
    }

    while (x) {
        st[++top] = x % 10;
        x /= 10;
    }

    while (top)
        putchar(st[top--] + '0');

    putchar(sep);
}

constexpr int MAXN = 5e3 + 10;

int t, p, n;
int c[MAXN][MAXN], f[MAXN], g[MAXN], s[MAXN];
int power[MAXN][MAXN];

void preprocess(int n) {
    for (int i = 0; i <= n; ++i) {
        c[i][0] = c[i][i] = 1;

        for (int j = 1; j < i; ++j)
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % p;
    }

    for (int i = 1; i <= n; ++i) {
        power[i][0] = 1;

        for (int j = 1; j <= n; ++j)
            power[i][j] = 1ll * power[i][j - 1] * i % p;
    }

    f[1] = 1;

    for (int i = 2; i <= n; ++i)
        f[i] = power[i][i - 2];

    g[0] = 1;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            g[i] = (g[i] + 1ll * c[i - 1][j - 1] * g[i - j] % p * f[j]) % p;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < i; ++j)
            s[i] = (s[i] + 1ll * c[i - 2][j - 1] * power[i - 1][i - j - 1] % p * j % p * j) % p;
}

int solve(int n) {
    int res = 0;

    for (int i = 1; i <= n; ++i)
        res = (res + 1ll * c[n - 1][i - 1] * g[n - i] % p * s[i]) % p;

    return 1ll * res * n % p;
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("forest.in", "r", stdin);
    freopen("forest.out", "w", stdout);
#endif
    t = read();
    p = read();

    preprocess(MAXN - 1);

    for (int i = 1; i <= t; ++i) {
        n = read();
        write(solve(n));
    }

    return 0;
}
