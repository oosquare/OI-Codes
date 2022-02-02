#include <iostream>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr long long oo = 0x3f3f3f3f3f3f3f3f;

struct Segment {
    long long k, b;

    long long calc(int x) const {
        return k * x + b;
    }
};

struct Node {
    int ls, rs;
    Segment seg;
};

int n, h[maxn], w[maxn], mx;
Node tree[maxn * 20];
int root, uuid;
long long f[maxn], ans;

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

long long query(int x, int l, int r, int p) {
    long long res = (x == 0 ? oo : tree[x].seg.calc(p));

    if (l == r)
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
        cin >> h[i];
        mx = max(mx, h[i]);
    }

    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
        ans += w[i];
    }

    f[1] = -w[1];
    modify(root, 0, mx, {-2ll * h[1], f[1] + 1ll * h[1] * h[1]});

    for (int i = 2; i <= n; ++i) {
        f[i] = query(root, 0, mx, h[i]) + 1ll * h[i] * h[i] - w[i];
        modify(root, 0, mx, {-2ll * h[i], f[i] + 1ll * h[i] * h[i]});
    }

    ans += f[n];
    cout << ans << endl;
    return 0;
}