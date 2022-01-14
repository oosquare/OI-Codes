#include <iostream>
using namespace std;

constexpr int mod = 1e9 + 7;

class Matrix {
public:
    Matrix(int row = 0, int column = 0) {
        this->row = row;
        this->column = column;

        for (int i = 1; i <= row; ++i)
            for (int j = 1; j <= column; ++j)
                data[i][j] = 0;
    }

    void init() {
        for (int i = 1; i <= row; ++i)
            data[i][i] = 1;
    }

    int *operator[](int x) {
        return data[x];
    }

    const int *operator[](int x) const {
        return data[x];
    }

    Matrix operator*(const Matrix &rhs) const {
        Matrix res(row, rhs.column);

        for (int i = 1; i <= row; ++i)
            for (int j = 1; j <= rhs.column; ++j)
                for (int k = 1; k <= column; ++k)
                    res[i][j] = (res[i][j] + 1ll * data[i][k] * rhs[k][j]) % mod;

        return res;
    }

    Matrix operator^(long long k) const {
        Matrix res(row, column), x(*this);
        res.init();

        for (; k; k /= 2) {
            if (k % 2)
                res = res * x;

            x = x * x;
        }

        return res;
    }

private:
    int data[3][3];
    int row, column;
};

int t;
long long n;

int solve(long long k) {
    if (k == 0)
        return 0;
    
    if (k == 1)
        return 2;

    Matrix base(2, 2), res(1, 2);
    base[1][1] = 1, base[1][2] = 1;
    base[2][1] = 1, base[2][2] = 0;
    res[1][1] = 1, res[1][2] = 1;
    res = res * (base ^ k);
    return (res[1][1] + res[1][2]) % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> t;

    while (t--) {
        cin >> n;
        cout << solve(n) << endl;
    }

    return 0;
}