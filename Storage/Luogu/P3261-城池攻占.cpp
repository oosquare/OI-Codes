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

constexpr int maxn = 3e5 + 10;

struct Node {
    int ls, rs, size;
    unsigned pri;
    long long key, add, mul = 1;
};

int n, m, c[maxn];
vector<int> tree[maxn];
int dep[maxn];
long long h[maxn], a[maxn], v[maxn];
Node treap[maxn];
unsigned seed;
int root[maxn];
int ans1[maxn], ans2[maxn];

unsigned randInt() {
    return (seed = (seed + 7) * 6236249 + 19301933);
}

void pushup(int x) {
    if (!x)
        return;

    treap[x].size = treap[treap[x].ls].size + 1 + treap[treap[x].rs].size;
}

void updateAdd(int x, long long v) {
    if (!x)
        return;

    treap[x].key += v;
    treap[x].add += v;
}

void updateMul(int x, long long v) {
    if (!x)
        return;

    treap[x].key *= v;
    treap[x].add *= v;
    treap[x].mul *= v;
}

void pushdown(int x) {
    if (!x)
        return;

    if (treap[x].mul != 1) {
        if (treap[x].ls)
            updateMul(treap[x].ls, treap[x].mul);

        if (treap[x].rs)
            updateMul(treap[x].rs, treap[x].mul);

        treap[x].mul = 1;
    }

    if (treap[x].add != 0) {
        if (treap[x].ls)
            updateAdd(treap[x].ls, treap[x].add);

        if (treap[x].rs)
            updateAdd(treap[x].rs, treap[x].add);

        treap[x].add = 0;
    }
}

void split(int root, long long key, int &x, int &y) {
    if (!root) {
        x = y = 0;
        return;
    }

    pushdown(root);

    if (treap[root].key <= key) {
        x = root;
        split(treap[x].rs, key, treap[x].rs, y);
        pushup(x);
    } else {
        y = root;
        split(treap[y].ls, key, x, treap[y].ls);
        pushup(y);
    }
}

int merge(int x, int y) {
    if (!x || !y)
        return x ^ y;

    pushdown(x);
    pushdown(y);

    if (treap[x].pri > treap[y].pri) {
        treap[x].rs = merge(treap[x].rs, y);
        pushup(x);
        return x;
    } else {
        treap[y].ls = merge(x, treap[y].ls);
        pushup(y);
        return y;
    }
}

int mergeTree(int x, int y) {
    if (!x || !y)
        return x ^ y;

    if (treap[x].pri < treap[y].pri)
        swap(x, y);

    pushdown(x);
    pushdown(y);
    int y1, y2;
    split(y, treap[x].key, y1, y2);
    treap[x].ls = mergeTree(treap[x].ls, y1);
    treap[x].rs = mergeTree(treap[x].rs, y2);
    pushup(x);
    return x;
}

void insert(int &root, int p) {
    int x, y;
    split(root, treap[p].key, x, y);
    root = merge(merge(x, p), y);
}

void link(int x, int y) {
    tree[x].push_back(y);
}

void calc(int x, int d) {
    if (!x)
        return;

    ans2[x] = dep[c[x]] - d;
    calc(treap[x].ls, d);
    calc(treap[x].rs, d);
}

void solve(int x) {
    for (int y : tree[x]) {
        dep[y] = dep[x] + 1;
        solve(y);
        root[x] = mergeTree(root[x], root[y]);
    }

    int r1, r2;
    split(root[x], h[x] - 1, r1, r2);
    calc(r1, dep[x]);
    ans1[x] = treap[r1].size;
    root[x] = r2;

    if (a[x] == 0)
        updateAdd(root[x], v[x]);
    else
        updateMul(root[x], v[x]);
}

int main() {
    n = read(), m = read();

    for (int i = 1; i <= n; ++i)
        h[i] = read<long long>();

    for (int i = 2; i <= n; ++i) {
        int f = read();
        a[i] = read(), v[i] = read<long long>();
        link(f, i);
    }

    for (int i = 1; i <= m; ++i) {
        long long s = read<long long>();
        c[i] = read();
        treap[i].size = 1;
        treap[i].key = s;
        treap[i].pri = randInt();
        insert(root[c[i]], i);
    }

    for (int i = 1; i <= m; ++i)
        ans2[i] = -1;

    dep[1] = 1;

    solve(1);

    for (int i = 1; i <= n; ++i)
        write(ans1[i]);

    for (int i = 1; i <= m; ++i)
        write(ans2[i] == -1 ? dep[c[i]] : ans2[i]);

    return 0;
}