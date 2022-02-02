#include <iostream>
#include <vector>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr long long oo = 0x3f3f3f3f3f3f3f3f;

struct Segment {
    long long k = 0, b = oo;

    long long calc(int x) const {
        return k * x + b;
    }
};

struct Node {
    int ls, rs;
    Segment seg;
};

int n, a[maxn], b[maxn], mi, mx;
Node nodes[maxn * 100];
int uuid, root[maxn];
vector<int> tree[maxn];
long long f[maxn];

void modify(int &x, int l, int r, const Segment &s) {
    if (!x) {
        x = ++uuid;
        nodes[x].seg = s;
        return;
    }

    if (s.calc(l) >= nodes[x].seg.calc(l) && s.calc(r) >= nodes[x].seg.calc(r))
        return;

    if (s.calc(l) < nodes[x].seg.calc(l) && s.calc(r) < nodes[x].seg.calc(r)) {
        nodes[x].seg = s;
        return;
    }

    int mid = (l + r) >> 1;

    if (s.k > nodes[x].seg.k) {
        if (s.calc(mid) < nodes[x].seg.calc(mid)) {
            modify(nodes[x].rs, mid + 1, r, nodes[x].seg);
            nodes[x].seg = s;
        } else {
            modify(nodes[x].ls, l, mid, s);
        }
    } else if (s.k < nodes[x].seg.k) {
        if (s.calc(mid) < nodes[x].seg.calc(mid)) {
            modify(nodes[x].ls, l, mid, nodes[x].seg);
            nodes[x].seg = s;
        } else {
            modify(nodes[x].rs, mid + 1, r, s);
        }
    } else {
        if (s.b < nodes[x].seg.b)
            nodes[x].seg = s;
    }
}

int merge(int x, int y, int l, int r) {
    if (!x || !y)
        return x ^ y;

    if (l == r) {
        if (nodes[x].seg.calc(l) < nodes[y].seg.calc(l))
            return x;
        else
            return y;
    }

    int mid = (l + r) >> 1;
    nodes[x].ls = merge(nodes[x].ls, nodes[y].ls, l, mid);
    nodes[x].rs = merge(nodes[x].rs, nodes[y].rs, mid + 1, r);
    modify(x, l, r, nodes[y].seg);
    return x;
}

long long query(int x, int l, int r, int p) {
    if (!x)
        return oo;

    if (l == r)
        return nodes[x].seg.calc(p);

    int mid = (l + r) >> 1;

    if (p <= mid)
        return min(nodes[x].seg.calc(p), query(nodes[x].ls, l, mid, p));
    else
        return min(nodes[x].seg.calc(p), query(nodes[x].rs, mid + 1, r, p));
}

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void dfs(int x, int fa) {
    if (tree[x].size() == 1 && fa != 0) {
        modify(root[x], mi, mx, {b[x], 0});
        return;
    }

    for (int y : tree[x]) {
        if (y == fa)
            continue;

        dfs(y, x);
        root[x] = merge(root[x], root[y], mi, mx);
    }

    f[x] = query(root[x], mi, mx, a[x]);
    modify(root[x], mi, mx, {b[x], f[x]});
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        mi = min(mi, a[i]);
        mx = max(mx, a[i]);
    }

    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
        mi = min(mi, b[i]);
        mx = max(mx, b[i]);
    }

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
    }

    dfs(1, 0);

    for (int i = 1; i <= n; ++i)
        cout << f[i] << " ";

    return 0;
}