#include <iostream>
using namespace std;

constexpr int maxn = 20 + 5;
constexpr int maxt = 10 + 5;

int n, t;
long long f[maxn][4][4][maxt][maxt], ans;

bool calc(int type, int a, int b, int c) {
    if (type == 1)
        return a < b && b > c;
    else
        return a > b && b < c;
}

int main() {
    cin >> n >> t;

    for (int a = 0; a < 4; ++a) {
        for (int b = 0; b < 4; ++b) {
            if (a == b)
                continue;

            f[2][a][b][0][0] = 1;
        }
    }

    for (int i = 2; i < n; ++i) {
        for (int a = 0; a < 4; ++a) {
            for (int b = 0; b < 4; ++b) {
                if (a == b)
                    continue;

                for (int x = 0; x <= t; ++x) {
                    for (int y = 0; y < t; ++y) {
                        for (int c = 0; c < 4; ++c) {
                            if (b == c)
                                continue;

                            f[i + 1][b][c][x + calc(1, a, b, c)][y + calc(2, a, b, c)] += f[i][a][b][x][y];
                        }
                    }
                }
            }
        }
    }

    for (int a = 0; a < 4; ++a) {
        for (int b = 0; b < 4; ++b) {
            if (a == b)
                continue;

            ans += f[n][a][b][t][t - 1];
        }
    }

    cout << ans << endl;
    return 0;
}