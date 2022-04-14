#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 10;
const int mod = 1e9 + 9;

struct range {
    int l, r;

    bool operator<(range b) { return l == b.l ? r > b.r : l < b.l; }
};

struct node {
    int sum, mul;
};

int n, m, points[maxn], len, mx;
range ranges[maxn];
// node tree[maxn * 10];
vector<int> tmp;
vector<int> rs[maxn];

int id(int v) {
    return lower_bound(tmp.begin(), tmp.end(), v) - tmp.begin() + 1;
}

int id2(int v) {
    auto it = lower_bound(tmp.begin(), tmp.end(), v);
    return it - tmp.begin() + (*it == v);
}

class SegmentTree {
  public:
    typedef long long type;
    type a[maxn];

    void build(int k, int l, int r) {
        st[k].add = 0;
        st[k].mul = 1;
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        build(k << 1, l, mid);
        build(k << 1 | 1, mid + 1, r);
        pushup(k);
    }

    void pushdown(int k, int l, int r) {
        if (st[k].mul != 1) {
            st[k << 1].add = (st[k << 1].add * st[k].mul) % mod;
            st[k << 1 | 1].add = (st[k << 1 | 1].add * st[k].mul) % mod;
            st[k << 1].mul = (st[k].mul * st[k << 1].mul) % mod;
            st[k << 1 | 1].mul = (st[k].mul * st[k << 1 | 1].mul) % mod;
            st[k << 1].v = (st[k << 1].v * st[k].mul) % mod;
            st[k << 1 | 1].v = (st[k << 1 | 1].v * st[k].mul) % mod;
        }
        if (st[k].add != 0) {
            int mid = (l + r) >> 1;
            int llen = mid - l + 1;
            int rlen = r - mid;
            st[k << 1].add = (st[k << 1].add + st[k].add) % mod;
            st[k << 1 | 1].add = (st[k << 1 | 1].add + st[k].add) % mod;
            st[k << 1].v = (st[k << 1].v + st[k].add * llen % mod) % mod;
            st[k << 1 | 1].v = (st[k << 1 | 1].v + st[k].add * rlen % mod) % mod;
        }
        st[k].add = 0;
        st[k].mul = 1;
    }

    void modifyAdd(int k, int l, int r, int x, int y, type v) {
        if (x <= l && r <= y) {
            st[k].v = (st[k].v + v * (r - l + 1) % mod) % mod;
            st[k].add = (st[k].add + v) % mod;
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(k, l, r);
        if (x <= mid)
            modifyAdd(k << 1, l, mid, x, y, v);
        if (mid < y)
            modifyAdd(k << 1 | 1, mid + 1, r, x, y, v);
        pushup(k);
    }

    void modifyMul(int k, int l, int r, int x, int y, type v) {
        if (x <= l && r <= y) {
            st[k].v = st[k].v * v % mod;
            st[k].add = st[k].add * v % mod;
            st[k].mul = st[k].mul * v % mod;
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(k, l, r);
        if (x <= mid)
            modifyMul(k << 1, l, mid, x, y, v);
        if (mid < y)
            modifyMul(k << 1 | 1, mid + 1, r, x, y, v);
        pushup(k);
    }

    type query(int k, int l, int r, int x, int y) {
        if (x <= l && r <= y)
            return st[k].v;
        int mid = (l + r) >> 1;
        pushdown(k, l, r);
        type res = 0;
        if (x <= mid)
            res = (res + query(k << 1, l, mid, x, y)) % mod;
        if (mid < y)
            res = (res + query(k << 1 | 1, mid + 1, r, x, y)) % mod;
        return res % mod;
    }

  private:
    struct node {
        type v, add, mul;
    };
    node st[maxn * 4];

    void pushup(int k) { st[k].v = (st[k << 1].v + st[k << 1 | 1].v) % mod; }
};

SegmentTree tree;

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("xmasinterval.in", "r", stdin);
    freopen("xmasinterval.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> ranges[i].l >> ranges[i].r;
    for (int i = 1; i <= m; ++i)
        cin >> points[i];
    for (int i = 1; i <= m; ++i)
        tmp.push_back(points[i]);
    sort(tmp.begin(), tmp.end());
    sort(ranges + 1, ranges + 1 + n);
    for (int i = 1; i <= n; ++i)
        ranges[i].l = id(ranges[i].l), ranges[i].r = id2(ranges[i].r);

    //    for (int i = 1; i <= m; ++i)
    //        points[i] = id(points[i]), mx = max(mx, points[i]);
    for (int i = 1; i <= n; ++i)
        rs[ranges[i].l].push_back(ranges[i].r);
    len = m;
    tree.build(1, 0, len);
    tree.modifyAdd(1, 0, len, 0, 0, 1);
    for (int i = 1; i <= n; ++i) {
        int l = ranges[i].l, r = ranges[i].r;
        int DJ = tree.query(1, 0, len, l - 1, r);
        tree.modifyAdd(1, 0, len, r, r, DJ);
        tree.modifyMul(1, 0, len, r + 1, len, 2);
    }
    cout << tree.query(1, 0, len, len, len) << endl;
    return 0;
}
