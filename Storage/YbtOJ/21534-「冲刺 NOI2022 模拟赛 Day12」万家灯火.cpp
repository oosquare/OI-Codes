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

constexpr int MAX_N = 1e5 + 10;

class Tree {
public:
    void link(int x, int y) {
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    void preprocess(int root) {
        dfs(root, 0);
    }

    vector<int> & operator[](int x) {
        return tree[x];
    }

    int fa(int x) {
        return step[x][0];
    }

    int lca(int x, int y) {
        if (dep[x] < dep[y])
            swap(x, y);

        for (int i = lim[x]; i >= 0; --i)
            if (dep[step[x][i]] >= dep[y])
                x = step[x][i];

        if (x == y)
            return x;

        for (int i = lim[x]; i >= 0; --i) {
            if (step[x][i] != step[y][i]) {
                x = step[x][i];
                y = step[y][i];
            }
        }

        return step[x][0];
    }

    int jump(int x, int d) {
        for (int i = 17; i >= 0; --i) {
            if ((d >> i) & 1)
                x = step[x][i];
            
            if (!x)
                return x;
        }

        return x;
    }

    int distance(int x, int y) {
        return dep[x] + dep[y] - 2 * dep[lca(x, y)];
    }
private:
    vector<int> tree[MAX_N];
    int dep[MAX_N], step[MAX_N][18], lim[MAX_N];

    void dfs(int x, int fa) {
        dep[x] = dep[fa] + 1;

        for (int i = 1; i <= 17; ++i) {
            step[x][i] = step[step[x][i - 1]][i - 1];

            if (!step[x][i]) {
                lim[x] = i;
                break;
            }
        }

        for (int y : tree[x]) {
            if (y == fa)
                continue;

            step[y][0] = x;
            dfs(y, x);
        }
    }
};

class BinaryIndexedTree {
public:
    void init(int n) {
        this->n = n + 1;
        arr = vector<int>(n + 2);
    }

    void add(int x, int y) {
        x = min(x + 1, n);

        for (; x <= n; x += lowbit(x))
            arr[x] += y;
    }

    int query(int x) {
        x = min(x + 1, n);
        int res = 0;

        for (; x; x -= lowbit(x))
            res += arr[x];

        return res;
    }
private:
    int n;
    vector<int> arr;

    int lowbit(int x) {
        return x & (-x);
    }
};

int n, q;
int col[MAX_N], cnt[MAX_N];
char tmp[MAX_N];
Tree tree;
int father[MAX_N];
int tot, root, sze[MAX_N], sze2[MAX_N];
bool vis[MAX_N];
BinaryIndexedTree arr1[MAX_N];
BinaryIndexedTree arr2[MAX_N];

void getRoot(int x, int fa) {
    sze[x] = 1;
    sze2[x] = 0;

    for (int y : tree[x]) {
        if (vis[y] || y == fa)
            continue;

        getRoot(y, x);
        sze[x] += sze[y];
        sze2[x] = max(sze2[x], sze[y]);
    }

    sze2[x] = max(sze2[x], tot - sze[x]);

    if (!root || sze2[x] < sze2[root])
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
    arr1[x].init(sze[x] / 2 + 1);
    arr2[x].init(sze[x]);

    for (int y : tree[x]) {
        if (vis[y])
            continue;

        root = 0;
        tot = sze[y];
        getRoot(y, 0);
        father[root] = x;
        build(root);
    }
}

void add(int x0, int v) {
    arr1[x0].add(0, v);

    for (int x = x0, fa = father[x]; fa; x = fa, fa = father[x]) {
        int d = tree.distance(fa, x0);
        arr1[fa].add(d, v);
        arr2[x].add(d, v);
    }
}

void modify(int x0) {
    if (!col[x0]) {
        col[x0] = true;
        if (cnt[x0])
            add(x0, -cnt[x0]);

        if (tree.fa(x0)) {
            ++cnt[tree.fa(x0)];

            if (!col[tree.fa(x0)])
                add(tree.fa(x0), 1);
        }
    } else {
        col[x0] = false;

        if (cnt[x0])
            add(x0, cnt[x0]);

        if (tree.fa(x0)) {
            --cnt[tree.fa(x0)];

            if (!col[tree.fa(x0)])
                add(tree.fa(x0), -1);
        }
    }
}

int query(int x0, int dis) {
    --dis;
    int res = arr1[x0].query(dis);

    for (int x = x0, fa = father[x]; fa; x = fa, fa = father[x]) {
        int d = dis - tree.distance(fa, x0);

        if (d < 0)
            continue;

        res += arr1[fa].query(d);
        res -= arr2[x].query(d);
    }

    int top = tree.jump(x0, dis);

    if (top && top != 1) {
        res += (col[top] && !col[tree.fa(top)]);
        top = tree.fa(top);
    } else {
        top = 1;
    }

    if (top && col[top])
        ++res;

    if (col[x0]) {
        res += cnt[x0];

        if (!col[tree.fa(x0)])
            --res;
    }

    return res;
}

int main() {
    freopen("lights.in", "r", stdin);
    freopen("lights.out", "w", stdout);

    n = read(), q = read();    

    for (int i = 1; i < n; ++i) {
        int x = read(), y = read();
        tree.link(x, y);
    }

    tree.preprocess(1);
    tot = n;
    getRoot(1, 0);
    build(root);

    scanf("%s", tmp + 1);

    for (int i = 1; i <= n; ++i)
        if (tmp[i] - '0')
            modify(i);

    for (int i = 1; i <= q; ++i) {
        int op = read();

        if (op == 1) {
            int x = read();
            modify(x);
        } else {
            int x = read(), d = read();
            write(query(x, d));
        }
    }
    
    return 0;
}
