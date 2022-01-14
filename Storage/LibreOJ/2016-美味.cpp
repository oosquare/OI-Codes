#include <iostream>
using namespace std;

constexpr int maxn = 2e5 + 10;

struct Node {
    int ls, rs;
    int sum;
};

int n, m, a[maxn];
Node tree[maxn * 50];
int uuid, root[maxn];

void modify(int &x, int y, int l, int r, int p) {
    x = ++uuid;
    tree[x] = tree[y];
    ++tree[x].sum;

    if (l == r)
        return;

    int mid = (l + r) / 2;

    if (p <= mid)
        modify(tree[x].ls, tree[y].ls, l, mid, p);
    else
        modify(tree[x].rs, tree[y].rs, mid + 1, r, p);
}

int query(int x, int y, int l, int r, int ql, int qr) {
    if (!x && !y)
        return 0;

    if (ql <= l && r <= qr)
        return tree[x].sum - tree[y].sum;

    int mid = (l + r) / 2, res = 0;

    if (ql <= mid)
        res += query(tree[x].ls, tree[y].ls, l, mid, ql, qr);

    if (mid < qr)
        res += query(tree[x].rs, tree[y].rs, mid + 1, r, ql, qr);

    return res;
}

int solve(int ql, int qr, int num, int delta) {
    int l = 0, r = 262143, res = 0;
    // 262143 = 2 ^ 18 - 1
    
    for (int i = 17; i >= 0; --i) {
        int w = ((num >> i) & 1), mid = (l + r) / 2;

        if (w == 0) {
            int nl = mid + 1 - delta, nr = r - delta;

            if (nr < 0 || nr > 262143 || !query(root[qr], root[ql - 1], 0, 262143, max(nl, 0), min(nr, 130171))) {
                r = mid;
            } else {
                l = mid + 1;
                res |= (1 << i);
            }
        } else {
            int nl = l - delta, nr = mid - delta;

            if (nr < 0 || nr > 262143 || !query(root[qr], root[ql - 1], 0, 262143, max(nl, 0), min(nr, 262143))) {
                l = mid + 1;
            } else {
                r = mid;
                res |= (1 << i);
            }
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        int a;
        cin >> a;
        modify(root[i], root[i - 1], 0, 262143, a);
    }

    for (int i = 1; i <= m; ++i) {
        int b, x, l, r;
        cin >> b >> x >> l >> r;
        cout << solve(l, r, b, x) << endl;
    }
    
    return 0;
}