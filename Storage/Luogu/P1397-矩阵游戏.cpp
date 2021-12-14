#include <cstdio>
#include <initializer_list>
#include <cstring>
#include <vector>
using namespace std;

constexpr int mod = 1e9 + 7;

class Matrix {
public:
    Matrix(int r = 0, int c = 0) {
        row = r;
        column = c;

        for (int i = 0; i < row; ++i)
            for (int j = 0; j < column; ++j)
                data[i][j] = 0;
    }

    Matrix(int r, int c, initializer_list<initializer_list<int>> init) {
        row = r;
        column = c;

        int i = 0;

        for (auto l : init) {
            int j = 0;

            for (auto v : l) {
                data[i][j] = v;
                ++j;

                if (j == column)
                    break;
            }

            ++i;

            if (i == row)
                break;
        }
    }

    void init() {
        for (int i = 0; i < row; ++i)
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

        for (int i = 0; i < row; ++i)
            for (int j = 0; j < rhs.column; ++j)
                for (int k = 0; k < rhs.row; ++k)
                    res[i][j] = (res[i][j] + 1ll * data[i][k] * rhs[k][j] % mod) % mod;

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

    friend ostream &operator<<(ostream &os, const Matrix &mat) {
        for (int i = 0; i < mat.row; ++i, os << endl)
            for (int j = 0; j < mat.column; ++j)
                os << mat[i][j] << " ";

        return os;
    }
private:
    int data[3][3];
    int row, column;
};

char n[1000000 + 10], m[1000000 + 10];
int a, b, c, d;
int tmp[1000000 + 10];
Matrix power[10000];

Matrix pow(Matrix mat, char k[]) {
    int len = strlen(k + 1);

    for (int i = len; i >= 1; --i)
        tmp[len - i] = (k[i] - '0');

    for (int i = 0; i < len; ++i) {
        if (tmp[i] == 0) {
            tmp[i] = 9;
        } else {
            --tmp[i];
            break;
        }
    }

    Matrix res(3, 3);
    power[0] = Matrix(3, 3);
    power[0].init();

    for (int i = 1; i < 10000; ++i)
        power[i] = power[i - 1] * mat;

    res.init();
    int i;
    for (i = len - 1; i - 3 >= 0; i -= 4) {
        int v = tmp[i] * 1000 + tmp[i - 1] * 100 + tmp[i - 2] * 10 + tmp[i - 3];
        res = (res ^ 10000) * power[v];
    }

    if (i != -1) {
        int w = 1, v = 0;

        while (i != -1) {
            v = v * 10 + tmp[i];
            w *= 10;
            --i;
        }

        res = (res ^ w) * power[v];
    }

    return res;
}

int main() {
    scanf("%s%s%d%d%d%d", n + 1, m + 1, &a, &b, &c, &d);
    Matrix init(1, 3, {
        {1, b, d}
    });

    Matrix base1(3, 3, {
        {a, 0, 0},
        {1, 1, 0},
        {0, 0, 1}
    });


    Matrix base2(3, 3, {
        {c, 0, 0},
        {0, 1, 0},
        {1, 0, 1}
    });

    base1 = pow(base1, m);
    auto res = init * pow(base1 * base2, n) * base1;
    printf("%d\n", res[0][0]);
}