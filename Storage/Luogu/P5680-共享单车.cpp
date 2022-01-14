#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

constexpr int maxn = 50000 + 10;
constexpr int oo = 0x3f3f3f3f;

class Tree {
public:
    void link(int x, int y, int l) {
        tree[x].push_back({y, l});
        tree[y].push_back({x, l});
    }

    vector<pair<int, int>> &operator[](int x) {
        return tree[x];
    }

    void preprocess(int root) {
        dfs(root);
        dfs(root, root);
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
        return dis[x] + dis[y] - 2 * dis[lca(x, y)];
    }

    int order(int x) {
        return dfn[x];
    }

private:
    vector<pair<int, int>> tree[maxn];
    int size[maxn], dep[maxn], fa[maxn], son[maxn], dis[maxn], top[maxn];
    int timer, dfn[maxn];

    void dfs(int x) {
        size[x] = 1;
        dep[x] = dep[fa[x]] + 1;

        for (auto [y, l] : tree[x]) {
            if (y == fa[x])
                continue;

            fa[y] = x;
            dis[y] = dis[x] + l;
            dfs(y);
            size[x] += size[y];

            if (size[y] > size[son[x]])
                son[x] = y;
        }
    }

    void dfs(int x, int t) {
        top[x] = t;
        dfn[x] = ++timer;

        if (son[x])
            dfs(son[x], t);

        for (auto [y, l] : tree[x]) {
            if (y == fa[x] || y == son[x])
                continue;

            dfs(y, y);
        }
    }
};

int n, m, k, q, num;
Tree graph, tree;
int dis[maxn], pre[maxn][2];
bool vis[maxn], key[maxn];
vector<pair<int, int>> vtree[maxn];
int seq[maxn];
int st[maxn], top;
int f[maxn];

void link(int x, int y, int l) {
    vtree[x].push_back({y, l});
    vtree[y].push_back({x, l});
}

void dijkstra(int start) {
    priority_queue<pair<int, int>> q;

    for (int i = 1; i <= n; ++i)
        dis[i] = oo;

    dis[start] = 0;
    q.push({0, start});

    while (!q.empty()) {
        int x = q.top().second;
        q.pop();

        if (vis[x])
            continue;

        vis[x] = true;

        for (auto [y, l] : graph[x]) {
            if (dis[y] > dis[x] + l || (dis[y] == dis[x] + l && (!pre[y][0] || pre[y][0] > x))) {
                dis[y] = dis[x] + l;
                pre[y][0] = x;
                pre[y][1] = l;
                q.push({-dis[y], y});
            }
        }
    }
}

void build(int seq[], int len) {
    sort(seq + 1, seq + 1 + len, [](int lhs, int rhs) {
        return tree.order(lhs) < tree.order(rhs);
    });

    st[top = 1] = k;
    vtree[k].clear();

    for (int i = 1; i <= len; ++i) {
        if (seq[i] == k)
            continue;

        int l = tree.lca(seq[i], st[top]);

        if (l != st[top]) {
            while (tree.order(l) < tree.order(st[top - 1])) {
                link(st[top], st[top - 1], tree.distance(st[top], st[top - 1]));
                --top;
            }

            if (l != st[top - 1]) {
                vtree[l].clear();
                link(l, st[top], tree.distance(l, st[top]));
                st[top] = l;
            } else {
                link(l, st[top], tree.distance(l, st[top]));
                --top;
            }
        }

        vtree[seq[i]].clear();
        st[++top] = seq[i];
    }

    for (int i = 1; i < top; ++i)
        link(st[i], st[i + 1], tree.distance(st[i], st[i + 1]));
}

void dfs(int x, int fa) {
    f[x] = 0;

    for (auto [y, l] : vtree[x]) {
        if (y == fa)
            continue;

        dfs(y, x);
        f[x] += (key[y] ? l : min(f[y], l));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> k >> q;

    for (int i = 1; i <= m; ++i) {
        int x, y, l;
        cin >> x >> y >> l;
        graph.link(x, y, l);
    }

    dijkstra(k);

    for (int i = 1; i <= n; ++i)
        if (pre[i][0])
            tree.link(pre[i][0], i, pre[i][1]);

    tree.preprocess(k);

    for (int i = 1; i <= q; ++i) {
        int op;
        cin >> op >> num;

        if (op == 0) {
            for (int i = 1; i <= num; ++i) {
                int x;
                cin >> x;
                
                if (key[x])
                    key[x] = false;
                else
                    key[x] = true;
            }
        } else {
            for (int i = 1; i <= num; ++i)
                cin >> seq[i];

            build(seq, num);
            dfs(k, 0);
            cout << (f[k] ? f[k] : -1) << endl;
        }
    }

    return 0;
}