#include <iostream>
using namespace std;

constexpr int maxn = 4e5 + 10;
constexpr int maxm = 2e5 + 10;

struct Node {
    int ls, rs, fa;
    bool rev;

    int &operator[](int x) {
        return (x == 0 ? ls : rs);
    }
};

int n, m;
Node tree[maxn];
int st[maxn];
int edges[maxm][2];
long long cnt[maxm];

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
    for (int y = 0; x; y = x, x = tree[x].fa) {
        splay(x);
        tree[x].rs = y;
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

    if (findRoot(y) == x && tree[y].fa == x && !tree[y].ls)
        tree[x].rs = tree[y].fa = 0;
}

void add0(int l, int r, int v) {
    cnt[l] += v;
    cnt[r + 1] -= v;
}

void add(int l, int r) {
    add0(l, r, 1);
    add0(r + 1, r + 1, -(r - l + 1));
}

int main() {
    ios::sync_with_stdio(false);
    cin >> m;

    for (int i = 1; i <= m; ++i) {
        auto &[x, y] = edges[i];
        cin >> x >> y;
        n = max(n, max(x, y));
    }

    for (int i = 1, j = 1; i <= m; ++i) {
        auto [x, y] = edges[i];

        while (j < i && findRoot(x) == findRoot(y)) {
            cut(edges[j][0], edges[j][1]);
            ++j;
        }

        link(x, y);
        add(j, i);
    }

    for (int i = 1; i <= m; ++i)
        cnt[i] += cnt[i - 1];

    for (int i = 1; i <= m; ++i)
        cnt[i] += cnt[i - 1];

    for (int i = 1; i <= m; ++i)
        cout << 1ll * i * (m - i + 1) - cnt[i] << " ";

    return 0;
}