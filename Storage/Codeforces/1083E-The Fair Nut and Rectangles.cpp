#include <iostream>
#include <algorithm>
using namespace std;

constexpr int maxn = 1e6 + 10;
constexpr long long oo = 0x3f3f3f3f3f3f3f3f;

struct Segment {
    int k;
    long long b;

    long long calc(int x) const {
        return 1ll * k * x + b;
    }
};

struct Point {
    int x, y;
    long long a;

    bool operator<(const Point &rhs) const {
        return x < rhs.x;
    }
};

struct Node {
    int ls, rs;
    Segment seg;
};

int n, mx;
Node tree[maxn * 10];
int root, uuid;
Point p[maxn];
long long f[maxn], ans;

void modify(int &x, int l, int r, const Segment &s) {
    if (!x) {
        x = ++uuid;
        tree[x].seg = s;
        return;
    }

    if (s.calc(l) > tree[x].seg.calc(l) && s.calc(r) > tree[x].seg.calc(r)) {
        tree[x].seg = s;
        return;
    }

    if (s.calc(l) <= tree[x].seg.calc(l) && s.calc(r) <= tree[x].seg.calc(r))
        return;

    int mid = (l + r) / 2;

    if (s.k > tree[x].seg.k) {
        if (s.calc(mid) > tree[x].seg.calc(mid)) {
            modify(tree[x].ls, l, mid, tree[x].seg);
            tree[x].seg = s;
        } else {
            modify(tree[x].rs, mid + 1, r, s);
        }
    } else {
        if (s.calc(mid) > tree[x].seg.calc(mid)) {
            modify(tree[x].rs, mid + 1, r, tree[x].seg);
            tree[x].seg = s;
        } else {
            modify(tree[x].ls, l, mid, s);
        }
    }
}

long long query(int x, int l, int r, int p) {
    if (!x)
        return -oo;

    if (l == r)
        return tree[x].seg.calc(p);

    int mid = (l + r) / 2;

    if (p <= mid)
        return max(tree[x].seg.calc(p), query(tree[x].ls, l, mid, p));
    else
        return max(tree[x].seg.calc(p), query(tree[x].rs, mid + 1, r, p));
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> p[i].x >> p[i].y >> p[i].a;
        mx = max(mx, p[i].y);
    }

    sort(p + 1, p + 1 + n);
    modify(root, 0, mx, {0, 0});

    for (int i = 1; i <= n; ++i) {
        f[i] = query(root, 0, mx, p[i].y) - p[i].a + 1ll * p[i].x * p[i].y;
        modify(root, 0, mx, {-p[i].x, f[i]});
        ans = max(ans, f[i]);
    }

    cout << ans << endl;
    return 0;
}