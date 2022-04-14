#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

constexpr int maxn = 1e5 + 10;

class SegmentTree {
public:
    void build(int n, int a[]) {
        build(1, 1, n, a);
    }

    void modify(int p, int v) {
        modify(1, p, v);
    }

    int query(int l, int r) {
        return query(1, l, r);
    }
private:
    struct Node {
        int left, right;
        int sum;
    };

    Node tree[maxn * 4];

    void pushup(int x) {
        tree[x].sum = tree[x * 2].sum + tree[x * 2 + 1].sum;
    }

    void build(int x, int l, int r, int a[]) {
        tree[x].left = l;
        tree[x].right = r;

        if (l == r) {
            tree[x].sum = max(a[l], 0);
            return;
        }

        int mid = (l + r) / 2;
        build(x * 2, l, mid, a);
        build(x * 2 + 1, mid + 1, r, a);
        pushup(x);
    }

    void modify(int x, int p, int v) {
        if (tree[x].left == tree[x].right) {
            tree[x].sum = max(v, 0);
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
        if (l <= tree[x].left && tree[x].right <= r)
            return tree[x].sum;

        int mid = (tree[x].left + tree[x].right) / 2, res = 0;

        if (l <= mid)
            res += query(x * 2, l, r);

        if (mid < r)
            res += query(x * 2 + 1, l, r);

        return res;
    }
};

int n, m, v[maxn], tmp[maxn];
SegmentTree tree[2];

int main() {
    freopen("trade.in", "r", stdin);
    freopen("trade.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        cin >> v[i];

    for (int i = 1; i < n; ++i)
        tmp[i] = v[i + 1] - v[i];

    tree[0].build(n - 1, tmp);

    for (int i = 1; i < n; ++i)
        tmp[i] = v[n - i] - v[n - i + 1];

    tree[1].build(n - 1, tmp);

    for (int i = 1; i <= m; ++i) {
        int o, x, y;
        cin >> o >> x >> y;

        if (o == 1) {
            if (x == y)
                cout << 0 << endl;
            else if (x < y)
                cout << tree[0].query(x, y - 1) << endl;
            else
                cout << tree[1].query(n - x + 1, n - y) << endl;
        } else {
            v[x] = y;
            
            if (x > 1)
                tree[0].modify(x - 1, v[x] - v[x - 1]);

            if (x < n)
                tree[0].modify(x, v[x + 1] - v[x]);

            int x2 = n - x + 1;
            
            if (x2 > 1)
                tree[1].modify(x2 - 1, v[x] - v[x + 1]);

            if (x2 < n)
                tree[1].modify(x2, v[x - 1] - v[x]);
        }
    }

    return 0;
}
