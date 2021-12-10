#include <iostream>
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

template <typename T> void write(T x, char sep = '\n') {
    if (x == 0) {
        putchar('0');
        putchar(sep);
        return;
    }

    static int st[21];
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

constexpr int maxn = 15;
constexpr int maxm = 50 + 10;
constexpr int mod = 1000003;

int t, n, k, m;
char str[maxn][maxm];
int cnt[1 << maxn];
int match[5][maxm][26], f[5][maxm][1 << maxn];
int ans;

inline int popcount(int x) {
    int res = 0;

    for (; x; x >>= 1)
        res += (x & 1);

    return res;
}

inline void add(int &x, int y) {
    x += y;

    if (x >= mod)
        x -= mod;
}

void solve() {
    n = read(), k = read();

    for (int i = 0; i < n; ++i)
        scanf("%s", str[i] + 1);

    m = strlen(str[0] + 1);

    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= m; ++j) {
            char c = str[i][j];
            if (c != '?') {
                match[t][j][c - 'a'] |= (1 << i);
            } else {
                for (int k = 0; k < 26; ++k) {
                    match[t][j][k] |= (1 << i);
                }
            }
        }
    }

    f[t][0][(1 << n) - 1] = 1;

    for (int i = 0; i < m; ++i)
        for (int s = 0; s < (1 << n); ++s)
            if (f[i][s] && cnt[s] >= k)
                for (int c = 0; c < 26; ++c)
                    if (cnt[s & match[t][i + 1][c]] >= k)
                    add(f[t][i + 1][s & match[t][i + 1][c]], f[t][i][s]);

    ans = 0;

    for (int s = 0; s < (1 << n); ++s)
        if (cnt[s] == k)
            add(ans, f[t][m][s]);

    write(ans);
}

int main() {
    for (int s = 0; s < (1 << 15); ++s)
        cnt[s] = popcount(s);

    t = read();

    while (t--)
        solve();

    return 0;
}