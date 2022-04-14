#include <iostream>
#include <iomanip>

constexpr int MAX_N = 100 + 10;

int n, m, x, y;
long double f[MAX_N][MAX_N];

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("expect.in", "r", stdin);
    std::freopen("expect.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m >> x >> y;

    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            f[i][j] = n * m;

    f[x][y] = 0;

    for (int t = 1; t <= 12000; ++t) {
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                if (i == x && j == y)
                    continue;
                else
                    f[i][j] = 0.5 * (f[(i + 1) % n][j] + f[i][(j + 1) % m]) + 1;
            }
        }
    }

    std::cout << std::fixed << std::setprecision(6) << f[0][0] << std::endl;
    return 0;
}
