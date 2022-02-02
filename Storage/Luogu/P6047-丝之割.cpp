#include <iostream>
#include <algorithm>
using namespace std;

constexpr int maxn = 3e5 + 10;
constexpr long long oo = 0x3f3f3f3f3f3f3f3f;

struct Segment {
    int k;
    long long b;

    long long calc(int x) const {
        return 1ll * k * x + b;
    }
};

struct Node {
    int ls, rs;
    Segment seg;
};

int n, m, mx;
int a[maxn], b[maxn], pre[maxn], suf[maxn];
pair<int, int> str[maxn];
int up[maxn], down[maxn];
Node tree[maxn * 50];
int root, uuid;
long long f[maxn];
int st[maxn], top;

void modify(int &x, int l, int r, const Segment &s) {
    if (!x) {
        x = ++uuid;
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
            modify(tree[x].ls, l, mid, tree[x].seg);
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
        return tree[x].seg.calc(p);

    int mid = (l + r) / 2;

    if (p <= mid)
        return min(tree[x].seg.calc(p), query(tree[x].ls, l, mid, p));
    else
        return min(tree[x].seg.calc(p), query(tree[x].rs, mid + 1, r, p));
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }

    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
        mx = max(mx, b[i]);
    }

    for (int i = 1; i <= m; ++i)
        cin >> str[i].first >> str[i].second;

    sort(str + 1, str + 1 + m, [](auto lhs, auto rhs) {
        return lhs.second < rhs.second;
    });

    for (int i = 1; i <= m; ++i) {
        while (top && str[st[top]].first >= str[i].first)
            --top;

        st[++top] = i;
    }

    m = top;

    for (int i = 1; i <= top; ++i) {
        up[i] = str[st[i]].first;
        down[i] = str[st[i]].second;
    }

    for (int i = 1; i <= n; ++i)
        pre[i] = (i == 1 ? a[i] : min(pre[i - 1], a[i]));

    for (int i = n; i >= 1; --i)
        suf[i] = (i == n ? b[i] : min(suf[i + 1], b[i]));

    modify(root, 1, mx, {pre[up[1] - 1], 0});

    for (int i = 1; i <= m; ++i) {
        f[i] = query(root, 1, mx, suf[down[i] + 1]);
        modify(root, 1, mx, {pre[up[i + 1] - 1], f[i]});
    }

    cout << f[m] << endl;
    return 0;
}