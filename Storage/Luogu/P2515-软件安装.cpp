#include <cstdio>
#include <vector>
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

constexpr int maxn = 100 + 10;
constexpr int maxm = 500 + 10;

int n, m, w[maxn], v[maxn];
vector<int> graph[maxn], tree[maxn];
int timer, uuid, dfn[maxn], low[maxn], idx[maxn], ww[maxn], vv[maxn];
int st[maxn], top, in[maxn];
int lim[maxn], f[maxn][maxm], tmp[maxm];
bool vis[maxn], mat[maxn][maxn];

void link(vector<int> graph[], int x, int y) {
    graph[x].push_back(y);
}

void tarjan(int x) {
    dfn[x] = low[x] = ++timer;
    st[++top] = x;
    vis[x] = true;

    for (int y : graph[x]) {
        if (!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        } else if (vis[y]) {
            low[x] = min(low[x], dfn[y]);
        }
    }

    if (dfn[x] == low[x]) {
        ++uuid;
        idx[x] = uuid;
        vis[x] = false;

        while (st[top] != x) {
            idx[st[top]] = uuid;
            vis[st[top]] = false;
            --top;
        }

        --top;
    }
}

void dfs(int x) {
    for (int i = ww[x]; i <= m; ++i)
        f[x][i] = vv[x];

    for (int y : tree[x]) {
        dfs(y);

        for (int i = m - ww[x]; i >= 0; --i)
            for (int j = 0; j <= i; ++j)
                f[x][i + ww[x]] = max(f[x][i + ww[x]], f[y][j] + f[x][i + ww[x] - j]);
    }
}

int main() {
    n = read(), m = read();

    for (int i = 1; i <= n; ++i)
        w[i] = read();

    for (int i = 1; i <= n; ++i)
        v[i] = read();

    for (int i = 1; i <= n; ++i) {
        int d = read();

        if (d)
            link(graph, d, i);
    }

    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);

    for (int i = 1; i <= n; ++i) {
        ww[idx[i]] += w[i];
        vv[idx[i]] += v[i];
    }

    for (int x = 1; x <= n; ++x) {
        for (int y : graph[x]) {
            if (idx[x] == idx[y])
                continue;

            mat[idx[x]][idx[y]] = true;
            ++in[idx[y]];
        }
    }

    for (int i = 1; i <= uuid; ++i)
        for (int j = 1; j <= uuid; ++j)
            if (mat[i][j])
                link(tree, i, j);

    for (int i = 1; i <= uuid; ++i)
        if (!in[i])
            link(tree, 0, i);

    dfs(0);
    write(f[0][m]);
    return 0;
}