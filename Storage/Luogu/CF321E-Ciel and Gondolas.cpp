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

int min(int x, int y) {
    return (x < y ? x : y);
}

constexpr int maxn = 4000 + 5;
constexpr int maxk = 800 + 5;
constexpr int oo = 0x3f3f3f3f;

int n, k, u[maxn][maxn];
int f[maxk][maxn];

inline int query(int x1, int y1, int x2, int y2) {
    return u[x2][y2] - u[x2][y1 - 1] - u[x1 - 1][y2] + u[x1 - 1][y1 - 1];
}

inline int weight(int i, int j) {
    return query(j + 1, j + 1, i, i) / 2;
}

void dp(int l, int r, int pl, int pr, int i) {
    if (l > r)
        return;

    int mid = (l + r) / 2, pos = 0;

    for (int j = pl; j <= min(pr, mid - 1); ++j) {
        if (f[i][mid] > f[i - 1][j] + weight(mid, j)) {
            f[i][mid] = f[i - 1][j] + weight(mid, j);
            pos = j;
        }
    }

    dp(l, mid - 1, pl, pos, i);
    dp(mid + 1, r, pos, pr, i);
}

int main() {
    n = read(), k = read();

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            u[i][j] = read();

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            u[i][j] += u[i][j - 1];
    
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            u[i][j] += u[i - 1][j];

    for (int i = 0; i <= k; ++i)
        for (int j = 0; j <= n; ++j)
            f[i][j] = oo;

    f[0][0] = 0;

    for (int i = 1; i <= k; ++i)
        dp(1, n, 0, n - 1, i);

    printf("%d\n", f[k][n]);
    return 0;
}