#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 100 + 10;
constexpr int mod = 4147;

struct Matrix {
    int mat[maxn][maxn];
    int row, col;

    Matrix(int r = 0, int c = 0) : row(r), col(c) {
        memset(mat, 0, sizeof(mat));
    }

    int *operator[](int x) {
        return mat[x];
    }

    const int *operator[](int x) const {
        return mat[x];
    }

    void init() {
        for (int i = 1; i <= row; ++i)
            mat[i][i] = 1;
    }

    Matrix operator*(const Matrix &rhs) {
        Matrix res(row, rhs.col);

        for (int i = 1; i <= row; ++i)
            for (int j = 1; j <= rhs.col; ++j)
                for (int k = 1; k <= col; ++k)
                    res[i][j] = (res[i][j] + mat[i][k] * rhs[k][j]) % mod;

        return res;
    }

    Matrix operator^(int k) {
        Matrix res(row, row), x(*this);
        res.init();

        for (; k; k /= 2) {
            if (k % 2)
                res = res * x;
            x = x * x;
        }

        return res;
    }
};

int n, m;
int a[maxn], w[maxn];
Matrix base, ans;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = n; i >= 1; --i)
        cin >> w[i];

    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    base = Matrix(n, n);
    ans = Matrix(1, n);

    for (int i = 1; i <= n; ++i)
        ans[1][i] = w[n - i + 1];

    for (int i = 1; i <= n; ++i)
        base[i][1] = a[i];

    for (int i = 1; i < n; ++i)
        base[i][i + 1] = 1;

    ans = ans * (base ^ (m - n));
    cout << ans[1][1] << endl;

    return 0;
}