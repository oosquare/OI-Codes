#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();

    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            s = -1;

    for (; '0' <= c && c <= '9'; c = getchar())
        x = 10 * x + c - '0';

    return x * s;
}

template <typename T> void write(T x, char blank = '\n') {
    if (x == 0) {
        putchar('0');
        putchar(blank);
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

    putchar(blank);
}

constexpr int maxn = 13;
constexpr int maxm = 2000 + 10;

int t, n, m, a[maxn][maxm], mx[maxm];
int id[maxm], sum[maxn + 5][1 << maxn];
int f[maxn + 5][1 << maxn];

inline int shift(int s) {
    return ((s << 1) & ((1 << n) - 1)) | (s >> (n - 1));
}

void solve() {
    n = read(), m = read();

    for (int i = 1; i <= m; ++i)
        mx[i] = 0;

    for (int i = 1; i <= min(n, m); ++i)
        for (int s = 0; s < (1 << n); ++s)
            sum[i][s] = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= m; ++j) {
            a[i][j] = read();
            mx[j] = max(mx[j], a[i][j]);
        }
    }

    iota(id + 1, id + 1 + m, 1);

    sort(id + 1, id + 1 + m, [](int l, int r) {
        return mx[l] > mx[r];
    });

    for (int j = 1; j <= min(n, m); ++j) {
        for (int s = 1; s < (1 << n); ++s) {
            int tmp = 0;

            for (int i = 0; i < n; ++i)
                if ((s >> i) & 1)
                    tmp += a[i][id[j]];

            for (int i = 1, ss = s; ss = shift(ss), i <= n; ++i)
                sum[j][ss] = max(sum[j][ss], tmp);
        }
    }

    for (int i = 1; i <= min(n, m); ++i) {
        for (int s = 0; s < (1 << n); ++s) {
            f[i][s] = f[i - 1][s];

            for (int ss = s; ss; ss = (s & (ss - 1)))
                f[i][s] = max(f[i][s], f[i - 1][s ^ ss] + sum[i][ss]);
        }
    }

    write(f[min(n, m)][(1 << n) - 1]);
}

int main() {
    t = read();

    while (t--)
        solve();
    return 0;
}