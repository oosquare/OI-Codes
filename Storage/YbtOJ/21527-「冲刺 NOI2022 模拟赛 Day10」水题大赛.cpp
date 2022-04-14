#include <iostream>

constexpr int MOD = 19491001;

class Matrix {
public:
    Matrix(int row = 0, int column = 0) {
        this->row = row;
        this->column = column;
        
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < column; ++j)
                data[i][j] = 0;
    }

    void unit() {
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
                for (int k = 0; k < column; ++k)
                    res[i][j] = (res[i][j] + 1ll * data[i][k] * rhs[k][j] % MOD) % MOD;

        return res;
    }

    Matrix operator^(long long expo) {
        Matrix res(row, column), base(*this);
        res.unit();

        for (; expo; expo /= 2) {
            if (expo % 2)
                res = res * base;
            
            base = base * base;
        }

        return res;
    }
private:
    int row, column;
    int data[2][2];
};

long long n;
Matrix init(1, 2), trans(2, 2);

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("water.in", "r", stdin);
    std::freopen("water.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::cin >> n;

    if (n == 1) {
        std::cout << 0 << std::endl;
        return 0;
    }

    --n;

    init[0][0] = 1, init[0][1] = 1;

    trans[0][0] = 1, trans[0][1] = 1;
    trans[1][0] = 1, trans[1][1] = 0;

    Matrix res = init * (trans ^ (n - 1));
    std::cout << ((res[0][0] + res[0][1]) % MOD - 1 + MOD) % MOD;

    return 0;
}
