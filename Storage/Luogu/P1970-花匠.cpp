#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 100000 + 10;

struct SegmentTree {
    struct Node {
        int left, right;
        int max;
    };
    Node tree[maxn * 4];

    void pushup(int x) {
        if (tree[x * 2].max > tree[x * 2 + 1].max)
            tree[x].max = tree[x * 2].max;
        else
            tree[x].max = tree[x * 2 + 1].max;
    }

    void build(int x, int l, int r) {
        tree[x].left = l;
        tree[x].right = r;
        tree[x].max = 0;
        if (l == r)
            return;
        int mid = (l + r) / 2;
        build(x * 2, l, mid);
        build(x * 2 + 1, mid + 1, r);
    }

    void modify(int x, int p, int v) {
        if (tree[x].left == tree[x].right) {
            tree[x].max = max(tree[x].max, v);
            return;
        }
        int mid = (tree[x].left + tree[x].right) / 2;
        if (p <= mid)
            modify(x * 2, p, v);
        else
            modify(x * 2 + 1, p, v);
        pushup(x);
    }

    int query(int x, int l, int r) {
        if (l > r)
            return 0;
        if (l <= tree[x].left && tree[x].right <= r)
            return tree[x].max;
        int res = 0, mid = (tree[x].left + tree[x].right) / 2;
        if (l <= mid)
            res = max(res, query(x * 2, l, r));
        if (mid < r)
            res = max(res, query(x * 2 + 1, l, r));
        return res;
    }
};

int n, h[maxn];
vector<int> val;
int f[maxn][2], ans;
SegmentTree tree[2];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> h[i];
        val.push_back(h[i]);
    }
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    for (int i = 1; i <= n; ++i)
        h[i] = lower_bound(val.begin(), val.end(), h[i]) - val.begin() + 1;

    tree[0].build(1, 1, val.size());
    tree[1].build(1, 1, val.size());
    for (int i = 1; i <= n; ++i) {
        if (i != 1)
            f[i][0] = tree[1].query(1, h[i] + 1, val.size()) + 1;
        f[i][1] = tree[0].query(1, 1, h[i] - 1) + 1;
        tree[0].modify(1, h[i], f[i][0]);
        tree[1].modify(1, h[i], f[i][1]);
    }
    ans = max(ans, max(f[n][0], f[n][1]));

    tree[0].build(1, 1, val.size());
    tree[1].build(1, 1, val.size());
    for (int i = 1; i <= n; ++i) {
        if (i != 1)
            f[i][0] = tree[1].query(1, 1, h[i] - 1) + 1;
        f[i][1] = tree[0].query(1, h[i] + 1, val.size()) + 1;
        tree[0].modify(1, h[i], f[i][0]);
        tree[1].modify(1, h[i], f[i][1]);
    }
    ans = max(ans, max(f[n][0], f[n][1]));

    cout << ans << endl;
    return 0;
}