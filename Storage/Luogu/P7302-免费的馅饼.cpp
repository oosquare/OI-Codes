#include <iostream>
#include <algorithm>
using namespace std;

constexpr int maxn = 1e5 + 10;

struct Pie {
    int t, p, v;
    int x, y;
};

struct Node {
    int ls, rs;
    int max;
};

int n, w, mx;
Pie pie[maxn];
Node tree[maxn * 20];
int root, uuid;
int f[maxn];

void modify(int &x, int l, int r, int p, int v) {
    if (!x)
        x = ++uuid;

    tree[x].max = max(tree[x].max, v);

    if (l == r)
        return;

    int mid = (l + r) / 2;

    if (p <= mid)
        modify(tree[x].ls, l, mid, p, v);
    else
        modify(tree[x].rs, mid + 1, r, p, v);
}

int query(int x, int l, int r, int ql, int qr) {
    if (!x)
        return 0;

    if (ql <= l && r <= qr)
        return tree[x].max;

    int mid = (l + r) / 2, res = 0;

    if (ql <= mid)
        res = max(res, query(tree[x].ls, l, mid, ql, qr));

    if (mid < qr)
        res = max(res, query(tree[x].rs, mid + 1, r, ql, qr));

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> w >> n;

    for (int i = 1; i <= n; ++i) {
        auto &[t, p, v, x, y] = pie[i];
        cin >> t >> p >> v;
        x = 2 * t - p;
        y = 2 * t + p;
        mx = max(mx, y);
    }

    sort(pie + 1, pie + 1 + n, [](const Pie &l, const Pie &r) {
        return l.x < r.x;
    });

    for (int i = 1; i <= n; ++i) {
        f[i] = query(root, 0, mx, 0, pie[i].y) + pie[i].v;
        modify(root, 0, mx, pie[i].y, f[i]);
    }

    cout << query(root, 0, mx, 0, mx) << endl;
    return 0;
}