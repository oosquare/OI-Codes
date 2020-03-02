#include <bits/stdc++.h>
using namespace std;

double f[2001][2001], p;
int n, t;

int main() {
    scanf("%d%lf%d", &n, &p, &t);
    f[0][0] = 1;
    for (int i = 0; i < t; ++i) {
        f[i + 1][n] += f[i][n];
        for (int j = 0; j < n; ++j) {
            if (f[i][j] > 1e-10) {
                f[i + 1][j + 1] += f[i][j] * p;
                f[i + 1][j] += f[i][j] * (1 - p);
            }
        }
    }
    double ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += f[t][i] * i;
    }
    printf("%.6lf\n", ans);
}