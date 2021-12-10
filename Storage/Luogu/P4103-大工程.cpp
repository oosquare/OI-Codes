#include <iostream>
#include <algorithm>

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

    static int st[21];
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
constexpr long long oo = 0x3f3f3f3f3f3f3f3f;

int n, q, k;
vector<pair<int, int>> tree[maxn], vtree[maxn];
int timer, dfn[maxn], dis[maxn], dep[maxn], step[maxn][21];
int st[maxn], top;
long long ans[3], sze[maxn], f[maxn][2], g[maxn][2];
int seq[maxn], selected[maxn], timer2;

void link(vector<pair<int, int>> tree[], int x, int y, int l = 1) {
    tree[x].push_back({y, l});
    tree[y].push_back({x, l});
}

void preprocess(int x, int fa) {
    dfn[x] = ++timer;
    dep[x] = dep[fa] + 1;

    for (int i = 1; i <= 20; ++i)
        step[x][i] = step[step[x][i - 1]][i - 1];

    for (auto [y, l] : tree[x]) {
        if (y == fa)
            continue;

        step[y][0] = x;
        dis[y] = dis[x] + l;
        preprocess(y, x);
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);

    for (int i = 20; i >= 0; --i) 
        if (dep[step[x][i]] >= dep[y])
            x = step[x][i];

    if (x == y)
        return x;

    for (int i = 20; i >= 0; --i) {
        if (step[x][i] != step[y][i]) {
            x = step[x][i];
            y = step[y][i];
        }
    }

    return step[x][0];
}

inline int distance(int x, int y) {
    if (dep[x] < dep[y])
        return dis[y] - dis[x];
    else
        return dis[x] - dis[y];
}

void build(int seq[], int tot) {
    sort(seq + 1, seq + 1 + tot, [](int lhs, int rhs) {
        return dfn[lhs] < dfn[rhs];
    });

    vtree[1].clear();
    st[top = 1] = 1;

    for (int i = 1; i <= tot; ++i) {
        if (seq[i] == 1)
            continue;

        int l = lca(seq[i], st[top]);

        if (l != st[top]) {
            while (dfn[l] < dfn[st[top - 1]]) {
                link(vtree, st[top], st[top - 1], distance(st[top], st[top - 1]));
                --top;
            }

            if (dfn[l] != dfn[st[top - 1]]) {
                vtree[l].clear();
                link(vtree, st[top], l, distance(st[top], l));
                st[top] = l;
            } else {
                link(vtree, st[top], l, distance(st[top], l));
                --top;
            }
        }

        vtree[seq[i]].clear();
        st[++top] = seq[i];
    }

    for (int i = 1; i < top; ++i)
        link(vtree, st[i], st[i + 1], distance(st[i], st[i + 1]));
}

void dfs(int x, int fa) {
    if (selected[x] == timer2) {
        sze[x] = 1;
        f[x][0] = 0;
        f[x][1] = oo;
        g[x][0] = 0;
        g[x][1] = -oo;
    } else {
        sze[x] = 0;
        f[x][0] = f[x][1] = oo;
        g[x][0] = g[x][1] = -oo;
    }

    for (auto [y, l] : vtree[x]) {
        if (y == fa)
            continue;

        dfs(y, x);
        sze[x] += sze[y];
        ans[0] += l * sze[y] * (k - sze[y]);

        if (f[x][0] >= f[y][0] + l)
            f[x][1] = exchange(f[x][0], f[y][0] + l);
        else if (f[x][1] > f[y][0] + l)
            f[x][1] = f[y][0] + l;

        if (g[x][0] <= g[y][0] + l)
            g[x][1] = exchange(g[x][0], g[y][0] + l);
        else if (g[x][1] < g[y][0] + l)
            g[x][1] = g[y][0] + l;
    }

    ans[1] = min(ans[1], f[x][0] + f[x][1]);
    ans[2] = max(ans[2], g[x][0] + g[x][1]);
}

int main() {
    n = read();

    for (int i = 1; i < n; ++i) {
        int a = read(), b = read();
        link(tree, a, b);
    }

    preprocess(1, 0);

    q = read();

    for (int i = 1; i <= q; ++i) {
        timer2 = i;
        k = read();

        for (int j = 1; j <= k; ++j) {
            int t = read();
            seq[j] = t;
            selected[t] = timer2;
        }

        build(seq, k);
        ans[0] = 0;
        ans[1] = oo;
        ans[2] = -oo;
        dfs(1, 0);
        write(ans[0], ' ');
        write(ans[1], ' ');
        write(ans[2]);
    }

    return 0;
}