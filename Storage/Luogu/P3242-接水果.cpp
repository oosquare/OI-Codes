#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int maxn = 4e4 + 10;

struct Tree {
    vector<int> tree[maxn];
    int size[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
    int timer, dfn[maxn], mdfn[maxn];

    void link(int x, int y) {
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    void dfs(int x) {
        size[x] = 1;
        dep[x] = dep[fa[x]] + 1;
        dfn[x] = ++timer;

        for (int y : tree[x]) {
            if (y == fa[x])
                continue;

            fa[y] = x;
            dfs(y);
            size[x] += size[y];

            if (size[son[x]] < size[y])
                son[x] = y;
        }

        mdfn[x] = dfn[x] + size[x] - 1;
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

    int jump(int x, int to) {
        int fx = top[x];

        while (fx != top[to]) {
            if (fa[fx] == to)
                return fx;

            x = fa[fx];
            fx = top[x];
        }

        return son[to];
    }
};

struct BinaryIndexedTree {
    int arr[maxn], n;

    void init(int n) {
        this->n = n;
    }

    void add(int l, int r, int v) {
        for (; l <= n; l += (l & (-l)))
            arr[l] += v;

        for (++r; r <= n; r += (r & (-r)))
            arr[r] -= v;
    }

    int query(int x) {
        int res = 0;

        for (; x; x -= (x & (-x)))
            res += arr[x];

        return res;
    }
};

struct Operation {
    int type, x, l, r, k, cont, id;
};

int n, p, q;
Tree tree;
BinaryIndexedTree arr;
Operation op[maxn * 5], tmp1[maxn * 5], tmp2[maxn * 5];
int tot;
vector<int> val;
int ans[maxn];

void solve(int l, int r, int al, int ar) {
    if (l > r)
        return;

    if (al == ar) {
        for (int i = l; i <= r; ++i)
            ans[op[i].id] = val[al];

        return;
    }

    int mid = (al + ar) / 2, it1 = 0, it2 = 0;

    for (int i = l; i <= r; ++i) {
        if (op[i].type == 1) {
            if (op[i].k <= val[mid]) {
                arr.add(op[i].l, op[i].r, op[i].cont);
                tmp1[++it1] = op[i];
            } else {
                tmp2[++it2] = op[i];
            }
        } else {
            int sum = arr.query(op[i].l);

            if (op[i].k <= sum) {
                tmp1[++it1] = op[i];
            } else {
                tmp2[++it2] = op[i];
                tmp2[it2].k -= sum;
            }
        }
    }

    for (int i = 1; i <= it1; ++i)
        op[l + i - 1] = tmp1[i];

    for (int i = 1; i <= it2; ++i)
        op[l + it1 + i - 1] = tmp2[i];

    solve(l, l + it1 - 1, al, mid);
    solve(l + it1, r, mid + 1, ar);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> p >> q;
    arr.init(n);

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        tree.link(x, y);
    }

    tree.preprocess();

    for (int i = 1; i <= p; ++i) {
        int x, y, v;
        cin >> x >> y >> v;
        val.push_back(v);
        int l = tree.lca(x, y);

        if (tree.dfn[x] > tree.dfn[y])
            swap(x, y);

        if (l != x && l != y) {
            op[++tot] = {1, tree.dfn[x], tree.dfn[y], tree.mdfn[y], v, 1, 0};
            op[++tot] = {1, tree.mdfn[x] + 1, tree.dfn[y], tree.mdfn[y], v, -1, 0};
        } else {
            int z = tree.jump(y, x);

            if (tree.dfn[z] > 1) {
                op[++tot] = {1, 1, tree.dfn[y], tree.mdfn[y], v, 1, 0};
                op[++tot] = {1, tree.dfn[z], tree.dfn[y], tree.mdfn[y], v, -1, 0};
            }

            if (tree.dfn[z] < n) {
                op[++tot] = {1, tree.dfn[y], tree.mdfn[z] + 1, n, v, 1, 0};
                op[++tot] = {1, tree.mdfn[y] + 1, tree.mdfn[z] + 1, n, v, -1, 0};
            }
        }
    }

    for (int i = 1; i <= q; ++i) {
        int x, y, k;
        cin >> x >> y >> k;

        if (tree.dfn[x] > tree.dfn[y])
            swap(x, y);

        op[++tot] = {2, tree.dfn[x], tree.dfn[y], 0, k, 0, i};
    }

    sort(val.begin(), val.end());
    auto it = unique(val.begin(), val.end());
    val.erase(it, val.end());

    sort(op + 1, op + 1 + tot, [](auto l, auto r) {
        if (l.x != r.x)
            return l.x < r.x;

        return l.type < r.type;
    });

    solve(1, tot, 0, val.size() - 1);

    for (int i = 1; i <= q; ++i)
        cout << ans[i] << endl;

    return 0;
}