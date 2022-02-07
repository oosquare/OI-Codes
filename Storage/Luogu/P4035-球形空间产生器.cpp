#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

constexpr int MAXN = 10 + 5;

int n;
double pos[MAXN][MAXN], mat[MAXN][MAXN];

void preprocess() {
    for (int i = 1; i <= n + 1; ++i) {
        double sum = 0;

        for (int j = 1; j <= n; ++j) {
            mat[i][j] = 2 * pos[i][j];
            sum += pos[i][j] * pos[i][j];
        }
        
        mat[i][n + 1] = 1;
        mat[i][n + 2] = sum;
    }
}

void transform(int n) {
    for (int i = 1; i <= n; ++i) {
        int p = i;

        for (int j = i + 1; j <= n; ++j)
            if (abs(mat[p][i]) < abs(mat[j][i]))
                p = j;
        
        if (i != p)
            for (int j = 1; j <= n + 1; ++j)
                swap(mat[i][j], mat[p][j]);

        for (int j = i + 1; j <= n; ++j) {
            double rate = mat[j][i] / mat[i][i];

            for (int k = i; k <= n + 1; ++k)
                mat[j][k] -= rate * mat[i][k];
        }
    }
}

void calc(int n) {
    for (int i = n; i >= 1; --i) {
        for (int j = i + 1; j <= n; ++j)
            mat[i][n + 1] -= mat[i][j] * mat[j][n + 1];
        
        mat[i][n + 1] /= mat[i][i];
    }
}

void gauss(int n) {
    transform(n);
    calc(n);
}

int main() {
    ios::sync_with_stdio(false);

    cin >> n;

    for (int i = 1; i <= n + 1; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> pos[i][j];

    preprocess();
    gauss(n + 1);

    for (int i = 1; i <= n; ++i)
        cout << fixed << setprecision(3) << mat[i][n + 2] << " ";

    cout << endl;
    return 0;
}