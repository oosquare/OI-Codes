#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>
#include <vector>
using namespace std;

using ll = long long;

ll n, m;
ll p, q, r, t, u, v, w, x, y, z;

ll multiply(ll x, ll y) {
    ll res = 0;

    for (; y; y /= 2) {
        if (y % 2)
            res = (res + x) % m;

        x = (x + x) % m;
    }

    return res;
}

class Matrix {
public:
    Matrix(int r = 0, int c = 0) : row(r), col(c) {
        memset(mat, 0, sizeof(mat));
    }

    void set(int r, int c, vector<vector<ll>> l) {
        row = r;
        col = c;

        for (int i = 1; i <= r; ++i)
            for (int j = 1; j <= c; ++j)
                mat[i][j] = l[i - 1][j - 1];
    }

    ll *operator[](int x) {
        return mat[x];
    }

    const ll *operator[](int x) const {
        return mat[x];
    }

    Matrix operator*(const Matrix &rhs) const {
        Matrix res(row, rhs.col);

        for (int i = 1; i <= row; ++i)
            for (int j = 1; j <= rhs.col; ++j)
                for (int k = 1; k <= col; ++k)
                    res[i][j] = (res[i][j] + multiply(mat[i][k], rhs[k][j])) % m;

        return res;
    }

    Matrix operator^(ll k) const {
        Matrix res(row, col), base = *this;

        for (int i = 1; i <= row; ++i)
            res[i][i] = 1;

        for (; k; k /= 2) {
            if (k % 2)
                res = res * base;

            base = base * base;
        }

        return res;
    }
private:
    ll mat[12][12];
    int row, col;
};

Matrix ans, base;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    cin >> p >> q >> r >> t;
    cin >> u >> v >> w;
    cin >> x >> y >> z;

    if (n == 1) {
        cout << "nodgd 1" << endl;
        cout << "Ciocio 1" << endl;
        cout << "Nicole 1" << endl;
        return 0;
    } else if (n == 2) {
        cout << "nodgd 3" << endl;
        cout << "Ciocio 3" << endl;
        cout << "Nicole 3" << endl;
        return 0;
    }

    ans.set(1, 11, {
        {3, 1, 3, 1, 3, 1, 0, 1, 1, 0, 1}
    });

    base.set(11, 11, {
        {p, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0},
        {q, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, u, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, v, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, x, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, y, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, w, 0, 0, 0, 0, w, 0, 0, 0},
        {0, 0, 0, 0, z, 0, 0, 0, z, 0, 0},
        {(2 * r + t) % m, 0, 0, 0, 1, 0, 2 * r % m, 0, 0, 1, 0},
        {(t + r + 1) % m, 0, 0, 0, 3, 0, r, 0, 0, 1, 1}
    });

    ans = ans * (base ^ (n - 2));
    cout << "nodgd " << ans[1][1] << endl;
    cout << "Ciocio " << ans[1][3] << endl;
    cout << "Nicole " << ans[1][5] << endl;
    return 0;
}