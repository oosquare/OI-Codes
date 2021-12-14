#include <cstdio>
#include <cstring>
using namespace std;

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();

    for (; c < '0' || '9' < c; c = getchar())
        if (c == '-')
            s = -1;

    for (; '0' <= c && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + c - '0';

    return x * s;
}

template <typename T> void write(T x, char sep) {
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

constexpr int maxn = 300 + 10;

int t, n, m, mod, cnt[maxn], suf[maxn];
int comb[maxn][maxn], f[maxn][maxn];

void solve() {
    n = read(), m = read(), mod = read();

    memset(f, 0, sizeof(f));
    memset(cnt, 0, sizeof(cnt));
    memset(suf, 0, sizeof(suf));

    for (int i = 1; i <= m; ++i) {
        int q = read();
        q = read();
        ++cnt[q];
    }

    for (int i = 0; i <= n; ++i) {
        comb[i][0] = comb[i][i] = 1;

        for (int j = 1; j < i; ++j)
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod;
    }

    for (int i = n; i >= 1; --i) {
        suf[i] = suf[i + 1] + cnt[i];

        if (suf[i] > n - i + 1) {
            printf("NO\n");
            return;
        }
    }


    f[n + 1][0] = 1;

    for (int i = n; i >= 1; --i)
        for (int j = suf[i]; j <= n - i + 1; ++j)
            for (int k = 0; k <= j - suf[i]; ++k)
                f[i][j] = (f[i][j] + 1ll * f[i + 1][j - cnt[i] - k] * comb[j - suf[i]][k] % mod) % mod;

    printf("YES %d\n", f[1][n]);
}

int main() {
    t = read();

    while (t--)
        solve();

    return 0;
}
