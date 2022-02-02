#include <iostream>
using namespace std;

long long n, m;

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

    long long *operator[](int x) {
        return data[x];
    }

    const long long *operator[](int x) const {
        return data[x];
    }

    Matrix operator*(const Matrix &rhs) const {
        Matrix res(row, rhs.column);

        for (int i = 1; i <= row; ++i)
            for (int j = 1; j <= rhs.column; ++j)
                for (int k = 1; k <= column; ++k)
                    res[i][j] = (res[i][j] + 1ll * data[i][k] * rhs[k][j]) % m;

        return res;
    }

    Matrix operator^(long long k) const {
        Matrix res(row, row), x(*this);
        res.init();

        for (; k; k /= 2) {
            if (k % 2)
                res = res * x;

            x = x * x;
        }

        return res;
    }

private:
    long long data[4][4];
    int row, column;
};

Matrix base(3, 3), res(1, 3);
long long power[20];

void preprocess() {
    power[0] = 1;

    for (int i = 1; i <= 18; ++i)
        power[i] = power[i - 1] * 10;
}

int main() {
    cin >> n >> m;
    preprocess();
    res[1][1] = 0, res[1][2] = 0, res[1][3] = 1;

    for (int i = 1; power[i - 1] <= n && i <= 19; ++i) {
        base[1][1] = power[i] % m, base[1][2] = 0, base[1][3] = 0;
        base[2][1] = 1, base[2][2] = 1, base[2][3] = 0;
        base[3][1] = 1, base[3][2] = 1, base[3][3] = 1;
        long long lim = (i == 19 ? n : min(1ll * n, power[i] - 1));
        res = res * (base ^ (lim - power[i - 1] + 1));
    }

    cout << res[1][1] << endl;
    return 0;
}