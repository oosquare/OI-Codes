#include <iostream>
#include <algorithm>
using namespace std;

constexpr int maxn = 5e4 + 10;
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

int n0, n;
Node tree[maxn * 50];
int root, uuid;
pair<int, int> p[maxn];
int st[maxn], top;
int w[maxn], l[maxn], mx;
long long f[maxn];

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

    if (s.calc(l) < tree[x].seg.calc(l) && s.calc(r) < tree[x].seg.calc(r)) {
        tree[x].seg = s;
        return;
    }

    if (s.calc(l) >= tree[x].seg.calc(l) && s.calc(r) >= tree[x].seg.calc(r))
        return;

    int mid = (l + r) / 2;

    if (s.k > tree[x].seg.k) {
        if (s.calc(mid) < tree[x].seg.calc(mid)) {
            modify(tree[x].rs, mid + 1, r, tree[x].seg);
            tree[x].seg = s;
        } else {
            modify(tree[x].ls, l, mid, s);
        }
    } else {
        if (s.calc(mid) < tree[x].seg.calc(mid)) {
            modify(tree[x].ls, l, mid + 1, tree[x].seg);
            tree[x].seg = s;
        } else {
            modify(tree[x].rs, mid + 1, r, s);
        }
    }
}

long long query(int x, int l, int r, int p) {
    if (!x)
        return oo;

    if (l == r)
        return tree[x].seg.calc(l);

    int mid = (l + r) / 2;

    if (p <= mid)
        return min(tree[x].seg.calc(p), query(tree[x].ls, l, mid, p));
    else
        return min(tree[x].seg.calc(p), query(tree[x].rs, mid + 1, r, p));
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n0;

    for (int i = 1; i <= n0; ++i) {
        cin >> p[i].first >> p[i].second;
        mx = max(mx, max(p[i].first, p[i].second));
    }

    sort(p + 1, p + 1 + n0);

    for (int i = 1; i <= n0; ++i) {
        while (top && p[st[top]].second <= p[i].second)
            --top;

        st[++top] = i;
    }

    n = top;

    for (int i = 1; i <= n; ++i) {
        w[i] = p[st[i]].first;
        l[i] = p[st[i]].second;
    }

    modify(root, 1, mx, {l[1], 0});

    for (int i = 1; i <= n; ++i) {
        f[i] = query(root, 1, mx, w[i]);
        modify(root, 1, mx, {l[i + 1], f[i]});
    }

    cout << f[n] << endl;
    return 0;
}