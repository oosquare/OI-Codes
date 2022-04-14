#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int maxnm = 2000 + 10;
constexpr int mod = 1e9 + 7;

int n, m, sl, sr, ans;
char str[maxn];
int f[maxnm][maxnm];

int main() {
    freopen("bracket.in", "r", stdin);
    freopen("bracket.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> m;
    cin >> (str + 1);

    for (int i = 1; i <= m; ++i) {
        if (str[i] == '(') {
            ++sr;
        } else {
            if (sr > 0) {
                --sr;
            } else {
                ++sl;
            }
        }
    }

    f[0][0] = 1;

    for (int i = 1; i <= n - m; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (j > 0)
                f[i][j] = (f[i][j] + f[i - 1][j - 1]) % mod;

            if (j < n - m)
                f[i][j] = (f[i][j] + f[i - 1][j + 1]) % mod;
        }
    }

    for (int i = 0; i <= n - m; ++i)
        for (int j = 0; j + max(sl, sr) <= n - m; ++j)
            ans = (ans + 1ll * f[i][sl + j] * f[n - m - i][sr + j] % mod) % mod;

    cout << ans << endl;
    return 0;
}
