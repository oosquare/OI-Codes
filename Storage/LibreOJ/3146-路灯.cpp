#include <iostream>
using namespace std;

constexpr int maxn = 3e5 + 10;
constexpr int oo = 0x3f3f3f3f;

struct SegmentTree {
    struct Node {
        int left, right;
        int sum, time, assign;
    } tree[maxn * 4];

    void pushup(int x) {
        tree[x].sum = tree[x * 2].sum + tree[x * 2 + 1].sum;
    }

    void update(int x, int v) {
        tree[x].time = v;
        tree[x].assign = v;
    }

    void pushdown(int x) {
        if (tree[x].assign) {
            update(x * 2, tree[x].assign);
            update(x * 2 + 1, tree[x].assign);
            tree[x].assign = 0;
        }
    }

    void build(int x, int l, int r, char a[]) {
        tree[x].left = l;
        tree[x].right = r;
        if (l == r) {
            tree[x].sum = a[l] - '0';
            return;
        }
        int mid = (l + r) / 2;
        build(x * 2, l, mid, a);
        build(x * 2 + 1, mid + 1, r, a);
        pushup(x);
    }

    void filp(int x, int p) {
        if (tree[x].left == tree[x].right) {
            tree[x].sum ^= 1;
            return;
        }
        int mid = (tree[x].left + tree[x].right) / 2;
        pushdown(x);
        if (p <= mid)
            filp(x * 2, p);
        else
            filp(x * 2 + 1, p);
        pushup(x);
    }

    void assign(int x, int l, int r, int v) {
        if (l <= tree[x].left && tree[x].right <= r) {
            update(x, v);
            return;
        }
        pushdown(x);
        int mid = (tree[x].left + tree[x].right) / 2;
        if (l <= mid)
            assign(x * 2, l, r, v);
        if (mid < r)
            assign(x * 2 + 1, l, r, v);
    }

    int queryStatus(int x, int p) {
        if (tree[x].left == tree[x].right)
            return tree[x].sum;
        int mid = (tree[x].left + tree[x].right) / 2;
        pushdown(x);
        if (p <= mid)
            return queryStatus(x * 2, p);
        else
            return queryStatus(x * 2 + 1, p);
    }

    int queryTime(int x, int p) {
        if (tree[x].left == tree[x].right)
            return tree[x].time;
        int mid = (tree[x].left + tree[x].right) / 2;
        pushdown(x);
        if (p <= mid)
            return queryTime(x * 2, p);
        else
            return queryTime(x * 2 + 1, p);
    }

    int findLeft(int x, int p) {
        if (p < tree[x].left && p > tree[x].right)
            return oo;
        if (tree[x].left == tree[x].right)
            return (tree[x].sum ? tree[x].left : oo);
        int mid = (tree[x].left + tree[x].right) / 2;
        pushdown(x);
        if (p <= mid) {
            return findLeft(x * 2, p);
        } else {
            int res;
            if (tree[x * 2 + 1].sum != tree[x].right - mid)
                res = findLeft(x * 2 + 1, p);
            else
                res = mid + 1;
            if (res == mid + 1)
                res = min(res, findLeft(x * 2, p));
            return res;
        }
    }

    int findRight(int x, int p) {
        if (p < tree[x].left && p > tree[x].right)
            return -oo;
        if (tree[x].left == tree[x].right)
            return (tree[x].sum ? tree[x].left : -oo);
        int mid = (tree[x].left + tree[x].right) / 2;
        pushdown(x);
        if (p > mid) {
            return findRight(x * 2 + 1, p);
        } else {
            int res;
            if (tree[x * 2].sum != mid - tree[x].left + 1)
                res = findRight(x * 2, p);
            else
                res = mid;
            if (res == mid)
                res = max(res, findRight(x * 2 + 1, p));
            return res;
        }
    }
};

struct TreeOfTree {
    struct Node {
        int ls, rs;
        int sum;
    } tree[maxn * 100];

    int len, uuid, root[maxn];

    void init(int len) {
        this->len = len;
    }

    void add(int &x, int l, int r, int p, int v) {
        if (!x)
            x = ++uuid;
        tree[x].sum += v;
        if (l == r)
            return;
        int mid = (l + r) / 2;
        if (p <= mid)
            add(tree[x].ls, l, mid, p, v);
        else
            add(tree[x].rs, mid + 1, r, p, v);
    }

    int query(int x, int l, int r, int ql, int qr) {
        if (!x)
            return 0;
        if (ql <= l && r <= qr)
            return tree[x].sum;
        int mid = (l + r) / 2, res = 0;
        if (ql <= mid)
            res += query(tree[x].ls, l, mid, ql, qr);
        if (mid < qr)
            res += query(tree[x].rs, mid + 1, r, ql, qr);
        return res;
    }

    int lowbit(int x) {
        return x & (-x);
    }

    void add(int l, int r, int x, int y) {
        for (; l <= len; l += lowbit(l))
            add(root[l], 1, len + 1, x, y);
        for (++r; r <= len; r += lowbit(r))
            add(root[r], 1, len + 1, x, -y);
    }

    int query(int x, int y) {
        int res = 0;
        for (; x; x -= lowbit(x))
            res += query(root[x], 1, len + 1, 1, y);
        return res;
    }
};

int n, q;
char s[maxn];
SegmentTree seg;
TreeOfTree arr;

void update(int l, int r, int ed) {
    int las = seg.queryTime(1, l);
    arr.add(l, r, seg.findLeft(1, l), ed - las + 1);
}

int query(int x, int y, int now) {
    int res = arr.query(y - 1, x);
    if (seg.queryStatus(1, y - 1) && seg.findLeft(1, y - 1) <= x)
        res += now - seg.queryTime(1, y - 1);
    return res;
}

void toggle(int x, int now) {
    if (seg.queryStatus(1, x) == 0) {
        int pre = seg.findLeft(1, x - 1);
        if (pre < x)
            update(pre, x - 1, now - 1);
        int suf = seg.findRight(1, x + 1);
        if (suf > x)
            update(x + 1, suf, now - 1);
        seg.filp(1, x);
        seg.assign(1, min(pre, x), max(suf, x), now);
    } else {
        int suf = seg.findRight(1, x);
        update(x, suf, now - 1);
        seg.filp(1, x);
        if (suf > x)
            seg.assign(1, x + 1, suf, now);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;
    cin >> (s + 1);
    seg.build(1, 1, n, s);
    arr.init(n);

    for (int i = 1; i <= q; ++i) {
        cin >> s;

        if (s[0] == 't') {
            int x;
            cin >> x;
            toggle(x, i);
        } else {
            int x, y;
            cin >> x >> y;
            cout << query(x, y, i) << endl;
        }
    }

    return 0;
}