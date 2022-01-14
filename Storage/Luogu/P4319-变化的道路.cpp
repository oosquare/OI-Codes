#include <iostream>
#include <stack>
#include <vector>
using namespace std;

constexpr int maxn = 5e4 + 10;
constexpr int maxr = 32766 + 10;
constexpr int maxm = 98298 + 10;
constexpr int oo = 0x3f3f3f3f;

struct Edge {
    int x, y, w;
};

int n, m;
Edge edges[maxn + maxm];
long long ans[maxr];

namespace LinkCutTree {

struct Node {
    int ls, rs, fa;
    bool rev;
    int key, max, pos;

    int &operator[](int x) {
        return (x == 0 ? ls : rs);
    }
};

Node tree[(maxn + maxm) * 2];
int st[(maxn + maxm) * 2];

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
    for (int y = 0; x; y = x, x = tree[x].fa) {
        splay(x);
        tree[x].rs = y;
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
    tree[x].rev = false;
    tree[x].key = tree[x].max = key;
    tree[x].pos = x;
}

} // namespace LinkCutTree

namespace SegmentTree {

struct Node {
    int left, right;
    vector<int> id;
};

Node tree[maxr * 4];

void build(int x, int l, int r) {
    tree[x].left = l;
    tree[x].right = r;

    if (l == r)
        return;

    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
}

void insert(int x, int l, int r, int id) {
    if (l <= tree[x].left && tree[x].right <= r) {
        tree[x].id.push_back(id);
        return;
    }

    int mid = (tree[x].left + tree[x].right) / 2;

    if (l <= mid)
        insert(x * 2, l, r, id);

    if (mid < r)
        insert(x * 2 + 1, l, r, id);
}

int add(int id, long long &sum) {
    using LinkCutTree::findRoot;
    using LinkCutTree::link;
    using LinkCutTree::cut;
    using LinkCutTree::split;
    using LinkCutTree::tree;

    auto [x, y, w] = edges[id];

    if (findRoot(x) != findRoot(y)) {
        link(n + id, x);
        link(n + id, y);
        sum += w;

        return 0;
    } else {
        int t = tree[split(x, y)].pos - n;

        if (edges[t].w > w) {
            cut(n + t, edges[t].x);
            cut(n + t, edges[t].y);
            sum -= edges[t].w;

            link(n + id, x);
            link(n + id, y);
            sum += w;

            return t;
        } else {
            return -1;
        }
    }
}


void del(int id, int pre) {
    using LinkCutTree::link;
    using LinkCutTree::cut;

    auto [x, y, w] = edges[id];

    if (pre == 0) {
        cut(n + id, x);
        cut(n + id, y);
    } else if (pre > 0) {
        cut(n + id, x);
        cut(n + id, y);

        link(n + pre, edges[pre].x);
        link(n + pre, edges[pre].y);
    }
}

void solve(int x, long long ans[], long long sum) {
    stack<int> st;

    for (int i = 0; i < (int)tree[x].id.size(); ++i)
        st.push(add(tree[x].id[i], sum));

    if (tree[x].left == tree[x].right) {
        ans[tree[x].left] = sum;
    } else {
        solve(x * 2, ans, sum);
        solve(x * 2 + 1, ans, sum);
    }

    for (int i = (int)tree[x].id.size() - 1; i >= 0; --i) {
        del(tree[x].id[i], st.top());
        st.pop();
    }
}

} // namespace SegmentTree

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    SegmentTree::build(1, 1, 32766);

    for (int i = 1; i < n; ++i) {
        auto &[x, y, w] = edges[i];
        cin >> x >> y >> w;
        SegmentTree::insert(1, 1, 32766, i);
    }

    cin >> m;

    for (int i = n; i <= n + m - 1; ++i) {
        auto &[x, y, w] = edges[i];
        int l, r;
        cin >> x >> y >> w >> l >> r;
        SegmentTree::insert(1, l, r, i);
    }

    for (int i = 1; i <= n; ++i)
        LinkCutTree::init(i, -oo);

    for (int i = 1; i <= n + m - 1; ++i)
        LinkCutTree::init(n + i, edges[i].w);

    SegmentTree::solve(1, ans, 0);

    for (int i = 1; i <= 32766; ++i)
        cout << ans[i] + 1 << endl;

    return 0;
}