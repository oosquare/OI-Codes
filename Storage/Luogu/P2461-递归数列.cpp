#include <iostream>
using namespace std;
#define int long long

long long p;

template <typename T> class Matrix {
public:
    Matrix(int r = 0, int c = 0) {
        row = r;
        column = c;

        for (int i = 1; i <= r; ++i)
            for (int j = 1; j <= c; ++j)
                data[i][j] = 0;
    }

    void init() {
        for (int i = 1; i <= row; ++i)
            data[i][i] = 1;
    }

    T *operator[](int x) {
        return data[x];
    }

    const T *operator[](int x) const {
        return data[x];
    }

    Matrix<T> operator*(const Matrix &rhs) const {
        Matrix<T> res(row, column);

        for (int i = 1; i <= row; ++i)
            for (int j = 1; j <= rhs.column; ++j)
                for (int k = 1; k <= rhs.row; ++k)
                    res[i][j] = (res[i][j] + 1ll * data[i][k] * rhs[k][j] % p) % p;

        return res;
    }

    Matrix<T> operator^(T k) const {
        Matrix<T> res(row, row), x(*this);
        res.init();

        for (; k; k /= 2) {
            if (k % 2)
                res = res * x;

            x = x * x;
        }

        return res;
    }
private:
    T data[20][20];
    int row, column;  
};

long long n, m;
long long k, b[20], c[20];

long long calc(long long x) {
    if (x <= k) {
        long long sum = 0;

        for (int i = 1; i <= x; ++i)
            sum = (sum + b[i]) % p;

        return sum;
    }

    Matrix<long long> init(1, k + 1), base(k + 1, k + 1);

    for (int i = 1; i <= k; ++i)
        init[1][k - i + 1] = b[i];

    for (int i = 1; i <= k; ++i)
        init[1][k + 1] = (init[1][k + 1] + b[i]) % p;

    for (int i = 1; i <= k; ++i)
        base[i][1] = c[i];

    for (int i = 2; i <= k; ++i)
        base[i - 1][i] = 1;

    for (int i = 1; i <= k; ++i)
        base[i][k + 1] = c[i];

    base[k + 1][k + 1] = 1;
    return (init * (base ^ (x - k)))[1][k + 1];
}

signed main() {
    ios::sync_with_stdio(false);
    cin >> k;

    for (int i = 1; i <= k; ++i)
        cin >> b[i];

    for (int i = 1; i <= k; ++i)
        cin >> c[i];

    cin >> m >> n >> p;
    cout << (calc(n) - calc(m - 1) + p) % p << endl;
    return 0;
}