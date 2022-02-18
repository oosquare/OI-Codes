#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

int n, m, a[7], p[7], f[307][307][64];
double ans;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        p[i] = i;
    }

    sort(a + 1, a + n + 1);
    do {
        memset(f, 0, sizeof(f));
        f[0][a[n] * n][0] = 1;

        for (int i = 1; i < n * m; ++i) {
            for (int j = i; j <= n * m; ++j) {
                for (int s = 0; s < (1 << (n - 1)); ++s) {
                    f[i][j][s] += f[i - 1][j][s];
                    
                    int x = i % n;
                    
                    if (!x || ((s >> (x - 1)) & 1))
                        continue;
                    
                    f[i][min(n * m, max(j, i + a[p[x]] * n))][s | (1 << (x - 1))] += f[i][j][s];
                }
            }
        }
        
        ans += f[n * m - 1][n * m][(1 << (n - 1)) - 1];
    } while (next_permutation(p + 1, p + n));

    for (int i = 1; i < n; ++i)
        ans /= i * m;
    
    cout << fixed << setprecision(1000) << ans << endl;
    return 0;
}
