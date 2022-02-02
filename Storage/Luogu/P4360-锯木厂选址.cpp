#include <iostream>
using namespace std;

constexpr int maxn = 20000 + 10;
constexpr int oo = 0x3f3f3f3f;

struct Segment {
    int k, b;

    int calc(int x) const {
        return k * x + b;
    }
};

struct Node {
    int ls, rs;
    Segment seg;
};

int n;
int w[maxn], d[maxn], mx;
Node tree[maxn * 50];
int root, uuid;
int sum[maxn], f[maxn], ans = oo;

void modify(int &x, int l, int r, const Segment &s) {
    if (!x) {
        x = ++uuid;
        tree[x].seg = s;
        return;
    }

    if (l == r) {
        if (s.calc(l) < tree[x].seg.calc(l))
            tree[x].seg = s;

        return;
    }

    int mid = (l + r) / 2;

    if (s.k > tree[x].seg.k) {
        if (s.calc(mid) < tree[x].seg.calc(mid)) {
            modify(tree[x].rs, mid + 1, r, tree[x].seg);
            tree[x].seg = s;
        } else {
            modify(tree[x].ls, l, mid, s);
        }
    } else if (s.k < tree[x].seg.k) {
        if (s.calc(mid) < tree[x].seg.calc(mid)) {
            modify(tree[x].ls, l, mid, tree[x].seg);
            tree[x].seg = s;
        } else {
            modify(tree[x].rs, mid + 1, r, s);
        }
    } else {
        if (s.b < tree[x].seg.b)
            tree[x].seg = s;
    }
}

int query(int x, int l, int r, int p) {
    int res = (x == 0 ? oo : tree[x].seg.calc(p));

    if (!x || l == r)
        return res;

    int mid = (l + r) / 2;

    if (p <= mid)
        return min(res, query(tree[x].ls, l, mid, p));
    else
        return min(res, query(tree[x].rs, mid + 1, r, p));
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> w[i] >> d[i + 1];
        d[i + 1] += d[i];
        sum[i] = sum[i - 1] + d[i] * w[i];
        w[i] += w[i - 1];
    }

    mx = d[n + 1];
    w[n + 1] = w[n];
    sum[n + 1] = sum[n];

    for (int i = 1; i <= n; ++i)
        modify(root, 0, mx, {-w[i], d[i] * w[i]});

    for (int i = 2; i <= n; ++i)
        f[i] = query(root, 0, mx, d[i]) - sum[i] + d[i] * w[i];

    for (int i = 2; i <= n; ++i)
        ans = min(ans, f[i] + d[n + 1] * (w[n + 1] - w[i]) - sum[n + 1] + sum[i]);

    cout << ans << endl;
    return 0;
}