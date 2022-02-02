#include <iostream>
#include <algorithm>
using namespace std;

constexpr int maxn = 20000 + 10;
constexpr int maxk = 100 + 10;
constexpr long long oo = 0x3f3f3f3f3f3f3f3f;

struct Range {
    int l, r, w;

    bool operator<(const Range &rhs) const {
        return r < rhs.r;
    }
};

struct Node {
    int left, right;
    long long min, add;
};

int n, k;
int d[maxn], c[maxn], s[maxn], w[maxn];
Range range[maxn];
Node tree[maxn * 4];
long long suf[maxn];
long long tmp[maxn];
long long arr[maxn];
long long f[maxk][maxn], ans;

void add(int x, long long y) {
    for (; x <= n; x += (x & (-x)))
        arr[x] += y;
}

long long query(int x) {
    int res = 0;

    for (; x; x -= (x & (-x)))
        res += arr[x];

    return res;
}

void pushup(int x) {
    tree[x].min = min(tree[x * 2].min, tree[x * 2 + 1].min);
}

void update(int x, long long v) {
    tree[x].add += v;
    tree[x].min += v;
}

void pushdown(int x) {
    if (tree[x].add) {
        update(x * 2, tree[x].add);
        update(x * 2 + 1, tree[x].add);
        tree[x].add = 0;
    }
}

void build(int x, int l, int r, long long *a) {
    tree[x].left = l;
    tree[x].right = r;
    tree[x].add = 0;

    if (l == r) {
        tree[x].min = a[l];
        return;
    }

    int mid = (l + r) / 2;
    build(x * 2, l, mid, a);
    build(x * 2 + 1, mid + 1, r, a);
    pushup(x);
}

void modify(int x, int p, long long v) {
    if (tree[x].left == tree[x].right) {
        tree[x].min = v;
        return;
    }

    int mid = (tree[x].left + tree[x].right) / 2;
    pushdown(x);

    if (p <= mid)
        modify(x * 2, p, v);
    else
        modify(x * 2 + 1, p, v);

    pushup(x);
}

void add(int x, int l, int r, long long v) {
    if (l <= tree[x].left && tree[x].right <= r) {
        update(x, v);
        return;
    }

    int mid = (tree[x].left + tree[x].right) / 2;
    pushdown(x);

    if (l <= mid)
        add(x * 2, l, r, v);

    if (mid < r)
        add(x * 2 + 1, l, r, v);

    pushup(x);
}

long long query(int x, int l, int r) {
    if (l <= tree[x].left && tree[x].right <= r)
        return tree[x].min;

    int mid = (tree[x].left + tree[x].right) / 2;
    long long res = oo;
    pushdown(x);

    if (l <= mid)
        res = min(res, query(x * 2, l, r));

    if (mid < r)
        res = min(res, query(x * 2 + 1, l, r));

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;

    for (int i = 2; i <= n; ++i)
        cin >> d[i];

    for (int i = 1; i <= n; ++i)
        cin >> c[i];

    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        range[i].l = lower_bound(d + 1, d + n + 1, d[i] - s[i]) - d;
        range[i].r = upper_bound(d + 1, d + n + 1, d[i] + s[i]) - d - 1;
    }

    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
        ans += w[i];
        range[i].w = w[i];
        suf[range[i].l] += w[i];
    }

    for (int i = n; i >= 1; --i)
        suf[i] += suf[i + 1];

    sort(range + 1, range + 1 + n);

    for (int i = 0; i <= k; ++i)
        for (int j = 0; j <= n; ++j)
            f[i][j] = oo;

    f[0][0] = 0;

    for (int i = 1; i <= k; ++i) {
        for (int j = 0; j <= n; ++j)
            tmp[j] = f[i - 1][j];

        for (int j = 1; j <= n; ++j)
            arr[j] = 0;

        build(1, 0, n, tmp);

        for (int j = 1, k = 0; j <= n; ++j) {
            f[i][j] = query(1, 0, j - 1) + query(n) + c[j];
            ans = min(ans, f[i][j] + suf[j + 1]);
            add(1, j, j, -query(j));

            while (k < n && range[k + 1].r <= j) {
                ++k;
                add(range[k].l, range[k].w);
                add(1, range[k].l, j, -range[k].w);
            }
        }
    }

    cout << ans << endl;
    return 0;
}