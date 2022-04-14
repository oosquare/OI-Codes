#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

constexpr int maxn = 2e5 + 10;
constexpr int mod = 1e9 + 7;

struct Node {
    int left, right;
    int sum, add;
};

int n, k, a[maxn], pos[maxn], pre[maxn], ans;
Node tree[maxn * 4];
vector<int> val;

int power(int x, int y) {
    int res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = 1ll * res * x % mod;

        x = 1ll * x * x % mod;
    }

    return res;
}

inline void pushup(int x) {
    tree[x].sum = (tree[x * 2].sum + tree[x * 2 + 1].sum) % mod;
}

inline void update(int x, int v) {
    tree[x].add = (tree[x].add + v) % mod;
    tree[x].sum = (tree[x].sum + 1ll * (tree[x].right - tree[x].left + 1) * v % mod) % mod;
}

inline void pushdown(int x) {
    if (!tree[x].add)
        return;

    update(x * 2, tree[x].add);
    update(x * 2 + 1, tree[x].add);
    tree[x].add = 0;
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

void modify(int x, int l, int r, int v) {
    if (l <= tree[x].left && tree[x].right <= r) {
        update(x, v);
        return;
    }

    int mid = (tree[x].left + tree[x].right) / 2;
    pushdown(x);

    if (l <= mid)
        modify(x * 2, l, r, v);

    if (mid < r)
        modify(x * 2 + 1, l, r, v);

    pushup(x);
}

int query(int x, int l, int r) {
    if (l <= tree[x].left && tree[x].right <= r)
        return tree[x].sum;

    int mid = (tree[x].left + tree[x].right) / 2, res = 0;
    pushdown(x);

    if (l <= mid)
        res = (res + query(x * 2, l, r)) % mod;

    if (mid < r)
        res = (res + query(x * 2 + 1, l, r)) % mod;

    return res;
}

void discretize() {
    for (int i = 1; i <= 2 * n; ++i)
        val.push_back(a[i]);

    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());

    for (int i = 1; i <= 2 * n; ++i)
        a[i] = lower_bound(val.begin(), val.end(), a[i]) - val.begin() + 1;
}

int main() {
    freopen("loop.in", "r", stdin);
    freopen("loop.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> k;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i + n] = a[i];
    }

    discretize();

    for (int i = 1; i <= 2 * n; ++i) {
        pre[i] = pos[a[i]];
        pos[a[i]] = i;
    }

    build(1, 1, 2 * n);

    for (int i = 1; i <= n; ++i) {
        modify(1, pre[i] + 1, i, 1);
        ans = (ans + 1ll * k * query(1, max(i - n + 2, 1), i) % mod) % mod;
    }

    int res = val.size();
    int s = 1ll * n * k % mod, inv2 = power(2, mod - 2);
    ans = (ans + (1 + 1ll * (s - n + 1)) * (s - n + 1) % mod * inv2 % mod * res % mod) % mod;

    if (k > 1) {
        for (int i = n + 1; i < 2 * n; ++i) {
            modify(1, pre[i] + 1, i, 1);
            ans = (ans + 1ll * (k - 1) * query(1, i - n + 2, n) % mod) % mod;
        }
    }

    cout << ans << endl;

    return 0;
}
