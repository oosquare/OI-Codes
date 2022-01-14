#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

constexpr int maxn = 1e5 + 10;

struct Data {
    int pre = 0, suf = 0, cnt = 0;

    static Data merge(Data lhs, Data rhs) {
        return {lhs.pre, rhs.suf, lhs.cnt + rhs.cnt - (lhs.suf == rhs.pre)};
    }

    static Data reverse(Data a) {
        return {a.suf, a.pre, a.cnt};
    }
};

struct SegmentTree {
public:
    void build(int n, int c[], int rev[]) {
        build(1, 1, n, c, rev);
    }

    void assign(int l, int r, int c) {
        assign(1, l, r, c);
    }

    Data query(int l, int r) {
        return query(1, l, r);
    }

private:
    struct Node {
        int left, right;
        Data data;
        int assign;
    };

    Node tree[maxn * 4];

    void pushup(int x) {
        tree[x].data = Data::merge(tree[x * 2].data, tree[x * 2 + 1].data);
    }

    void update(int x, int c) {
        tree[x].data.cnt = 1;
        tree[x].data.pre = tree[x].data.suf = c;
        tree[x].assign = c;
    }

    void pushdown(int x) {
        if (tree[x].assign) {
            update(x * 2, tree[x].assign);
            update(x * 2 + 1, tree[x].assign);
            tree[x].assign = 0;
        }
    }

    void build(int x, int l, int r, int c[], int rev[]) {
        tree[x].left = l;
        tree[x].right = r;

        if (l == r) {
            tree[x].data.pre = tree[x].data.suf = c[rev[l]];
            tree[x].data.cnt = 1;
            return;
        }

        int mid = (l + r) / 2;
        build(x * 2, l, mid, c, rev);
        build(x * 2 + 1, mid + 1, r, c, rev);
        pushup(x);
    }

    void assign(int x, int l, int r, int c) {
        if (l <= tree[x].left && tree[x].right <= r) {
            update(x, c);
            return;
        }

        int mid = (tree[x].left + tree[x].right) / 2;
        pushdown(x);

        if (l <= mid)
            assign(x * 2, l, r, c);

        if (mid < r)
            assign(x * 2 + 1, l, r, c);

        pushup(x);
    }

    Data query(int x, int l, int r) {
        if (l <= tree[x].left && tree[x].right <= r)
            return tree[x].data;

        int mid = (tree[x].left + tree[x].right) / 2;
        pushdown(x);

        if (r <= mid)
            return query(x * 2, l, r);
        else if (mid < l)
            return query(x * 2 + 1, l, r);
        else
            return Data::merge(query(x * 2, l, r), query(x * 2 + 1, l, r));
    }
};

class Tree {
public:
    void init(int c[], int n) {
        for (int i = 1; i <= n; ++i)
            col[i] = c[i];
    }

