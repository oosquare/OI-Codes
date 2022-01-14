#include <iostream>
#include <algorithm>
using namespace std;

constexpr int maxn = 5e4 + 10;
constexpr int maxm = 2e5 + 10;
constexpr int oo = 0x3f3f3f3f;

struct Node {
    int ls, rs, fa, size;
    bool rev;
    int key, min, pos;

    int &operator[](int x) {
        return (x == 0 ? ls : rs);
    }
};

struct Edge {
    int x, y, w;

    bool operator<(const Edge &rhs) const {
        return w < rhs.w;
    }
};

int n, m;
Node tree[maxn + maxm];
int st[maxn + maxm];
Edge edges[maxm];
bool selected[maxm];
int ans = oo;

void pushup(int x) {
    tree[x].min = tree[x].key;
    tree[x].pos = x;

    if (tree[x].ls && tree[tree[x].ls].min < tree[x].min) {
        tree[x].min = tree[tree[x].ls].min;
        tree[x].pos = tree[tree[x].ls].pos;
    }

    if (tree[x].rs && tree[tree[x].rs].min < tree[x].min) {
        tree[x].min = tree[tree[x].rs].min;
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

int find(int x, int y) {
    makeRoot(x);
    access(y);
    splay(y);
    return tree[y].pos;
}

void init(int x, int key) {
    tree[x].ls = tree[x].rs = tree[x].fa = 0;
    tree[x].size = 1;
    tree[x].rev = false;
    tree[x].key = tree[x].min = key;
    tree[x].pos = x;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        init(i, oo);

    for (int i = 1; i <= m; ++i) {
        cin >> edges[i].x >> edges[i].y >> edges[i].w;

        if (edges[i].x == edges[i].y) {
            --m;
            --i;
        }
    }

    sort(edges + 1, edges + 1 + m);

    for (int i = 1; i <= m; ++i)
        init(n + i, edges[i].w);

    for (int i = 1, j = 0, c = 0; i <= m; ++i) {
        auto [x, y, w] = edges[i];

        if (findRoot(x) != findRoot(y)) {
            ++c;
            link(x, n + i);
            link(y, n + i);
            selected[i] = true;
        } else {
            int t = find(x, y) - n;
            cut(edges[t].x, n + t);
            cut(edges[t].y, n + t);
            link(x, n + i);
            link(y, n + i);
            selected[t] = false;
            selected[i] = true;
        }

        while (!selected[j])
            ++j;

        if (c == n - 1)
            ans = min(ans, edges[i].w - edges[j].w);
    }

    cout << ans << endl;
    return 0;
}