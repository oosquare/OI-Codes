/**
 * æ¥è¯¢ç»ç¹ x çæ·±åº¦ï¼
 * åæ¾å° x çå­æ çæ ¹èç¹å¨åæ ä¸­çå¯¹åºä½ç½® rt,è®¾ x å¨å¶å­æ åçæåä¸º kï¼å­æ å¨ç¬¬ i æ¬¡è¢«æ·»å ï¼åå¨ä¸»å¸­æ ä¸äºåæ¾å°å¯¹åºç»ç¹ x1 ï¼æ¥è¯¢çæ¬ i ç dfn[x1] ä½ç½®çå¼ã
 * æ·»å å­æ  (fr, to), è®¾æ¯ç¬¬ i æ¬¡ï¼
 * ä»çæ¬ 1 å¤å¶åºçæ¬ i + 1ï¼æ¥è¯¢ to çæ·±åº¦ï¼å¨çæ¬ i + 1 çåºé´ [dfn[fr], dfn[fr] + size[fr] - 1] ä¸å ä¸ to çæ·±åº¦ã
 */

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

constexpr int maxn = 1e5 + 10;

struct SubTree {
    long long l, r, fr, to;
};

struct Tree {
    vector<int> tree[maxn];
    int size[maxn], dep[maxn], step[maxn][18];
    int timer, dfn[maxn], rev[maxn];

    void link(int x, int y) {
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    void preprocess() {
        dfs(1, 1);
    }

    void dfs(int x, int fa) {
        size[x] = 1;
        dep[x] = dep[fa] + 1;
        dfn[x] = ++timer;
        rev[timer] = x;

        for (int i = 1; i <= 17; ++i)
            step[x][i] = step[step[x][i - 1]][i - 1];

        for (int y : tree[x]) {
            if (y == fa)
                continue;

            step[y][0] = x;
            dfs(y, x);
            size[x] += size[y];
        }
    }

    tuple<int, int, int> lca(int x, int y) {
        if (x == y)
            return {x, -1, -1};

        if (dep[x] > dep[y]) {
            for (int i = 17; i >= 0; --i)
                if (dep[step[x][i]] > dep[y])
                    x = step[x][i];

            if (step[x][0] == y)
                return {y, x, -1};
            else
                x = step[x][0];
        } else if (dep[x] < dep[y]) {
            for (int i = 17; i >= 0; --i)
                if (dep[step[y][i]] > dep[x])
                    y = step[y][i];

            if (step[y][0] == x)
                return {x, -1, y};
            else
                y = step[y][0];
        }

        for (int i = 17; i >= 0; --i) {
            if (step[x][i] != step[y][i]) {
                x = step[x][i];
                y = step[y][i];
            }
        }

        return {step[x][0], x, y};
    }
};

struct PresistentArray {
    struct Node {
        int ls, rs;
        long long sum, add;
    };

    Node tree[maxn * 50];
    int uuid, root[maxn];

    void build(int &x, int l, int r, int a[], int mp[]) {
        x = ++uuid;

        if (l == r) {
            tree[x].sum = a[mp[l]];
            return;
        }

        int mid = (l + r) / 2;
        build(tree[x].ls, l, mid, a, mp);
        build(tree[x].rs, mid + 1, r, a, mp);
    }

    void add(int &now, int pre, int l, int r, int al, int ar, long long v) {
        now = ++uuid;
        tree[now] = tree[pre];

        if (al <= l && r <= ar) {
            tree[now].add += v;
            return;
        }

        int mid = (l + r) / 2;

        if (al <= mid)
            add(tree[now].ls, tree[pre].ls, l, mid, al, ar, v);

        if (mid < ar)
            add(tree[now].rs, tree[pre].rs, mid + 1, r, al, ar, v);
    }

