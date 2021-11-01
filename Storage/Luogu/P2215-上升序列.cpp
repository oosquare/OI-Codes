#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int maxn = 10000 + 10;
constexpr int maxm = 1000 + 10;

struct Node {
    int left, right;
    int max;
};

int n, m, mx, a[maxn], f[maxn], pre[maxn];
int arr[maxn];
Node tree[maxn * 4];
vector<int> val;

void pushup(int x) {
    tree[x].max = max(tree[x * 2].max, tree[x * 2 + 1].max);
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

void modify(int x, int p, int v) {
    if (tree[x].left == tree[x].right) {
        if (tree[x].max < v)
            tree[x].max = max(tree[x].max, v);

        return;
    }

    int mid = (tree[x].left + tree[x].right) / 2;

    if (p <= mid)
        modify(x * 2, p, v);
    else
        modify(x * 2 + 1, p, v);

    pushup(x);
}


int query(int x, int l, int r) {
    if (l > r)
        return 0;

    if (l <= tree[x].left && tree[x].right <= r)
        return tree[x].max;

    int mid = (tree[x].left + tree[x].right) / 2, res = 0;

    if (l <= mid)
        res = max(res, query(x * 2, l, r));

    if (mid < r)
        res = max(res, query(x * 2 + 1, l, r));

    return res;
}

void discretize() {
    copy(a + 1, a + 1 + n, back_inserter(val));
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());

    for (int i = 1; i <= n; ++i)
        a[i] = lower_bound(val.begin(), val.end(), a[i]) - val.begin() + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    discretize();
    build(1, 1, n);

    for (int i = n; i >= 1; --i) {
        f[i] = query(1, a[i] + 1, n) + 1;
        modify(1, a[i], f[i]);
        mx = max(f[i], mx);
    }

    cin >> m;

    for (int t = 1; t <= m; ++t) {
        int l, last = 0;
        cin >> l;

        if (l > mx) {
            cout << "Impossible" << endl;
            continue;
        }

        for (int i = 1; i <= n && l > 0; ++i) {
            if (f[i] >= l && a[i] > last) {
                cout << val[a[i] - 1] << " ";
                last = a[i];
                --l;
            }
        }
        cout << endl;
    }
    return 0;
}