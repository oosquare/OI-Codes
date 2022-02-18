#include <iostream>
using namespace std;

constexpr int MAX_M = 10 + 1;
constexpr int MOD = 9973;

class Matrix {
public:
    Matrix(int row = 0, int column = 0) {
        this->row = row;
        this->column = column;

        for (int i = 1; i <= row; ++i)
            for (int j = 1; j <= column; ++j)
                data[i][j] = 0;
    }

    void unit() {
        for (int i = 1; i <= row; ++i)
            for (int j = 1; j <= column; ++j)
                data[i][j] = (i == j);
    }

    int * operator[](int x) {
        return data[x];
    }

    const int * operator[](int x) const {
        return data[x];
    }

    Matrix operator*(const Matrix & rhs) const {
        Matrix res(row, rhs.column);

        for (int i = 1; i <= row; ++i)
            for (int j = 1; j <= rhs.column; ++j)
                for (int k = 1; k <= column; ++k)
                    res[i][j] = (res[i][j] + data[i][k] * rhs[k][j]) % MOD;

        return res;
    }

    Matrix operator^(int exp) const {
        Matrix res(row, row), base(*this);
        res.unit();

        for (; exp; exp /= 2) {
            if (exp % 2)
                res = res * base;

            base = base * base;
        }

        return res;
    }
private:
    int row, column;
    int data[MAX_M][MAX_M];
};

int t, n, m, k;
bool valid[MAX_M][MAX_M];

int power(int x, int y) {
    x %= MOD;
    int res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = res * x % MOD;

        x = x * x % MOD;
    }

    return res;
}

int phi(int x) {
    int res = x;

    for (int i = 2; i * i <= x; ++i) {
        if (x % i)
            continue;

        res = res / i * (i - 1);

        while (x % i == 0)
            x /= i;
    }

    if (x > 1)
        res = res / x * (x - 1);

    return res;
}

int dp(int t, int k) {
    Matrix f(1, m), trans(m, m);
    int res = 0;
    f[1][t] = 1;

    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= m; ++j)
            trans[j][i] = valid[i][j];

    f = f * (trans ^ (k - 1));

    for (int i = 1; i <= m; ++i)
        if (valid[t][i])
            res += f[1][i];

    return res % MOD;
}

int calc(int k) {
    int res = 0;

    for (int i = 1; i <= m; ++i)
        res += dp(i, k);

    return res % MOD;
}

int solve() {
    int ans = 0;

    for (int i = 1; i * i <= n; ++i) {
        if (n % i)
            continue;

        if (i * i == n) {
            ans = (ans + 1ll * calc(i) * phi(n / i)) % MOD;
        } else {
            ans = (ans + 1ll * calc(i) * phi(n / i)) % MOD;
            ans = (ans + 1ll * calc(n / i) * phi(i)) % MOD;
        }
    }

    return ans * power(n, MOD - 2) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> t;

    while (t--) {
        cin >> n >> m >> k;

        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= m; ++j)
                valid[i][j] = true;

        for (int i = 1; i <= k; ++i) {
            int x, y;
            cin >> x >> y;
            valid[x][y] = valid[y][x] = false;
        }

        cout << solve() << endl;
    }

    return 0;
}