    long long query(int now, int l, int r, int p) {
        if (l == r)
            return tree[now].sum + tree[now].add;

        int mid = (l + r) / 2;

        if (p <= mid)
            return query(tree[now].ls, l, mid, p) + tree[now].add;
        else
            return query(tree[now].rs, mid + 1, r, p) + tree[now].add;
    }
};

struct PresistentSegmentTree {
    struct Node {
        int ls, rs;
        int sum;
    };

    Node tree[maxn * 50];
    int uuid, root[maxn];

    void add(int &now, int pre, int l, int r, int p) {
        now = ++uuid;
        tree[now] = tree[pre];
        ++tree[now].sum;

        if (l == r)
            return;

        int mid = (l + r) / 2;

        if (p <= mid)
            add(tree[now].ls, tree[pre].ls, l, mid, p);
        else
            add(tree[now].rs, tree[pre].rs, mid + 1, r, p);
    }

    int query(int x, int y, int l, int r, int k) {
        if (l == r)
            return l;

        int mid = (l + r) / 2;
        int sum = tree[tree[x].ls].sum - tree[tree[y].ls].sum;

        if (k <= sum)
            return query(tree[x].ls, tree[y].ls, l, mid, k);
        else
            return query(tree[x].rs, tree[y].rs, mid + 1, r, k - sum);
    }
};

int n, m, q, len;
SubTree sub[maxn];
Tree tree, vtree;
PresistentArray arr;
PresistentSegmentTree seg;

int getId(long long x) {
    int l = 1, r = len;

    while (l < r) {
        int mid = (l + r) / 2;

        if (x <= sub[mid].r)
            r = mid;
        else
            l = mid + 1;
    }

    return l;
}

pair<int, int> getPosition(long long x, int id = -1) {
    if (id == -1)
        id = getId(x);

    if (id == 1)
        return {x, id};
    
    int rt = sub[id].fr, rk = x - sub[id].l + 1;
    int l = tree.dfn[rt], r = tree.dfn[rt] + tree.size[rt] - 1;
    int x0 = seg.query(seg.root[r], seg.root[l - 1], 1, n, rk);
    return {x0, id};
}

long long getDepth(long long x) {
    auto [x0, ver] = getPosition(x);
    return arr.query(arr.root[ver], 1, n, tree.dfn[x0]);
}

void add(long long fr, long long to) {
    ++len;
    sub[len] = {sub[len - 1].r + 1, sub[len - 1].r + tree.size[fr], fr, to};
    int l = tree.dfn[fr], r = l + tree.size[fr] - 1;
    arr.add(arr.root[len], arr.root[1], 1, n, l, r, getDepth(to) - getDepth(fr) + 1);
    vtree.link(len, getId(to));
}

long long distance(long long x, long long y) {
    int ix = getId(x), iy = getId(y);
    auto [l, sx, sy] = vtree.lca(ix, iy);
    long long fx = (sx == -1 ? x : sub[sx].to);
    long long fy = (sy == -1 ? y : sub[sy].to);
    int l0 = get<0>(tree.lca(getPosition(fx, l).first, getPosition(fy, l).first));
    long long res = getDepth(x) + getDepth(y) - 2 * arr.query(arr.root[l], 1, n, tree.dfn[l0]);
    return res;
}

int main() {
    freopen("deployment.in", "r", stdin);
    freopen("deployment.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> m >> q;

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        tree.link(x, y);
    }

    len = 1;
    sub[len] = {1, n, 1, 0};
    tree.preprocess();
    arr.build(arr.root[1], 1, n, tree.dep, tree.rev);

    for (int i = 1; i <= n; ++i)
        seg.add(seg.root[i], seg.root[i - 1], 1, n, tree.rev[i]);

    for (int i = 1; i <= m; ++i) {
        long long x, y;
        cin >> x >> y;
        add(y, x);
    }

    vtree.preprocess();

    for (int i = 1; i <= q; ++i) {
        long long x, y;
        cin >> x >> y;
        cout << distance(x, y) << endl;
    }

    return 0;
}
