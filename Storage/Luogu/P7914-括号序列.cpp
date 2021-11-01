#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 500 + 10;
constexpr int mod = 1e9 + 7;

int n, t;
char s[maxn];
int f[4][maxn][maxn], sum[maxn];

inline void add(int &x, int y) {
    x += y;

    if (x >= mod)
        x -= mod;
}

bool isBracket(char a, char b) {
    return (a == '(' || a == '?') && (b == ')' || b == '?');
}

bool isStar(char a) {
    return a == '*' || a == '?';
}

int main() {
    // ios::sync_with_stdio(false);
    cin >> n >> t;
    cin >> (s + 1);

    for (int i = 1; i <= n; ++i)
        sum[i] += sum[i - 1] + isStar(s[i]);

    for (int l = 2; l <= n; ++l) {
        for (int i = 1, j = i + l - 1; j <= n; ++i, ++j) {
            int cnt = sum[j - 1] - sum[i];

            if (isBracket(s[i], s[j])) {
                if (cnt == j - i - 1 && cnt <= t) {
                    add(f[0][i][j], 1);
                    add(f[1][i][j], 1);
                }

                for (int k = i + 1; k < j; ++k) {
                    add(f[0][i][j], 1ll * f[1][i][k] * f[0][k + 1][j] % mod);
                    add(f[0][i][j], 1ll * f[1][i][k] * f[2][k + 1][j] % mod);
                }

                add(f[0][i][j], f[0][i + 1][j - 1]);
                add(f[0][i][j], f[2][i + 1][j - 1]);
                add(f[0][i][j], f[3][i + 1][j - 1]);
                add(f[1][i][j], f[0][i + 1][j - 1]);
                add(f[1][i][j], f[2][i + 1][j - 1]);
                add(f[1][i][j], f[3][i + 1][j - 1]);
            }

            if (isStar(s[i])) {
                int cnt = 0;

                for (int k = i; k <= j - 2; ++k) {
                    if (!isStar(s[k]) || cnt + 1 > t)
                        break;

                    ++cnt;
                    add(f[2][i][j], f[0][k + 1][j]);
                }
            }

            if (isStar(s[j])) {
                int cnt = 0;

                for (int k = j; k >= i + 2; --k) {
                    if (!isStar(s[k]) || cnt + 1 > t)
                        break;

                    ++cnt;
                    add(f[3][i][j], f[0][i][k - 1]);
                }
            }
        }
    }

    cout << f[0][1][n] << endl;
    return 0;
}