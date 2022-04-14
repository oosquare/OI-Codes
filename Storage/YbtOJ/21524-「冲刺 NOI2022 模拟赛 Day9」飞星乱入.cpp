#include <iostream>

constexpr int MAX_N = 1000 + 10;

int p;

class Matrix {
public:
    void set(int row, int column) {
        this->row = row;
        this->column = column;
    }

    int * operator[](int x) {
        return data[x];
    }

    const int * operator[](int x) const {
        return data[x];
    }
    
    Matrix operator*(int x) {
        Matrix res(*this);

        for (int i = 1; i <= row; ++i)
            for (int j = 1; j <= column; ++j)
                res[i][j] = (int) (1ll * res[i][j] * x % p);

        return res;
    }

    Matrix operator+(const Matrix & rhs) {
        Matrix res(*this);
        
        for (int i = 1; i <= row; ++i)
            for (int j = 1; j <= column; ++j)
                res[i][j] = (res[i][j] + rhs[i][j]) % p;

        return res;
    }
private:
    int data[MAX_N][MAX_N];
    int row, column;
};

int n, t;
int sum;
int sumx[MAX_N], sumy[MAX_N];
Matrix mat, h, r, res;

int power(int x, int y) {
    int res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = (int) (1ll * res * x % p);

        x = (int) (1ll * x * x % p);
    }

    return res;
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("matrix.in", "r", stdin);
    std::freopen("matrix.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);

    std::cin >> n >> t >> p;
    mat.set(n, n);
    h.set(n, n);
    r.set(n, n);
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cin >> mat[i][j];
            mat[i][j] %= p;
            sum = (sum + mat[i][j]) % p;
        }
    }

    if (t == 0) {
        for (int i = 1; i <= n; ++i, std::cout << std::endl)
            for (int j = 1; j <= n; ++j)
                std::cout << mat[i][j] << " ";

        return 0;
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            h[i][j] = sum;
    
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            sumx[i] = (sumx[i] + mat[i][j]) % p;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            sumy[j] = (sumy[j] + mat[i][j]) % p;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            r[i][j] = (sumx[i] + sumy[j]) % p;

    int c1 = (int) (1ll * (power(2, t) - 2 + p) % p * power(n, t - 2) % p);
    int c2 = power(n, t - 1);

    res = h * c1 + r * c2;

    for (int i = 1; i <= n; ++i, std::cout << std::endl)
        for (int j = 1; j <= n; ++j)
            std::cout << res[i][j] << " ";

    return 0;
}
