#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 200 + 10;

int f[maxn][maxn];
int n0, n, len[maxn], color[maxn];
char seq[maxn];

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("zuma.in", "r", stdin);
    freopen("zuma.out", "w", stdout);
#endif
    cin >> (seq + 1);
    n0 = strlen(seq + 1);
    len[n = 1] = 1;
    color[n] = seq[1] - '0';
    for (int i = 2; i <= n0; ++i) {
        if (seq[i] == seq[i - 1]) {
            ++len[n];
        } else {
            len[++n] = 1;
            color[n] = seq[i] - '0';
        }
    }
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; ++i)
        f[i][i] = 3 - len[i];
    for (int l = 2; l <= n; ++l) {
        for (int i = 1, j = i + l - 1; j <= n; ++i, ++j) {
            if (color[i] != color[j]) {
                for (int k = i; k < j; ++k) {
                    f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
                }
            } else {
                if (l >= 3 && len[i] + len[j] >= 3) {
                    f[i][j] = f[i + 1][j - 1];
                }
                if (l >= 3 && len[i] + len[j] < 3) {
                    f[i][j] = f[i + 1][j - 1] + 1;
                }
                if (l >= 5) {
                    if (len[i] + len[j] < 4) {
                        for (int k = i + 2; k <= j - 2; k += 2) {
                            if (len[k] == 1) {
                                f[i][j] = min(f[i][j], f[i + 1][k - 1] + f[k + 1][j - 1]);
                            }
                        }
                    }
                }

            }
        }
    }
    cout << f[1][n] << endl;
    return 0;
}
