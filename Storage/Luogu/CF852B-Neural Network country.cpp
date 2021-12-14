#include <cstdio>
#include <iostream>
using namespace std;

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();

    for (; c < '0' || '9' < c; c = getchar())
        if (c == '-')
            s = -1;

    for (; '0' <= c && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + c - '0';

    return x * s;
}

template <typename T> void write(T x, char sep = '\n') {
    if (x == 0) {
        putchar('0');
        putchar(sep);
        return;
    }

    static int st[50];
    int top = 0;

    if (x < 0) {
        putchar('-');
        x = -x;
    }

    while (x) {
        st[++top] = x % 10;
        x /= 10;
    }

    while (top)
        putchar(st[top--] + '0');

    putchar(sep);
}

constexpr int maxn = 1e6 + 10;
constexpr int maxm = 100;
constexpr int mod = 1e9 + 7;

class Matrix {
public:
    Matrix(int r = 0, int c = 0) {
        row = r;
        column = c;

        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                data[i][j] = 0;
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

    Matrix operator^(int k) const {
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
    int data[maxm][maxm];
    int row, column;
};

int n, l, m, ans;
int vv[maxn], cnt[maxm];
Matrix init, base;

int main() {
    n = read(), l = read(), m = read();
    init = Matrix(1, m);
    base = Matrix(m, m);

    for (int i = 1; i <= n; ++i) {
        int v = read();
        v %= m;
        ++init[0][v];
    }

    for (int i = 1; i <= n; ++i) {
        int v = read();
        v %= m;
        ++cnt[v];
        vv[i] = v;
    }

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < m; ++j)
            base[(i - j + m) % m][i] = cnt[j];

    Matrix res = init * (base ^ (l - 2));

    for (int i = 1; i <= n; ++i) {
        int v = read();
        v %= m;
        ans = (ans + res[0][(m - v - vv[i] + m) % m]) % mod;
    }

    write(ans);
    return 0;
}