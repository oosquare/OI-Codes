#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

template <typename T>
class Matrix {
public:
    Matrix(bool v) : vaild(v), mod(1) {}

    Matrix(int r = 0, int c = 0, T m = 1) : row(r), column(c), mod(m) {
        memset(data, 0, sizeof(data));
        vaild = m != 0;
    }

    T* operator[](int x) {
        return data[x];
    }

    Matrix<T> operator+(const Matrix<T>& r) {
        if (!vaild || !r.vaild || row != r.row && column != r.column)
            return Matrix<T>(false);
        Matrix<T> res = Matrix<T>(row, column, mod);
        for (int i = 0; i <= row; ++i) {
            for (int j = 0; j <= column; ++j) {
                res[i][j] = (data[i][j] + r.data[i][j]) % mod;
            }
        }
        return res;
    }

    Matrix<T> operator-(const Matrix<T>& r) {
        if (!vaild || !r.vaild || row != r.row && column != r.column)
            return Matrix<T>(false);
        Matrix<T> res = Matrix<T>(row, column, mod);
        for (int i = 0; i <= row; ++i) {
            for (int j = 0; j <= column; ++j) {
                res = (data[i][j] - r.data[i][j] + mod) % mod;
            }
        }
        return res;
    }

    Matrix<T> operator*(const Matrix<T>& r) {
        if (!vaild || !r.vaild || column != r.row)
            return Matrix<T>(false);
        Matrix<T> res = Matrix<T>(row, r.column, mod);
        for (int i = 0; i <= row; ++i) {
            for (int j = 0; j <= r.column; ++j) {
                for (int k = 0; k <= column; ++k) {
                    res[i][j] = (res[i][j] + data[i][k] * r.data[k][j]) % mod;
                }
            }
        }
        return res;
    }

    Matrix<T> operator^(T k) {
        if (row != column || !vaild)
            return Matrix<T>(false);
        Matrix<T> self = *this;
        Matrix<T> res = Matrix<T>(row, column, mod);
        for (int i = 0; i <= row; ++i)
            res[i][i] = 1;
        while (k) {
            if (k % 2 == 1)
                res = res * self;
            self = self * self;
            k /= 2;
        }
        return res;
    }
private:
    T data[3][3], mod;
    int row, column;
    bool vaild;
};

int n;
ll mod, g0, g1, g0g1;

ll get(int x) {
    if (x == 0)
        return 0;
    if (x == 1 || x == 2)
        return 1;
    Matrix<ll> a0(2, 2, mod), ans(1, 2, mod);
    a0[1][1] = 1, a0[1][2] = 1;
    a0[2][1] = 1, a0[2][2] = 0;
    ans[1][1] = 1, ans[1][2] = 1;
    ans = ans * (a0 ^ (x - 2));
    return ans[1][1];
}

ll square(ll x) {
    return x * x % mod;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("fib.in", "r", stdin);
    freopen("fib.out", "w", stdout);
#endif
    cin >> g0 >> g1 >> mod >> n;
    g0g1 = (ll)sqrt(3 + g0 * g1) % mod;
    if (n == 0) {
        cout << g0 << endl;
        return 0;
    }
    if (n == 1) {
        cout << g1 << endl;
        return 0;
    }
    ll ans1 = square(get(n - 1)) * g0 % mod;
    ll ans2 = square(get(n)) * g1 % mod;
    ll ans3 = (square(get(n)) + square(get(n - 1)) - square(get(n - 2)) + mod) % mod * g0g1 % mod;
    cout << (ans1 + ans2 + ans3) % mod << endl;
    return 0;
}