    void link(int x, int y) {
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    void preprocess() {
        dfs(1);
        dfs(1, 1);
        seg.build(timer, col, rev);
    }

    int order(int x) {
        return dfn[x];
    }

    int depth(int x) {
        return dep[x];
    }

    vector<int> &operator[](int x) {
        return tree[x];
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

    void assign(int x, int y, int c) {
        int fx = top[x], fy = top[y];

        while (fx != fy) {
            if (dep[fx] < dep[fy]) {
                swap(x, y);
                swap(fx, fy);
            }

            seg.assign(dfn[fx], dfn[x], c);
            x = fa[fx];
            fx = top[x];
        }

        if (dep[x] > dep[y])
            swap(x, y);

        seg.assign(dfn[x], dfn[y], c);
    }

    Data query(int x, int y) {
        int fx = top[x], fy = top[y];
        Data l, r;

        while (fx != fy) {
            if (dep[fx] > dep[fy]) {
                l = Data::merge(seg.query(dfn[fx], dfn[x]), l);
                x = fa[fx];
                fx = top[x];
            } else {
                r = Data::merge(seg.query(dfn[fy], dfn[y]), r);
                y = fa[fy];
                fy = top[y];
            }
        }

        if (dep[x] < dep[y])
            r = Data::merge(seg.query(dfn[x], dfn[y]), r);
        else
            l = Data::merge(seg.query(dfn[y], dfn[x]), l);

        return Data::merge(Data::reverse(l), r);
    }

private:
    vector<int> tree[maxn];
    int size[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
    int timer, dfn[maxn], rev[maxn], col[maxn];
    SegmentTree seg;

    void dfs(int x) {
        dep[x] = dep[fa[x]] + 1;
        size[x] = 1;

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
        dfn[x] = ++timer;
        rev[timer] = x;

        if (son[x])
            dfs(son[x], t);

        for (int y : tree[x]) {
            if (y == fa[x] || y == son[x])
                continue;

            dfs(y, y);
        }
    }
};

int n, q, k, col[maxn];
Tree tree;
vector<pair<int, Data>> vtree[maxn];
int timer, seq[maxn], raw[maxn], key[maxn], st[maxn], top;
int f[maxn][2], cont[maxn], sze[maxn], cnt[maxn];

void link(int x, int y, Data data) {
    vtree[x].push_back({y, data});
    vtree[y].push_back({x, Data::reverse(data)});
}

void build(int seq[], int len) {
    sort(seq + 1, seq + 1 + len, [](int lhs, int rhs) {
        return tree.order(lhs) < tree.order(rhs);
    });

    st[top = 1] = 1;
    vtree[1].clear();

    for (int i = 1; i <= len; ++i) {
        if (seq[i] == 1)
            continue;

        int l = tree.lca(seq[i], st[top]);

        if (l != st[top]) {
            while (tree.order(l) < tree.order(st[top - 1])) {
                link(st[top], st[top - 1], tree.query(st[top], st[top - 1]));
                --top;
            }

            if (l != st[top - 1]) {
                vtree[l].clear();
                link(l, st[top], tree.query(l, st[top]));
                st[top] = l;
            } else {
                link(l, st[top], tree.query(l, st[top]));
                --top;
            }
        }

        vtree[seq[i]].clear();
        st[++top] = seq[i];
    }

    for (int i = 1; i < top; ++i)
        link(st[i], st[i + 1], tree.query(st[i], st[i + 1]));
}

void dfs1(int x, int fa, int col) {
    sze[x] = (key[x] == timer);
    f[x][0] = 0;
    cnt[x] = 0;

    for (auto [y, d] : vtree[x]) {
        if (y == fa)
            continue;

        dfs1(y, x, d.suf);
        sze[x] += sze[y];
        f[x][0] += f[y][0] + sze[y] * d.cnt - cnt[y];
        cont[y] = f[y][0] + sze[y] * d.cnt - cnt[y];
        cnt[x] += (col == d.pre ? sze[y] : 0);
    }
}

void dfs2(int x, int fa, int col) {
    if (fa == 0)
        f[x][1] = f[x][0];

    map<int, int> mp;
    mp[col] = k - sze[x];

    for (auto [y, d] : vtree[x]) {
        if (y == fa)
            continue;

        mp[d.pre] += sze[y];
    }

    for (auto [y, d] : vtree[x]) {
        if (y == fa)
            continue;

        f[y][1] = f[y][0] + (f[x][1] - cont[y]) + (k - sze[y]) * d.cnt - (mp[d.pre] - sze[y]);
        dfs2(y, x, d.suf);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;

    for (int i = 1; i <= n; ++i)
        cin >> col[i];

    tree.init(col, n);

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        tree.link(x, y);
    }

    tree.preprocess();

    for (int i = 1; i <= q; ++i) {
        int op;
        cin >> op;

        if (op == 1) {
            int x, y, c;
            cin >> x >> y >> c;
            tree.assign(x, y, c);
        } else {
            cin >> k;
            ++timer;

            for (int i = 1; i <= k; ++i) {
                int x;
                cin >> x;
                key[x] = timer;
                seq[i] = raw[i] = x;
            }

            build(seq, k);
            dfs1(1, 0, 0);
            dfs2(1, 0, 0);

            for (int i = 1; i <= k; ++i)
                cout << f[raw[i]][1] + 1 << " ";

            cout << endl;
        }
    }

    return 0;
}