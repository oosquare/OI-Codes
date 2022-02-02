#include <iostream>
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

constexpr int maxn = 1e5 + 10;

class Tree {
public:
    void link(int x, int y) {
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    void preprocess() {
        dfs(1);
        dfs(1, 1);
    }

    int lca(int x, int y) {
        int fx = top[x], fy = top[y];

        while (fx != fy) {
            if (dep[fx] > dep[fy]) {
                x = fa[fx];
                fx = top[x];
            } else {
                y = fa[fy];
                fy = top[y];
            }
        }

        return (dep[x] < dep[y] ? x : y);
    }

    int distance(int x, int y) {
        return dep[x] + dep[y] - 2 * dep[lca(x, y)];
    }

    void clear(int n) {
        for (int i = 1; i <= n; ++i)
            tree[i].clear();
    }

    vector<int> &operator[](int x) {
        return tree[x];
    }

private:
    vector<int> tree[maxn];
    int size[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];

    void dfs(int x) {
        dep[x] = dep[fa[x]] + 1;
        size[x] = 1;
        son[x] = 0;

        for (int y : tree[x]) {
            if (y == fa[x])
                continue;

            fa[y] = x;
            dfs(y);
            size[x] += size[y];

            if (size[y] > size[son[x]])
                son[x] = y;
        }
    }

    void dfs(int x, int t) {
        top[x] = t;

        if (son[x])
            dfs(son[x], t);

        for (int y : tree[x]) {
            if (y == fa[x] || y == son[x])
                continue;

            dfs(y, y);
        }
    }
};

int t, n, m;
Tree tree;
int tot, root, sze[maxn], sze2[maxn], dep[maxn];
bool vis[maxn];
int fa[maxn];
vector<int> f1[maxn], f2[maxn];

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

    if (!root || sze2[root] > sze2[x])
        root = x;
}

void getSize(int x, int fa) {
    sze[x] = 1;

    for (int y : tree[x]) {
        if (y == fa || vis[y])
            continue;

        getSize(y, x);
        sze[x] += sze[y];
    }
}

void build(int x) {
    vis[x] = true;
    getSize(x, 0);
    f1[x] = vector<int>(sze[x] + 5);
    f2[x] = vector<int>(sze[x] + 5);

    for (int y : tree[x]) {
        if (vis[y])
            continue;

        tot = sze[y];
        root = 0;
        getRoot(y, x);
        fa[root] = x;
        build(root);
    }
}

void init(int x0) {
    ++f1[x0][0];

    for (int x = x0; fa[x]; x = fa[x]) {
        int d = tree.distance(x0, fa[x]);
        ++f1[fa[x]][d];
        ++f2[x][d];
    }
}

int query(int x0, int k) {
    int res = 0;

    if (k < (int)f1[x0].size())
        res += f1[x0][k];

    for (int x = x0; fa[x]; x = fa[x]) {
        int k2 = k - tree.distance(x0, fa[x]);

        if (0 <= k2 && k2 < (int)f1[fa[x]].size())
            res += f1[fa[x]][k2];

        if (0 <= k2 && k2 < (int)f2[x].size())
            res -= f2[x][k2];
    }

    return res;
}

void solve() {
    n = read(), m = read();
    tree.clear(n);

    for (int i = 1; i <= n; ++i)
        vis[i] = false;

    for (int i = 1, x, y; i < n; ++i) {
        x = read(), y = read();
        tree.link(x, y);
    }

    tree.preprocess();

    tot = n;
    root = 0;
    getRoot(1, 0);
    fa[root] = 0;
    build(root);

    for (int i = 1; i <= n; ++i)
        init(i);

    for (int i = 1, x, k; i <= m; ++i) {
        x = read(), k = read();
        write(query(x, k));
    }
}

int main() {
    t = read();

    while (t--)
        solve();

    return 0;
}
