#pragma GCC optimize(3)
#include <cstdio>
#include <vector>
#include <random>

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = (int) getchar();

    for (; c < '0' || c > '9'; c = (int) getchar())
        if (c == '-')
            s = -1;

    for (; '0' <= c && c <= '9'; c = (int) getchar())
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

constexpr int MAX_N = 300000 + 10;

class SparseTable {
public:
    void init(int * arr, int len) {
        data = arr;
        log2Val[0] = -1;

        for (int i = 1; i <= len; ++i) {
            log2Val[i] = log2Val[i / 2] + 1;
            pos[i][0] = i;
        }

        for (int j = 1; j <= 17; ++j)
            for (int i = 1; i + (1 << j) - 1 <= len; ++i)
                pos[i][j] = data[pos[i][j - 1]] > data[pos[i + (1 << (j - 1))][j - 1]]
                ? pos[i][j - 1]
                : pos[i + (1 << (j - 1))][j - 1];
    }

    int query(int l, int r) {
        int s = log2Val[r - l + 1];
        return data[pos[l][s]] > data[pos[r - (1 << s) + 1][s]]
            ? pos[l][s]
            : pos[r - (1 << s) + 1][s];
    }
private:
    int * data;
    int log2Val[MAX_N], pos[MAX_N][20];
} st;

class Tree {
public:
    void link(int x, int y) {
        tree[x].push_back(y);
    }

    void preprocess(int root) {
        dfs(root, 0);
    }

    int jump(int x, int mx) {
        for (int i = 16; i >= 0; --i)
            if (step[x][i] && step[x][i] <= mx)
                x = step[x][i];

        return step[x][0];
    }

    int getDfn(int x) {
        return dfn[x];
    }

    int getLast(int x) {
        return last[x];
    }
private:
    std::vector<int> tree[MAX_N];
    int step[MAX_N][20], dep[MAX_N];
    int dfn[MAX_N], last[MAX_N], timer;

    void dfs(int x, int fa) {
        dep[x] = dep[fa] + 1;
        dfn[x] = ++timer;

        for (int i = 1; i <= 16; ++i)
            step[x][i] = step[step[x][i - 1]][i - 1];

        for (int y : tree[x]) {
            step[y][0] = x;
            dfs(y, x);
        }

        last[x] = timer;
    }
} tree;

class Treap {
public:
    Treap() : gen((std::random_device())()) {}

    void init(int n) {
        for (int i = 1; i <= n; ++i)
            root = merge(root, create(i));
    }

    void modify(int l, int r) {
        int al, ar, x, y, mid;
        split(root, l - 1, al, mid);
        split(mid, r - l + 1, mid, ar);
        split(mid, 1, x, mid);
        split(mid, r - l - 1, mid, y);
        tree[x].key = tree[y].key;
        root = merge(merge(merge(merge(al, mid), y), x), ar);
    }

    int query(int k) {
        int x, y, z, res;
        split(root, k - 1, x, y);
        split(y, 1, y, z);
        res = tree[y].key;
        root = merge(merge(x, y), z);
        return res;
    }
private:
    struct Node {
        int ls, rs, size, key;
        unsigned long priority;
    };

    Node tree[MAX_N];
    int root, tot;
    std::mt19937 gen;

    int create(int key) {
        tree[++tot] = { 0, 0, 1, key, gen() };
        return tot;
    }

    void pushup(int x) {
        tree[x].size = tree[tree[x].ls].size + 1 + tree[tree[x].rs].size;
    }

    void split(int root, int sze, int & x, int & y) {
        if (!root) {
            x = y = 0;
            return;
        }

        if (tree[tree[root].ls].size < sze) {
            x = root;
            split(tree[x].rs, sze - tree[tree[root].ls].size - 1, tree[x].rs, y);
            pushup(x);
        } else {
            y = root;
            split(tree[y].ls, sze, x, tree[y].ls);
            pushup(y);
        }
    }

    int merge(int x, int y) {
        if (!x || !y)
            return x ^ y;

        if (tree[x].priority > tree[y].priority) {
            tree[x].rs = merge(tree[x].rs, y);
            pushup(x);
            return x;
        } else {
            tree[y].ls = merge(x, tree[y].ls);
            pushup(y);
            return y;
        }
    }
} treap;

class BinaryIndexedTree {
public:
    void init(int len) {
        this->len = len;
    }

    void add(int x, int y) {
        int p = tree.getDfn(x);

        for (; p <= len; p += lowbit(p))
            arr[p] += y;

        p = tree.getLast(x) + 1;

        for (; p <= len; p += lowbit(p))
            arr[p] -= y;
    }

    long long query(int x) {
        long long res = 0;
        x = tree.getDfn(x);

        for (; x; x -= lowbit(x))
            res += arr[x];

        return res;
    }
private:
    long long arr[MAX_N];
    int len;

    int lowbit(int x) {
        return x & (-x);
    }
} bit;

int n, m;
int a[MAX_N];

int position(int x) {
    return st.query(x, treap.query(x));
}

void preprocess() {
    st.init(a, n);
    treap.init(n);

    for (int i = 1; i <= n; ++i) {
        int l = i + 1, r = n;
        int p = n + 1;

        while (l <= r) {
            int mid = (l + r) / 2;

            if (a[st.query(i + 1, mid)] > a[i]) {
                p = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        tree.link(p, i);
    }

    tree.preprocess(n + 1);

    bit.init(n + 1);

    for (int i = 1; i <= n; ++i)
        bit.add(i, a[i]);
}

void modify(int l, int r) {
    if (l == r)
        return;

    int start = position(l);
    treap.modify(l, r);

    if ((l == 1 || position(l - 1) != start) && position(l) != start)
        bit.add(start, -a[start]);
}

long long query(int l, int r) {
    int start = position(l), end = tree.jump(start, position(r));
    return bit.query(start) - bit.query(end);
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("sequence.in", "r", stdin);
    std::freopen("sequence.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    n = read(), m = read();

    for (int i = 1; i <= n; ++i)
        a[i] = read();

    preprocess();
    
    for (int i = 1; i <= m; ++i) {
        int op = read(), l = read(), r = read();

        if (op == 1)
            modify(l, r);
        else
            write(query(l, r));
    }

    return 0;
}
