#include <iostream>
#include <iomanip>
using namespace std;

constexpr int MAXN = 1e3 + 5;

// * * 0 0 0 0
// * * * 0 0 0
// 0 * * * 0 0
// 0 0 * * * 0
// 0 0 0 * * *
// 0 0 0 0 * *

int n, m, x, y;
double mat[MAXN][MAXN], f[MAXN];

void fill() {
    mat[1][1] = 2;
    mat[1][2] = -1;
    mat[1][m + 1] = 3 + f[1];

    for (int i = 2; i < m; ++i) {
        mat[i][i] = 3;
        mat[i][i - 1] = -1;
        mat[i][i + 1] = -1;
        mat[i][m + 1] = 4 + f[i];
    }

    mat[m][m] = 2;
    mat[m][m - 1] = -1;
    mat[m][m + 1] = 3 + f[m];
}

void gauss() {
    for (int i = 1; i < m; ++i) {
        double rate = mat[i + 1][i] / mat[i][i];
        mat[i + 1][i] = 0;
        mat[i + 1][i + 1] -= rate * mat[i][i + 1];
        mat[i + 1][m + 1] -= rate * mat[i][m + 1];
    }

    mat[m][m + 1] /= mat[m][m];

    for (int i = m - 1; i >= 1; --i)
        mat[i][m + 1] = (mat[i][m + 1] - mat[i + 1][m + 1] * mat[i][i + 1]) / mat[i][i];
    
    for (int i = 1; i <= m; ++i)
        f[i] = mat[i][m + 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> x >> y;
    
    if (m == 1) {
        cout << 2 * (n - x) << endl;
        return 0;
    }

    for (int i = n - 1; i >= x; --i) {
        fill();
        gauss();
    }

    cout << setprecision(8) << f[y] << endl;
    return 0;
}