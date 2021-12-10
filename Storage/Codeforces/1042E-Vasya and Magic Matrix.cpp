#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();

    for (; c < '0' && c > '9'; c = getchar())
        if (c == '-')
            s = -1;

    for (; '0' <= c && c <= '9'; c = getchar())
        x = 10 * x + c - '0';

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
        x = -x;
        putchar('-');
    }

    while (x) {
        st[++top] = x % 10;
        x /= 10;
    }

    while (top)
        putchar(st[top--] + '0');

    putchar(sep);
}

constexpr int maxn = 1000000 + 10;
constexpr int mod = 998244353;

struct Node {
    int x, y, v;

    bool operator<(const Node &rhs) const {
        return v < rhs.v;
    }
};

int n, m, sx, sy;
Node point[maxn];
int f[maxn], sum[maxn], inv[maxn];
int sqrx[maxn], sqry[maxn], sumx[maxn], sumy[maxn];
vector<int> val, pos[maxn];

inline int id(int x, int y) {
    return (x - 1) * m + y;
}

void preprocess() {
    inv[1] = 1;

    for (int i = 2; i <= n * m; ++i)
        inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
}

int power(int x) {
    return 1ll * x * x % mod;
}

int main() {
    n = read(), m = read();
    preprocess();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int v = read();
            point[id(i, j)] = {i, j, v};
            val.push_back(v);
        }
    }

    sx = read(), sy = read();

    sort(point + 1, point + 1 + n * m);
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());

    for (int i = 1; i <= n * m; ++i) {
        point[i].v = lower_bound(val.begin(), val.end(), point[i].v) - val.begin() + 1;
        pos[point[i].v].push_back(i);
    }

    for (int i = 1, sze = 0; i <= (int)val.size(); ++i) {
        sumx[i] = sumx[i - 1];
        sumy[i] = sumy[i - 1];
        sqrx[i] = sqrx[i - 1];
        sqry[i] = sqry[i - 1];
        sum[i] = sum[i - 1];

        for (int t : pos[i]) {
            auto [x, y, v] = point[t];

            if (i != 1) {
                f[t] = (power(x) + power(y) + 1ll * sum[i - 1] * inv[sze] % mod) % mod;
                f[t] = (f[t] + 1ll * (sqrx[i - 1] + sqry[i - 1]) * inv[sze] % mod) % mod;
                f[t] = (f[t] - 2ll * x * sumx[i - 1] % mod * inv[sze] % mod + mod) % mod;
                f[t] = (f[t] - 2ll * y * sumy[i - 1] % mod * inv[sze] % mod + mod) % mod;
            }

            sumx[i] = (sumx[i] + x) % mod;
            sumy[i] = (sumy[i] + y) % mod;
            sqrx[i] = (sqrx[i] + power(x)) % mod;
            sqry[i] = (sqry[i] + power(y)) % mod;
            sum[i] = (sum[i] + f[t]) % mod;

            if (x == sx && y == sy) {
                write(f[t]);
                // return 0;
            }
        }

        sze += pos[i].size();
    }

    return 0;
}