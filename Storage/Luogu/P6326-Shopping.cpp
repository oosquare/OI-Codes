#include <cstdio>
#include <vector>
using namespace std;

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();

    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            s = -1;

    for (; '0' <= c && c <= '9'; c = getchar())
        x = x * 10 + c - '0';

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

constexpr int maxn = 500 + 10;
constexpr int maxm = 4000 + 10;

int t, n, m;
int w[maxn], c[maxm], d[maxn];
vector<int> tree[maxn];
int sze[maxn], sze2[maxn], dfn[maxn], mdfn[maxn], rev[maxn], root, tot, timer;
bool vis[maxn];
int f[maxn][maxm], q[maxm], fr, bk, ans;

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void getRoot(int x, int fa) {
    sze[x] = 1;
    sze2[x] = 0;

    for (int y : tree[x]) {
        if (y == fa || vis[y])
            continue;

        getRoot(y, x);
        sze[x] += sze[y];
        sze2[x] = max(sze2[x], sze[y]);
    }

    sze2[x] = max(sze2[x], tot - sze[x]);

    if (!root || sze2[x] < sze2[root])
        root = x;
}

void dfs(int x, int fa) {
    dfn[x] = mdfn[x] = ++timer;
    rev[timer] = x;

    for (int y : tree[x]) {
        if (y == fa || vis[y])
            continue;

        dfs(y, x);
        mdfn[x] = mdfn[y];
    }
}

void solve(int x) {
    timer = 0;
    dfs(x, 0);
    dfn[timer + 1] = rev[timer + 1] = 0;
    vis[x] = true;

    for (int i = 0; i <= m; ++i)
        f[timer + 1][i] = 0;

    for (int i = timer; i >= 1; --i) {
        int u = rev[i];

        for (int j = 0; j <= m; ++j)
            f[i][j] = f[mdfn[u] + 1][j];

        for (int j = 0; j < c[u] && j < m; ++j) {
            fr = 1;
            bk = 0;

            for (int k = j; k <= m; k += c[u]) {
                while (fr <= bk && q[fr] < k - c[u] * d[u])
                    ++fr;

                if (fr <= bk)
                    f[i][k] = max(f[i][k], f[i + 1][q[fr]] + (k - q[fr]) / c[u] * w[u]);

                while (fr <= bk && f[i + 1][q[bk]] - (q[bk] - j) / c[u] * w[u] <= f[i + 1][k] - (k - j) / c[u] * w[u])
                    --bk;

                q[++bk] = k;
            }
        }
    }

    ans = max(ans, f[1][m]);

    for (int y : tree[x]) {
        if (vis[y])
            continue;

        root = 0;
        tot = sze[y];
        getRoot(y, 0);
        solve(root);
    }
}

int main() {
    sze2[0] = 0x3f3f3f3f;
    t = read();

    while (t--) {
        n = read(), m = read();

        for (int i = 1; i <= n; ++i)
            w[i] = read();

        for (int i = 1; i <= n; ++i)
            c[i] = read();

        for (int i = 1; i <= n; ++i)
            d[i] = read();

        for (int i = 1; i <= n; ++i) {
            tree[i].clear();
            vis[i] = false;
        }

        for (int i = 1; i < n; ++i) {
            int x = read(), y = read();
            link(x, y);
        }

        root = 0;
        tot = n;
        getRoot(1, 0);
        ans = 0;
        solve(root);
        write(ans);
    }

    return 0;
}