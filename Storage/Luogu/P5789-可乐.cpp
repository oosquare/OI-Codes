#include <bits/stdc++.h>
using namespace std;

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T = int>
T read() {
    T x = 0, s = 1;
    char c = mygetchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = mygetchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = mygetchar();
    }
    return x * s;
}

typedef long long ll;

template <typename T>
class Matrix {
public:
    Matrix(bool v) : Vaild(v), Mod(1) {}

    Matrix(int r = 0, int c = 0, T m = 1) : Row(r), Col(c), Mod(m) {
        memset(Data, 0, sizeof(Data));
        Vaild = m != 0;
    }

    T* operator[](int x) {
        return Data[x];
    }

    Matrix<T> operator+(const Matrix<T>& r) {
        if (!Vaild || !r.Vaild || Row != r.Row && Col != r.Col)
            return Matrix<T>(false);
        Matrix<T> res = Matrix<T>(Row, Col, Mod);
        for (int i = 0; i <= Row; ++i) {
            for (int j = 0; j <= Col; ++j) {
                res[i][j] = (Data[i][j] + r.Data[i][j]) % Mod;
            }
        }
        return res;
    }

    Matrix<T> operator-(const Matrix<T>& r) {
        if (!Vaild || !r.Vaild || Row != r.Row && Col != r.Col)
            return Matrix<T>(false);
        Matrix<T> res = Matrix<T>(Row, Col, Mod);
        for (int i = 0; i <= Row; ++i) {
            for (int j = 0; j <= Col; ++j) {
                res = (Data[i][j] - r.Data[i][j] + Mod) % Mod;
            }
        }
        return res;
    }

    Matrix<T> operator*(const Matrix<T>& r) {
        if (!Vaild || !r.Vaild || Col != r.Row)
            return Matrix<T>(false);
        Matrix<T> res = Matrix<T>(Row, r.Col, Mod);
        for (int i = 0; i <= Row; ++i) {
            for (int j = 0; j <= r.Col; ++j) {
                for (int k = 0; k <= Col; ++k) {
                    res[i][j] = (res[i][j] + Data[i][k] * r.Data[k][j]) % Mod;
                }
            }
        }
        return res;
    }

    Matrix<T> operator^(T k) {
        if (Row != Col || !Vaild)
            return Matrix<T>(false);
        Matrix<T> self = *this;
        Matrix<T> res = Matrix<T>(Row, Col, Mod);
        for (int i = 0; i <= Row; ++i)
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
    T Data[105][105], Mod;
    int Row, Col;
    bool Vaild;
};

int n, m, t;
Matrix<ll> mat;

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read();
    m = read();
    mat = Matrix<ll>(n, n, 2017);
    for (int i = 1; i <= m; ++i) {
        int x = read(), y = read();
        mat[x][y] = mat[y][x] = 1;
    }
    for (int i = 0; i <= n; ++i)
        mat[i][i] = 1;
    for (int i = 1; i <= n; ++i)
        mat[i][0] = 1;
    t = read();
    Matrix<ll> res = mat ^ t;
    ll ans = 0;
    for (int i = 0; i <= n; ++i)
        ans = (ans + res[1][i]) % 2017;
    printf("%lld\n", ans);
    return 0;
}