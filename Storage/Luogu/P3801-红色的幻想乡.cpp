#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;

struct SegmentTree {

    struct Node {
        int left, right;
        int sum;
    };

    Node tree[maxn * 4];

    void pushup(int root) {
        tree[root].sum = tree[root * 2].sum + tree[root * 2 + 1].sum;
    }

    void build(int root, int left, int right) {
        tree[root].left = left;
        tree[root].right = right;

        if (left == right)
            return;

        int mid = (left + right) / 2;
        build(root * 2, left, mid);
        build(root * 2 + 1, mid + 1, right);
    }

    void filp(int root, int pos) {
        if (tree[root].left == tree[root].right) {
            tree[root].sum ^= 1;
            return;
        }

        int mid = (tree[root].left + tree[root].right) / 2;

        if (pos <= mid)
            filp(root * 2, pos);
        else
            filp(root * 2 + 1, pos);

        pushup(root);
    }

    int query(int root, int left, int right) {
        if (left <= tree[root].left && tree[root].right <= right)
            return tree[root].sum;

        int mid = (tree[root].left + tree[root].right) / 2, res = 0;

        if (left <= mid)
            res += query(root * 2, left, right);

        if (mid < right)
            res += query(root * 2 + 1, left, right);

        return res;
    }

};

int n, m, q;
SegmentTree row, col;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> q;
    row.build(1, 1, n);
    col.build(1, 1, m);

    for (int i = 1; i <= q; ++i) {
        int op;
        cin >> op;

        if (op == 1) {
            int x, y;
            cin >> x >> y;
            row.filp(1, x);
            col.filp(1, y);
        } else {
            long long x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            long long r = row.query(1, x1, x2), c = col.query(1, y1, y2);
            cout << (x2 - x1 + 1) * c + (y2 - y1 + 1) * r - 2 * r * c << endl;
        }
    }

    return 0;
}
