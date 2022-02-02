#include <iostream>
#include <cmath>
using namespace std;

constexpr int maxx = 40000 + 10;
constexpr double eps = 1e-6;

struct Segment {
    double k, b;
    int id = 0x3f3f3f3f;

    double calc(int x) const {
        return k * x + b;
    }
};

struct Node {
    int left, right;
    Segment seg;

    bool isLeaf() const {
        return left == right;
    }
};

int n, tot, ans;
Node tree[maxx * 4];

void build(int x, int l, int r) {
    tree[x].left = l;
    tree[x].right = r;

    if (l == r)
        return;

    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
}

void modify(int x, int l, int r, const Segment &s) {
    int mid = (tree[x].left + tree[x].right) / 2;

    if (l <= tree[x].left && tree[x].right <= r) {
        if (tree[x].seg.id == 0) {
            tree[x].seg = s;
            return;
        }

        double vl1 = tree[x].seg.calc(tree[x].left), vr1 = tree[x].seg.calc(tree[x].right);
        double vl2 = s.calc(tree[x].left), vr2 = s.calc(tree[x].right);

        if (vl2 - vl1 > eps && vr2 - vr1 > eps) {
            tree[x].seg = s;
            return;
        } else if (vl1 - vl2 > eps && vr1 - vr2 > eps) {
            return;
        }

        double vm1 = tree[x].seg.calc(mid), vm2 = s.calc(mid);

        if (s.k - tree[x].seg.k > eps) {
            if (vm2 - vm1 > eps) {
                if (!tree[x].isLeaf())
                    modify(x * 2, l, r, tree[x].seg);

                tree[x].seg = s;
            } else {
                if (!tree[x].isLeaf())
                    modify(x * 2 + 1, l, r, s);
            }
        } else {
            if (vm2 - vm1 > eps) {
                if (!tree[x].isLeaf())
                    modify(x * 2 + 1, l, r, tree[x].seg);

                tree[x].seg = s;
            } else {
                if (!tree[x].isLeaf())
                    modify(x * 2, l, r, s);
            }
        }

        return;
    }

    if (l <= mid)
        modify(x * 2, l, r, s);

    if (mid < r)
        modify(x * 2 + 1, l, r, s);
}

Segment query(int x, int p) {
    if (tree[x].left == tree[x].right)
        return tree[x].seg;

    int mid = (tree[x].left + tree[x].right) / 2;
    Segment res;

    if (p <= mid)
        res = query(x * 2, p);
    else
        res = query(x * 2 + 1, p);

    if (tree[x].seg.calc(p) - res.calc(p) > eps)
        res = tree[x].seg;
    else if (abs(tree[x].seg.calc(p) - res.calc(p)) < eps && res.id > tree[x].seg.id)
        res = tree[x].seg;

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    build(1, 1, 39989);

    for (int i = 1; i <= n; ++i) {
        int op;
        cin >> op;

        if (op == 0) {
            int k;
            cin >> k;
            k = (k + ans - 1) % 39989 + 1;
            ans = query(1, k).id;

            if (ans == 0x3f3f3f3f)
                ans = 0;

            cout << ans << endl;
        } else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1 = (x1 + ans - 1) % 39989 + 1;
            y1 = (y1 + ans - 1) % 1000000000 + 1;
            x2 = (x2 + ans - 1) % 39989 + 1;
            y2 = (y2 + ans - 1) % 1000000000 + 1;

            if (x1 > x2) {
                swap(x1, x2);
                swap(y1, y2);
            }
            
            Segment s;
            s.k = (x1 == x2 ? 0.0 : 1.0 * (y1 - y2) / (x1 - x2));
            s.b = y1 - s.k * x1;
            s.id = ++tot;
            modify(1, x1, x2, s);
        }
    }

    return 0;
}