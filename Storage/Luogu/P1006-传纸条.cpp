#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 50 + 1;
constexpr int maxm = 50 + 1;

int n, m;
int a[maxn][maxm], f[maxn][maxm][maxn][maxm];
constexpr int dir[2][2] = {{-1, 0}, {0, -1}};

bool invaild(int x, int y) {
    return x < 1 || x > n || y < 1 || y > m;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> a[i][j];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int k = 1; k <= n; ++k) {
                for (int l = 1; l <= m; ++l) {
                    f[i][j][k][l] = a[i][j] + a[k][l];
                    for (int p = 0; p <= 1; ++p) {
                        for (int q = 0; q <= 1; ++q) {
                            int li = i + dir[p][0], lj = j + dir[p][1];
                            int lk = k + dir[q][0], ll = l + dir[q][1];
                            if (invaild(li, lj) || invaild(lk, ll) || (li == lk && lj == ll))
                                continue;
                            f[i][j][k][l] = max(f[i][j][k][l], f[li][lj][lk][ll] + a[i][j] + a[k][l]);
                        }
                    }
                }
            }
        }
    }
    cout << f[n][m][n][m] << endl;
    return 0;
}