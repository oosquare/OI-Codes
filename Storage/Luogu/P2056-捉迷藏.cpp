#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

constexpr int maxn = 1e5 + 10;

struct Tree {
    vector<int> tree[maxn];
    int size[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];

    void link(int x, int y) {
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    vector<int> &operator[](int x) {
        return tree[x];
    }

    void preprocess() {
        dfs(1);
        dfs(1, 1);
    }

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

        if (son[x])
            dfs(son[x], t);

        for (int y : tree[x]) {
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

    int distance(int x, int y) {
        return dep[x] + dep[y] - 2 * dep[lca(x, y)];
    }
};

struct Heap {
    priority_queue<int> a, b;

    void push(int x) {
        a.push(x);
    }

    void pop(int x) {
        b.push(x);
    }

    bool empty() {
        while (!a.empty() && !b.empty() && a.top() == b.top()) {
            a.pop();
            b.pop();
        }

        return a.empty();
    }

    int top() {
        while (!a.empty() && !b.empty() && a.top() == b.top()) {
            a.pop();
            b.pop();
        }

        return a.top();
    }
};

struct Node {
    int fa, max = -1;
    bool on;
    Heap son, sub;

    void update() {
        if (!on) {
            if (son.empty()) {
                max = 0;
            } else {
                int x = son.top();
                max = x;
                son.pop(x);

                if (!son.empty())
                    max += son.top();

                son.push(x);
            }
        } else {
            if (son.empty()) {
                max = -1;
            } else {
                int x = son.top();
                max = 0;
                son.pop(x);

                if (!son.empty())
                    max = x + son.top();

                son.push(x);
            }
        }
    }
};

int n, q;
Tree tree;
Node nodes[maxn];
int sze[maxn], sze2[maxn], root, tot;
bool vis[maxn];
int st[maxn], top;
Heap ans;

void getSize(int x, int fa) {
    sze[x] = 1;

    for (int y : tree[x]) {
        if (y == fa || vis[y])
            continue;

        getSize(y, x);
        sze[x] += sze[y];
    }
}

void getRoot(int x, int fa) {
    sze[x] = 1;
    sze2[x] = 0;

    for (int y : tree[x]) {
        if (y == fa || vis[y])
            continue;

        getRoot(y, x);
        sze[x] += sze[y];
        sze2[x] = max(sze2[x], sze[y]);
    }

    sze2[x] = max(sze2[x], tot - sze[x]);

    if (!root || sze2[x] < sze2[root])
        root = x;
}

void build(int x) {
    vis[x] = true;
    getSize(x, 0);

    for (int y : tree[x]) {
        if (vis[y])
            continue;

        root = 0;
        tot = sze[y];
        getRoot(y, 0);
        nodes[root].fa = x;
        build(root);
    }
}

void add(int x0) {
    nodes[x0].on = false;
    ans.pop(nodes[x0].max);
    nodes[x0].update();
    ans.push(nodes[x0].max);

    for (int x = x0, fa; fa = nodes[x].fa, fa; x = fa) {
        if (!nodes[x].sub.empty()) {
            int v = nodes[x].sub.top();
            nodes[fa].son.pop(v);
        }

        nodes[x].sub.push(tree.distance(fa, x0));
        nodes[fa].son.push(nodes[x].sub.top());

        ans.pop(nodes[fa].max);
        nodes[fa].update();
        ans.push(nodes[fa].max);
    }
}

void del(int x0) {
    nodes[x0].on = true;
    ans.pop(nodes[x0].max);
    nodes[x0].update();
    ans.push(nodes[x0].max);

    for (int x = x0, fa; fa = nodes[x].fa, fa; x = fa) {
        if (!nodes[x].sub.empty()) {
            int v = nodes[x].sub.top();
            nodes[fa].son.pop(v);
        }

        nodes[x].sub.pop(tree.distance(fa, x0));

        if (!nodes[x].sub.empty())
            nodes[fa].son.push(nodes[x].sub.top());

        ans.pop(nodes[fa].max);
        nodes[fa].update();
        ans.push(nodes[fa].max);
    }
}

void filp(int x) {
    if (!nodes[x].on)
        del(x);
    else
        add(x);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        tree.link(x, y);
    }

    tree.preprocess();
    tot = n;
    getRoot(1, 0);
    build(root);

    for (int i = 1; i <= n; ++i) {
        if (nodes[i].fa == 0) {
            root = i;
            break;
        }
    }

    for (int i = 1; i <= n; ++i)
        add(i);

    cin >> q;

    while (q--) {
        char op;
        cin >> op;

        if (op == 'C') {
            int x;
            cin >> x;
            filp(x);
        } else {
            cout << ans.top() << endl;
        }
    }

    return 0;
}