#include <iostream>
#include <vector>

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

constexpr int MAX_N = 200000 + 10;

class Tree {
public:
    void link(int x, int y) {
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    void preprocess(int root) {
        dfs(root, 0);
    }

    int lca(int x, int y) {
        if (dep[x] < dep[y])
            std::swap(x, y);

        for (int i = 18; i >= 0; --i)
            if (dep[step[x][i]] >= dep[y])
                x = step[x][i];

        if (x == y)
            return x;

        for (int i = 18; i >= 0; --i) {
            if (step[x][i] != step[y][i]) {
                x = step[x][i];
                y = step[y][i];
            }
        }

        return step[x][0];
    }

    int distance(int x, int y) {
        return dep[x] + dep[y] - 2 * dep[lca(x, y)];
    }

    int jump(int x, int dis) {
        for (int i = 18; i >= 0; --i)
            if ((dis >> i) & 1)
                x = step[x][i];

        return x;
    }

    int depth(int x) {
        return dep[x];
    }

    int father(int x) {
        return step[x][0];
    }

    std::vector<int> &operator[](int x) {
        return tree[x];
    }
private:
    std::vector<int> tree[MAX_N];
    int dep[MAX_N], step[MAX_N][19];

    void dfs(int x, int fa) {
        dep[x] = dep[fa] + 1;

        for (int i = 1; i <= 18; ++i)
            step[x][i] = step[step[x][i - 1]][i - 1];

        for (int y : tree[x]) {
            if (y == fa)
                continue;

            step[y][0] = x;
            dfs(y, x);
        }
    }
};
struct BinaryIndexedTree {
    std::vector<int> arr;
    int size;

    void init(int s) {
        size = s;
        arr.clear();
        arr = std::vector<int>(size + 3);
    }

    int lowbit(int x) {
        return x & (-x);
    }

    void add(int p, int v) {
        ++p;

        if (p > size + 1)
            return;

        for (; p <= size + 1; p += lowbit(p))
            arr[p] += v;
    }

    int query(int p) {
        p = std::min(p + 1, size + 1);
        int res = 0;

        for (; p; p -= lowbit(p))
            res += arr[p];

        return res;
    }
};
// class BinaryIndexedTree {
// public:
//     void init(int len) {
//         this->len = len + 1;
//         arr.reserve((unsigned long) len + 3);
//     }

//     void add(int x, int y) {
//         for (++x; x <= len; x += lowbit(x))
//             arr[(unsigned long) x] += y;
//     }

//     int query(int x) {
//         int res = 0;

//         for (x = std::min(x + 1, len); x; x -= lowbit(x))
//             res += arr[(unsigned long) x];

//         return res;
//     }
// private:
//     std::vector<int> arr;
//     int len;

//     int lowbit(int x) {
//         return x & (-x);
//     }
// };

int n, m;
int root, tot, sze[MAX_N], sze2[MAX_N];
bool vis[MAX_N];
Tree tree, vtree;
BinaryIndexedTree bit[MAX_N], bit2[MAX_N];
int ans;

void getRoot(int x, int fa) {
    sze[x] = 1;
    sze2[x] = 0;

    for (int y : tree[x]) {
        if (vis[y] || y == fa)
            continue;

        getRoot(y, x);
        sze[x] += sze[y];
        sze2[x] = std::max(sze2[x], sze[y]);
    }

    sze2[x] = std::max(sze2[x], tot - sze[x]);

    if (!root || sze2[root] > sze2[x])
        root = x;
}

void getSize(int x, int fa) {
    sze[x] = 1;

    for (int y : tree[x]) {
        if (vis[y] || y == fa)
            continue;

        getSize(y, x);
        sze[x] += sze[y];
    }
}

void build(int x) {
    vis[x] = true;
    getSize(x, 0);
    bit[x].init(sze[x]);
    bit2[x].init(sze[x]);

    for (int y : tree[x]) {
        if (vis[y])
            continue;

        root = 0;
        tot = sze[y];
        getRoot(y, x);
        vtree.link(x, root);
        build(root);
    }
}

void add(int x0) {
    bit[x0].add(0, 1);

    for (int x = x0, fa; fa = vtree.father(x), fa; x = fa) {
        int d = tree.distance(fa, x0);
        bit[fa].add(d, 1);
        bit2[x].add(d, 1);
    }
}

int query(int x0, int k) {
    if (k < 0)
        return 0;

    int res = bit[x0].query(k);
    
    for (int x = x0, fa; fa = vtree.father(x), fa; x = fa) {
        int d = k - tree.distance(fa, x0);

        if (d < 0)
            continue;

        res += bit[fa].query(d) - bit2[x].query(d);
    }

    return res;
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("tree.in", "r", stdin);
    std::freopen("tree.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    n = read(), m = read();
    
    for (int i = 1; i < n; ++i) {
        int x = read(), y = read();
        tree.link(x, n + i);
        tree.link(n + i, y);
    }

    tree.preprocess(1);
    tot = 2 * n - 1;
    getRoot(1, 0);
    int nroot = root;
    build(root);
    vtree.preprocess(nroot);

    for (int i = 1; i <= n; ++i)
        add(i);
        
    for (int i = 1; i <= m; ++i) {
        int x = read(), y = read(), w = read();
        x = (x + ans) % n + 1;
        y = (y + ans) % n + 1;
        w = ((w + ans) % n) * 2;
        int d = tree.distance(x, y);
        int mid = (tree.depth(x) > tree.depth(y)
            ? tree.jump(x, d / 2)
            : tree.jump(y, d / 2));
        ans = query(x, w) + query(y, w) - query(mid, w - d / 2);
        printf("%d\n", ans);
    }

    return 0;
}
