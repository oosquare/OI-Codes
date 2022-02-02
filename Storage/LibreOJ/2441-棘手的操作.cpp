#include <iostream>
#include <set>
#include <tuple>
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
    int ls, rs, fa, size;
    int pri;
    int key;
};

int n, q;
Node tree[maxn];
int root[maxn];
int fa[maxn], sze[maxn], add[maxn], add2;
multiset<int> se;
unsigned seed;
char op[maxn][3];
tuple<int, int, int> qs[maxn];
int sum[maxn];

inline unsigned randInt() {
    return (seed = ((seed + 5) * 413415 + 5317369));
}

void pushup(int x) {
    tree[x].size = tree[tree[x].ls].size + 1 + tree[tree[x].rs].size;

    if (tree[x].ls)
        tree[tree[x].ls].fa = x;

    if (tree[x].rs)
        tree[tree[x].rs].fa = x;
}

void splitByValue(int root, int val, int &x, int &y) {
    if (!root) {
        x = y = 0;
        return;
    }

    if (tree[root].key <= val) {
        x = root;
        splitByValue(tree[x].rs, val, tree[x].rs, y);
        pushup(x);
        tree[y].fa = 0;
    } else {
        y = root;
        splitByValue(tree[y].ls, val, x, tree[y].ls);
        pushup(y);
        tree[x].fa = 0;
    }
}

void splitBySize(int root, int sze, int &x, int &y) {
    if (!root) {
        x = y = 0;
        return;
    }

    if (tree[tree[root].ls].size + 1 <= sze) {
        x = root;
        splitBySize(tree[x].rs, sze - tree[tree[root].ls].size - 1, tree[x].rs, y);
        pushup(x);
        tree[y].fa = 0;
    } else {
        y = root;
        splitBySize(tree[y].ls, sze, x, tree[y].ls);
        pushup(y);
        tree[x].fa = 0;
    }
}

int merge(int x, int y) {
    if (!x || !y)
        return x ^ y;

    if (tree[x].pri > tree[y].pri) {
        tree[x].rs = merge(tree[x].rs, y);
        pushup(x);
        return x;
    } else {
        tree[y].ls = merge(x, tree[y].ls);
        pushup(y);
        return y;
    }
}

int mergeTree(int x, int y) {
    if (!x || !y)
        return x ^ y;

    if (tree[x].pri < tree[y].pri)
        swap(x, y);

    int y1, y2;
    splitByValue(y, tree[x].key, y1, y2);
    tree[x].ls = mergeTree(tree[x].ls, y1);
    tree[x].rs = mergeTree(tree[x].rs, y2);
    pushup(x);
    return x;
}

int ask(int x) {
    int res = tree[tree[x].ls].size;

    for (int f; f = tree[x].fa, f; x = f)
        if (tree[f].rs == x)
            res += tree[tree[f].ls].size + 1;

    return res;
}

void dfs(int x, int v) {
    if (!x)
        return;

    tree[x].key += v;
    dfs(tree[x].ls, v);
    dfs(tree[x].rs, v);
}

void init(int x, int key) {
    tree[x].size = 1;
    tree[x].pri = randInt();
    tree[x].key = key;
}

int find(int x) {
    return (fa[x] == x ? x : fa[x] = find(fa[x]));
}

int top(int x) {
    while (tree[x].rs)
        x = tree[x].rs;

    return tree[x].key + add[find(x)];
}

inline int query(int x) {
    return tree[x].key + add[find(x)];
}

void link(int x, int y) {
    x = find(x), y = find(y);

    if (x == y)
        return;

    se.erase(se.find(top(root[x])));
    se.erase(se.find(top(root[y])));

    if (sze[x] < sze[y])
        swap(x, y);

    dfs(root[y], add[y] - add[x]);
    root[x] = mergeTree(root[x], root[y]);
    fa[y] = x;
    root[y] = sze[y] = add[y] = 0;
    sze[x] += sze[y];
    se.insert(top(root[x]));
}

void addNode(int x, int d) {
    int k = ask(x), fx = find(x);
    se.erase(se.find(top(root[fx])));
    int r1, r2, r3;
    splitBySize(root[fx], k, r1, r2);
    splitBySize(r2, 1, r2, r3);
    tree[r2].key += d;
    root[fx] = mergeTree(r2, merge(r1, r3));
    se.insert(top(root[fx]));
}

void addTree(int x, int d) {
    int fx = find(x), t = top(root[fx]);
    se.erase(se.find(t));
    add[fx] += d;
    se.insert(t + d);
}

inline void addGlobal(int d) {
    add2 += d;
}

inline int queryNode(int x) {
    return query(x) + add2;
}

inline int queryTree(int x) {
    return top(root[find(x)]) + add2;
}

inline int queryGlobal() {
    return *se.rbegin() + add2;
}

int main() {
    ios::sync_with_stdio(false);
    n = read();

    for (int i = 1, a; i <= n; ++i) {
        a = read();
        fa[i] = i;
        root[i] = i;
        init(i, a);
        se.insert(a);
    }

    q = read();

    for (int i = 1; i <= q; ++i) {
        scanf("%s", op[i]);
        auto &[x, y, v] = qs[i];

        if (op[i][0] == 'U') {
            x = read(), y = read();
        } else if (op[i][0] == 'A' && op[i][1] == '1') {
            x = read(), v = read();
        } else if (op[i][0] == 'A' && op[i][1] == '2') {
            x = read(), v = read();
        } else if (op[i][0] == 'A' && op[i][1] == '3') {
            v = read();
        } else if (op[i][0] == 'F' && op[i][1] == '1') {
            x = read();
        } else if (op[i][0] == 'F' && op[i][1] == '2') {
            x = read();
        }
    }

    for (int i = q; i >= 1; --i)
        sum[i] = sum[i + 1] + (op[i][0] == 'F');

    for (int i = 1; i <= q; ++i) {
        if (!sum[i])
            break;

        auto [x, y, v] = qs[i];

        if (op[i][0] == 'U') {
            link(x, y);
        } else if (op[i][0] == 'A' && op[i][1] == '1') {
            addNode(x, v);
        } else if (op[i][0] == 'A' && op[i][1] == '2') {
            addTree(x, v);
        } else if (op[i][0] == 'A' && op[i][1] == '3') {
            addGlobal(v);
        } else if (op[i][0] == 'F' && op[i][1] == '1') {
            write(queryNode(x));
        } else if (op[i][0] == 'F' && op[i][1] == '2') {
            write(queryTree(x));
        } else {
            write(queryGlobal());
        }
    }

    return 0;
}