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
constexpr long long oo = 123456789123456789;

struct Segment {
    long long k = 0, b = oo;

    long long calc(long long x) const {
        return k * x + b;
    }

    long long calc(long long l, long long r) const {
        return (k > 0 ? calc(l) : calc(r));
    }
};

struct Node {
    int ls, rs;
    Segment seg;
    long long key, min;

    Node() : ls(0), rs(0), seg(Segment()), key(oo), min(oo) {}
};

template <int size> struct NodePool {
    Node pool[size];
    int uuid;

    int allocate() {
        return ++uuid;
    }

    Node &operator[](int x) {
        return pool[x];
    }

    const Node &operator[](int x) const {
        return pool[x];
    }
};

NodePool<maxn * 50> nodes;

class LiChaoSegmentTree {
public:
    LiChaoSegmentTree() {
        root = 0;
        len = 0;
    }

    void init(long long len) {
        this->len = len;
    }

    void insert(long long l, long long r, const Segment &s) {
        insert(root, 0, len, l, r, s);
    }

    long long query(long long l, long long r) {
        return query(root, 0, len, l, r);
    }

private:
    long long len;
    int root;

    void pushup(int x) {
        nodes[x].min = min(nodes[x].min, nodes[x].key);
        nodes[x].min = min(nodes[x].min, min(nodes[nodes[x].ls].min, nodes[nodes[x].rs].min));
    }

    void insert(int &x, long long l, long long r, long long il, long long ir, const Segment &s) {
        if (!x) {
            x = nodes.allocate();

            if (il <= l && r <= ir) {
                nodes[x].seg = s;
                nodes[x].min = nodes[x].key = s.calc(l, r);
                return;
            }
        }

        long long mid = (l + r) / 2;

        if (il <= l && r <= ir) {
            if (l == r) {
                if (s.calc(l) < nodes[x].seg.calc(l)) {
                    nodes[x].seg = s;
                    nodes[x].min = nodes[x].key = s.calc(l);
                }

                return;
            }

            if (s.k > nodes[x].seg.k) {
                if (s.calc(mid) < nodes[x].seg.calc(mid)) {
                    insert(nodes[x].rs, mid + 1, r, il, ir, nodes[x].seg);
                    nodes[x].seg = s;
                } else {
                    insert(nodes[x].ls, l, mid, il, ir, s);
                }
            } else if (s.k < nodes[x].seg.k) {
                if (s.calc(mid) < nodes[x].seg.calc(mid)) {
                    insert(nodes[x].ls, l, mid, il, ir, nodes[x].seg);
                    nodes[x].seg = s;
                } else {
                    insert(nodes[x].rs, mid + 1, r, il, ir, s);
                }
            } else {
                if (s.b < nodes[x].seg.b)
                    nodes[x].seg = s;
            }

            nodes[x].key = min(nodes[x].key, s.calc(l, r));
            pushup(x);
            return;
        }

        if (il <= mid)
            insert(nodes[x].ls, l, mid, il, ir, s);

        if (mid < ir)
            insert(nodes[x].rs, mid + 1, r, il, ir, s);

        pushup(x);
    }

    long long query(int x, long long l, long long r, long long ql, long long qr) {
        if (!x)
            return oo;

        if (ql <= l && r <= qr)
            return nodes[x].min;

        long long mid = (l + r) / 2;
        long long res = nodes[x].seg.calc(max(l, ql), min(r, qr));

        if (ql <= mid)
            res = min(res, query(nodes[x].ls, l, mid, ql, qr));

        if (mid < qr)
            res = min(res, query(nodes[x].rs, mid + 1, r, ql, qr));

        return res;
    }
};

int n, m;
vector<pair<int, int>> tree[maxn];
int sze[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
int cnt, id[maxn];
long long dis[maxn], pos[maxn];
LiChaoSegmentTree seg[maxn];

void link(int x, int y, int l) {
    tree[x].push_back({y, l});
    tree[y].push_back({x, l});
}

void dfs(int x) {
    sze[x] = 1;
    dep[x] = dep[fa[x]] + 1;

    for (auto [y, l] : tree[x]) {
        if (y == fa[x])
            continue;

        fa[y] = x;
        dis[y] = dis[x] + l;
        dfs(y);
        sze[x] += sze[y];

        if (sze[y] > sze[son[x]])
            son[x] = y;
    }
}

void dfs(int x, int t) {
    top[x] = t;
    pos[x] = dis[x] - dis[t];
    id[x] = (x == t ? ++cnt : id[t]);

    if (son[x])
        dfs(son[x], t);
    else
        seg[id[x]].init(pos[x]);

    for (auto [y, l] : tree[x]) {
        if (y == fa[x] || y == son[x])
            continue;

        dfs(y, y);
    }
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

void insert(int x, int y, long long a, long long b) {
    int fx = top[x], fy = top[y], x0 = x, l = lca(x, y);
    long long dx, dy;

    while (fx != fy) {
        if (dep[fx] > dep[fy]) {
            dx = dis[x0] - dis[x];
            seg[id[x]].insert(pos[fx], pos[x], {-a, a * (dx + pos[x]) + b});
            x = fa[fx];
            fx = top[x];
        } else {
            dy = dis[x0] + dis[fy] - 2 * dis[l];
            seg[id[y]].insert(pos[fy], pos[y], {a, a * (dy - pos[fy]) + b});
            y = fa[fy];
            fy = top[y];
        }
    }

    if (dep[x] < dep[y]) {
        dx = dis[x0] - dis[x];
        seg[id[x]].insert(pos[x], pos[y], {a, a * (dx - pos[x]) + b});
    } else {
        dx = dis[x0] - dis[x];
        seg[id[y]].insert(pos[y], pos[x], {-a, a * (dx + pos[x]) + b});
    }
}

long long query(int x, int y) {
    int fx = top[x], fy = top[y];
    long long res = oo;

    while (fx != fy) {
        if (dep[fx] < dep[fy]) {
            swap(x, y);
            swap(fx, fy);
        }

        res = min(res, seg[id[x]].query(pos[fx], pos[x]));
        x = fa[fx];
        fx = top[x];
    }

    if (dep[x] > dep[y])
        swap(x, y);

    res = min(res, seg[id[x]].query(pos[x], pos[y]));
    return res;
}

int main() {
    n = read(), m = read();

    for (int i = 1; i < n; ++i) {
        int x = read(), y = read(), l = read();
        link(x, y, l);
    }

    dfs(1);
    dfs(1, 1);

    for (int i = 1; i <= m; ++i) {
        int op = read(), x = read(), y = read(), a, b;

        if (op == 1) {
            a = read(), b = read();
            insert(x, y, a, b);
        } else {
            write(query(x, y));
        }
    }

    return 0;
}