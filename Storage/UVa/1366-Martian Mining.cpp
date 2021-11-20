#include <iostream>
using namespace std;

constexpr int maxn = 500 + 10;
constexpr int maxm = 500 + 10;

int n, m, a[maxn][maxm], b[maxn][maxm];
int sa[maxn][maxm], sb[maxn][maxm];
int f[maxn][maxm], mx[maxn][maxm];

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();

    while (c < '0' || c > '9') {
        if (c == '-')
            s = -1;

        c = getchar();
    }

    while ('0' <= c && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }

    return x * s;
}

int main() {
    while (true) {
        n = read(), m = read();

        if (!n && !m)
            break;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cin >> a[i][j];
                sa[i][j] = sa[i][j - 1] + a[i][j];
            }
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cin >> b[i][j];
                sb[i][j] = sb[i][j - 1] + b[i][j];
            }
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                f[i][j] = mx[i - 1][j] + sa[i][j] + sb[i][m] - sb[i][j];
                mx[i][j] = max(f[i][j], (j > 0 ? mx[i][j - 1] : 0));
            }
        }

        cout << mx[n][m] << endl;
    }
    return 0;
}