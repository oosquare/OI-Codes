#include <cstdio>
#include <vector>
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

constexpr int maxn = 2e5 + 10;
constexpr int maxk = 5;

int n, k;
vector<int> tree[maxn];
long long f[2][maxn][5], g[2][maxn][5], ans;
int sze[maxn];

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void dfs1(int x, int fa) {
    sze[x] = 1;
    f[0][x][0] = 1;

    for (int y : tree[x]) {
        if (y == fa)
            continue;

        dfs1(y, x);
        sze[x] += sze[y];
        ans += 1ll * sze[y] * (n - sze[y]);

        for (int i = 0; i < k; ++i) {
            f[0][x][i] += f[0][y][(i - 1 + k) % k];
            g[0][x][i] += g[0][y][(i - 1 + k) % k];
        }

        g[0][x][1] += f[0][y][0];
    }
}

void dfs2(int x, int fa) {
    if (fa == 0) {
        for (int i = 0; i < k; ++i) {
            f[1][x][i] = f[0][x][i];
            g[1][x][i] = g[0][x][i];
        }
    }

    for (int y : tree[x]) {
        if (y == fa)
            continue;

        for (int i = 0; i < k; ++i) {
            f[1][y][i] = f[1][x][(i - 1 + k) % k] - f[0][y][(i - 2 + k) % k] + f[0][y][i];
            g[1][y][i] = g[1][x][(i - 1 + k) % k] - g[0][y][(i - 2 + k) % k] + g[0][y][i];

            if ((i - 1 + k) % k == 1)
                g[1][y][i] -= f[0][y][0];
        }

        g[1][y][1] += f[1][x][0] - f[0][y][k - 1];

        dfs2(y, x);
    }
}

int main() {
    n = read(), k = read();

    for (int i = 1; i < n; ++i) {
        int x = read(), y = read();
        link(x, y);
    }

    dfs1(1, 0);
    dfs2(1, 0);

    if (k == 1) {
        write(ans);
        return 0;
    }

    ans = 0;

    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < k; ++j)
            ans += g[1][i][j];

    write(ans / 2);
    return 0;
}