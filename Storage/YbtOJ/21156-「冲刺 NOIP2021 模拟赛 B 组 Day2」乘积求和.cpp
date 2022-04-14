#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long;

constexpr int maxn = 4e4 + 10;
constexpr ll mod = 1e12 + 7;

struct Node {
    int left, right;
    ll sum;
};

int n, d;
ll a[maxn], sum[maxn], ans;
vector<ll> val;
Node tree[maxn * 4];

inline ll add(ll x, ll y) {
    x += y;

    if (x >= mod)
        x -= mod;

    return x;
}

inline ll sub(ll x, ll y) {
    x = x - y + mod;

    if (x >= mod)
        x -= mod;

    return x;
}

inline ll multiply(ll x, ll y) {
    ll res = 0;

    for (; y; y /= 2) {
        if (y % 2)
            res = add(res, x);

        x = add(x, x);
    }

    return res;
}

void discretize() {
    for (int i = 1; i <= n; ++i)
        val.push_back(a[i]);

    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());

    for (int i = 1; i <= n; ++i)
        a[i] = lower_bound(val.begin(), val.end(), a[i]) - val.begin() + 1;

    for (int i = 1; i <= n; ++i)
        sum[i] = add(sum[i - 1], val[i - 1]);

    d = val.size();
}

inline void pushup(int x) {
    tree[x].sum = add(tree[x * 2].sum, tree[x * 2 + 1].sum);
}

void build(int x, int l, int r) {
    tree[x].left = l;
    tree[x].right = r;

    if (l == r)
        return;

    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
}

void add(int x, int p, ll v) {
    if (tree[x].left == tree[x].right) {
        tree[x].sum = add(tree[x].sum, multiply(val[tree[x].left - 1], v));
        return;
    }

    int mid = (tree[x].left + tree[x].right) / 2;

    if (p <= mid)
        add(x * 2, p, v);
    else
        add(x * 2 + 1, p, v);

    pushup(x);
}

ll query(int x, int l, int r) {
    if (l <= tree[x].left && tree[x].right <= r)
        return tree[x].sum;

    int mid = (tree[x].left + tree[x].right) / 2;
    ll res = 0;

    if (l <= mid)
        res = add(res, query(x * 2, l, r));

    if (mid < r)
        res = add(res, query(x * 2 + 1, l, r));

    return res;
}

int main() {
    freopen("multiplication.in", "r", stdin);
    freopen("multiplication.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    discretize();
    build(1, 1, d);

    for (int i = 1; i <= n; ++i) {
        ll mul = multiply(val[a[i] - 1], query(1, a[i] + 1, d));
        mul = multiply(mul, n - i + 1);
        ans = add(ans, mul);
        add(1, a[i], i);
    }

    cout << ans << endl;
    return 0;
}
