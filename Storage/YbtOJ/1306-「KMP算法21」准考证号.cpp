#include <bits/stdc++.h>
using namespace std;

constexpr int maxm = 25;

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
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                res[i][j] = (data[i][j] + r.data[i][j]) % mod;
            }
        }
        return res;
    }

    Matrix<T> operator-(const Matrix<T>& r) {
        if (!vaild || !r.vaild || row != r.row && column != r.column)
            return Matrix<T>(false);
        Matrix<T> res = Matrix<T>(row, column, mod);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                res = (data[i][j] - r.data[i][j] + mod) % mod;
            }
        }
        return res;
    }

    Matrix<T> operator*(const Matrix<T>& r) {
        if (!vaild || !r.vaild || column != r.row)
            return Matrix<T>(false);
        Matrix<T> res = Matrix<T>(row, r.column, mod);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < r.column; ++j) {
                for (int k = 0; k < column; ++k) {
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
        for (int i = 0; i < row; ++i)
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
    T data[21][21], mod;
    int row, column;
    bool vaild;
};

int n, m, k;
int fail[maxm];
char str[maxm];

Matrix<int> getmatrix() {
	fail[1] = 0;
	for (int i = 2, j = 0; i <= m; ++i) {
		while (j && str[j + 1] != str[i])
			j = fail[j];
		if (str[j + 1] == str[i])
			++j;
		fail[i] = j;
	}
	Matrix<int> mat(m, m, k);
	for (int i = 0; i < m; ++i) {
		for (char c = '0'; c <= '9'; ++c) {
			int j = i;
			while (j && str[j + 1] != c)
				j = fail[j];
			if (str[j + 1] == c)
				++j;
			++mat[i][j];
		}
	}
	return mat;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
#endif
	cin >> n >> m >> k >> (str + 1);
	auto mat = getmatrix();
	mat = mat ^ n;
	int ans = 0;
	for (int i = 0; i < m; ++i)
		ans = (ans + mat[0][i]) % k;
	cout << ans << endl;
}
