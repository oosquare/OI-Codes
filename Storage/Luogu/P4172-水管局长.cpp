#include <iostream>
#include <map>
#include <stack>
using namespace std;

constexpr int maxn = 1e3 + 10;
constexpr int maxm = 1e5 + 10;
constexpr int oo = 0x3f3f3f3f;

struct Node {
    int ls, rs, fa, size;
    bool rev;
    int key, max, pos;

    int &operator[](int x) {
        return (x == 0 ? ls : rs);
    }
};

struct Edge {
    int x, y, w;
};

int n, m, q;
Node tree[maxn + maxm];
int st[maxn + maxm];
Edge edges[maxm];
int op[maxm][3];
bool destory[maxm];
map<pair<int, int>, int> mp;
stack<int> ans;

void pushup(int x) {
    tree[x].max = tree[x].key;
    tree[x].pos = x;

    if (tree[x].ls && tree[tree[x].ls].max > tree[x].max) {
        tree[x].max = tree[tree[x].ls].max;
        tree[x].pos = tree[tree[x].ls].pos;
    }

    if (tree[x].rs && tree[tree[x].rs].max > tree[x].max) {
        tree[x].max = tree[tree[x].rs].max;
        tree[x].pos = tree[tree[x].rs].pos;
    }
}

void update(int x) {
    tree[x].rev ^= 1;
    swap(tree[x].ls, tree[x].rs);
}

void pushdown(int x) {
    if (tree[x].rev) {
        if (tree[x].ls)
            update(tree[x].ls);

        if (tree[x].rs)
            update(tree[x].rs);

        tree[x].rev = false;
    }
}

int which(int x) {
    return tree[tree[x].fa].rs == x;
}

bool isRoot(int x) {
    return tree[tree[x].fa].ls != x && tree[tree[x].fa].rs != x;
}

void rotate(int x) {
    int y = tree[x].fa, z = tree[y].fa, k = which(x), w = tree[x][k ^ 1];

    if (!isRoot(y))
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
    int top = 0;
    st[++top] = x;

    for (int y = x; !isRoot(y); y = tree[y].fa)
        st[++top] = tree[y].fa;

    while (top)
        pushdown(st[top--]);

    for (int y; y = tree[x].fa, !isRoot(x); rotate(x))
        if (!isRoot(y))
            rotate(which(x) == which(y) ? y : x);
}

void access(int x) {
    for (int s = 0; x; s = x, x = tree[x].fa) {
        splay(x);
        tree[x].rs = s;
        pushup(x);
    }
}

void makeRoot(int x) {
    access(x);
    splay(x);
    update(x);
}

int findRoot(int x) {
    access(x);
    splay(x);
    pushdown(x);

    while (tree[x].ls) {
        x = tree[x].ls;
        pushdown(x);
    }

    splay(x);
    return x;
}

void link(int x, int y) {
    makeRoot(x);

    if (findRoot(y) != x)
        tree[x].fa = y;
}

void cut(int x, int y) {
    makeRoot(x);

    if (findRoot(y) == x && tree[y].fa == x && !tree[y].ls) {
        tree[x].rs = tree[y].fa = 0;
        pushup(x);
    }
}

int split(int x, int y) {
    makeRoot(x);
    access(y);
    splay(y);
    return y;
}

void init(int x, int key) {
    tree[x].ls = tree[x].rs = tree[x].fa = 0;
    tree[x].size = 1;
    tree[x].rev = false;
    tree[x].key = tree[x].max = key;
    tree[x].pos = x;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> q;

    for (int i = 1; i <= n; ++i)
        init(i, -oo);

    for (int i = 1; i <= m; ++i) {
        auto &[x, y, w] = edges[i];
        cin >> x >> y >> w;
        mp[ {x, y}] = mp[ {y, x}] = i;
        init(n + i, w);
    }

    for (int i = 1; i <= q; ++i) {
        cin >> op[i][0] >> op[i][1] >> op[i][2];

        if (op[i][0] == 2)
            destory[mp[ {op[i][1], op[i][2]}]] = true;
    }

    for (int i = 1; i <= m; ++i) {
        if (!destory[i]) {
            auto [x, y, w] = edges[i];

            if (findRoot(x) != findRoot(y)) {
                link(n + i, x);
                link(n + i, y);
            } else {
                int j = tree[split(x, y)].pos - n;

                if (edges[j].w > edges[i].w) {
                    cut(n + j, edges[j].x);
                    cut(n + j, edges[j].y);
                    link(n + i, x);
                    link(n + i, y);
                }
            }
        }
    }

    for (int i = q; i >= 1; --i) {
        auto [t, x, y] = op[i];

        if (t == 1) {
            ans.push(tree[split(x, y)].max);
        } else {
            int id = mp[ {x, y}];

            if (findRoot(x) != findRoot(y)) {
                link(n + id, x);
                link(n + id, y);
            } else {
                int id2 = tree[split(x, y)].pos - n;

                if (edges[id2].w > edges[id].w) {
                    cut(n + id2, edges[id2].x);
                    cut(n + id2, edges[id2].y);
                    link(n + id, x);
                    link(n + id, y);
                }
            }
        }
    }

    while (!ans.empty()) {
        cout << ans.top() << endl;
        ans.pop();
    }

    return 0;
}