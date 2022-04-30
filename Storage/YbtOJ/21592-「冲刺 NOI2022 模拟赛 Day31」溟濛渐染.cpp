#include <iostream>
#include <vector>

const int MAX_N = 400100;

inline long long square(long long x) {
    return x * x;
}

class LinkCutTree {
public:
    LinkCutTree() : ans(0) {}

    void init(int x, int fa = 0) {
        up[x] = fa;
        tree[x].ls = tree[x].rs = tree[x].fa = 0;
        tree[x].size = 1;
        tree[x].sum = tree[x].sqr = 0;
    }

    void link(int x) {
        int y = up[x];
        splay(x);
        ans -= tree[x].sqr + square(tree[tree[x].rs].size);

        int z = find_root(y);
        access(x);
        splay(z);
        ans -= square(tree[tree[z].rs].size);

        tree[x].fa = y;
        splay(y);
        tree[y].sum += tree[x].size;
        tree[y].sqr += square(tree[x].size);
        pushup(y);
        access(x);

        splay(z);
        ans += square(tree[tree[z].rs].size);
    }

    void cut(int x) {
        int y = up[x];
        access(x);
        ans += tree[x].sqr;

        int z = find_root(y);
        access(x);
        splay(z);
        ans -= square(tree[tree[z].rs].size);

        splay(x);
        tree[x].ls = tree[tree[x].ls].fa = 0;
        pushup(x);

        splay(z);
        ans += square(tree[tree[z].rs].size);
    }

    long long query() {
        return ans;
    }

private:
    struct Node {
        int ls, rs, fa;
        long long size, sum, sqr;

        int &operator[](int x) {
            return (x == 0 ? ls : rs);
        }
    };

    Node tree[MAX_N];
    int up[MAX_N];
    long long ans;

    void pushup(int x) {
        tree[x].size = tree[tree[x].ls].size + tree[tree[x].rs].size + 1 + tree[x].sum;
    }

    int which(int x) {
        return (x == tree[tree[x].fa].rs ? 1 : 0);
    }

    bool is_root(int x) {
        return (x != tree[tree[x].fa].ls && x != tree[tree[x].fa].rs);
    }

    void rotate(int x) {
        int y = tree[x].fa, z = tree[y].fa, k = which(x), w = tree[x][k ^ 1];

        if (!is_root(y))
            tree[z][which(y)] = x;

        tree[x][k ^ 1] = y;
        tree[y][k] = w;
        tree[x].fa = z;
        tree[y].fa = x;

        if (w)
            tree[w].fa = y;

        pushup(y);
        pushup(x);
    }

    void splay(int x) {
        for (int y; y = tree[x].fa, !is_root(x); rotate(x))
            if (!is_root(y))
                rotate(which(x) == which(y) ? y : x);
    }

    void access(int x) {
        for (int y = 0; x; y = x, x = tree[x].fa) {
            splay(x);
            tree[x].sum += tree[tree[x].rs].size - tree[y].size;
            tree[x].sqr += square(tree[tree[x].rs].size) - square(tree[y].size);
            tree[x].rs = y;
            pushup(x);
        }
    }

    int find_root(int x) {
        access(x);
        splay(x);

        while (tree[x].ls)
            x = tree[x].ls;

        splay(x);
        return x;
    }
};

int n, m;
int col[MAX_N];
bool tag[MAX_N];
std::vector<int> tree[MAX_N];
std::vector<std::pair<int, int>> op[MAX_N];
long long ans, last, delta[MAX_N];
LinkCutTree lct;

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void dfs(int x, int fa) {
    lct.init(x, fa);

    for (int y : tree[x]) {
        if (y == fa)
            continue;

        dfs(y, x);
    }
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("col.in", "r", stdin);
    std::freopen("col.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::cin >> n >> m;

    for (int i = 1; i <= n; i++)
        std::cin >> col[i];

    for (int i = 1; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        link(x, y);
    }

    for (int i = 1; i <= n; i++)
        op[col[i]].push_back({ i, 0 });

    for (int i = 1; i <= m; i++) {
        int x, y;
        std::cin >> x >> y;

        if (col[x] == y)
            continue;

        op[col[x]].push_back({ x, i });
        col[x] = y;
        op[col[x]].push_back({ x, i });
    }

    dfs(1, n + 1);
    lct.init(n + 1);

    for (int i = 1; i <= n; i++) {
        lct.link(i);
        tag[i] = 1;
    }

    for (int i = 1; i <= n; i++) {
        if (!op[i].size()) {
            delta[0] += square(n);
            continue;
        }

        if (op[i][0].second) {
            delta[0] += square(n);
            last = square(n);
        } else {
            last = 0;
        }

        for (auto [x, id] : op[i]) {
            tag[x] ^= 1;

            if (tag[x])
                lct.link(x);
            else
                lct.cut(x);

            delta[id] += lct.query() - last;
            last = lct.query();
        }

        for (auto [x, id] : op[i]) {
            tag[x] ^= 1;

            if (tag[x])
                lct.link(x);
            else
                lct.cut(x);
        }
    }

    ans = 1ll * n * n * n;

    for (int i = 0; i <= m; i++) {
        ans -= delta[i];
        std::cout << ans << std::endl;
    }

    return 0;
}
