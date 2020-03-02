#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int f[11][11][11][11];
int c[11][11] = {0};
int n;
int main() {
    cin >> n;
    while (1) {
        int a, b, num;
        cin >> a >> b >> num;
        if (!a && !b)
            break;
        c[a][b] = num;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                for (int h = 1; h <= n; h++) {
                    if (i == k && j == h) {
                        f[i][j][k][h] = max(f[i - 1][j][k - 1][h],
                                            max(f[i][j - 1][k][h - 1],
                                                max(f[i - 1][j][k][h - 1],
                                                    f[i][j - 1][k - 1][h]))) +
                                        c[i][j];
                    } else {
                        f[i][j][k][h] = max(f[i - 1][j][k - 1][h],
                                            max(f[i][j - 1][k][h - 1],
                                                max(f[i - 1][j][k][h - 1],
                                                    f[i][j - 1][k - 1][h]))) +
                                        c[i][j] + c[k][h];
                    }
                }
            }
        }
    }
    cout << f[n][n][n][n];
}