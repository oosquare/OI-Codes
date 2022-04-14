#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>
#include <vector>
using namespace std;

constexpr int maxn = 200000 + 10;
constexpr int oo = 0x3f3f3f3f;

struct Node {
    int left, right;
    int val = oo, assign = oo;
};

struct Range {
    int id, left, right;

    bool operator<(const Range &rhs) const {
        return right < rhs.right;
    }
};

int n, m, a[maxn], pos[maxn], pre[maxn];
Node tree[maxn * 4];
vector<int> val;
int ans[maxn];
Range ranges[maxn];

void update(int x, int v) {
    tree[x].assign = min(tree[x].assign, v);
    tree[x].val = min(tree[x].val, v);
}

void build(int x, int l, int r) {
    tree[x].left = l;
    tree[x].right = r;

    if (l == r)
        return;

    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
}

void assign(int x, int l, int r, int v) {
    if (l <= tree[x].left && tree[x].right <= r) {
        update(x, v);
        return;
    }

    int mid = (tree[x].left + tree[x].right) / 2;

    if (l <= mid)
        assign(x * 2, l, r, v);

    if (mid < r)
        assign(x * 2 + 1, l, r, v);
}

int query(int x, int p) {
    if (tree[x].left == tree[x].right)
        return tree[x].val;

    int mid = (tree[x].left + tree[x].right) / 2, res;

    if (p <= mid)
        res = query(x * 2, p);
    else
        res = query(x * 2 + 1, p);

    res = min(res, tree[x].assign);
    return res;
}

void discretize() {
    for (int i = 1; i <= n; ++i)
        val.push_back(a[i]);

    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());

    for (int i = 1; i <= n; ++i)
        a[i] = lower_bound(val.begin(), val.end(), a[i]) - val.begin() + 1;
}

int main() {
    freopen("jewel.in", "r", stdin);
    freopen("jewel.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    for (int i = 1; i <= m; ++i) {
        auto &[id, l, r] = ranges[i];
        id = i;
        cin >> l >> r;
    }

    discretize();

    for (int i = 1; i <= n; ++i) {
        pre[i] = pos[a[i]];
        pos[a[i]] = i;
    }

    sort(ranges + 1, ranges + 1 + m);
    build(1, 1, n);

    for (int i = 1; i <= m; ++i) {
        auto [id, l, r] = ranges[i];
        for (int j = ranges[i - 1].right + 1; j <= r; ++j)
            assign(1, 1, pre[j], j - pre[j]);

        ans[id] = query(1, l);

        if (ans[id] == oo)
            ans[id] = -1;
    }

    for (int i = 1; i <= m; ++i)
        cout << ans[i] << endl;

    return 0;
}
