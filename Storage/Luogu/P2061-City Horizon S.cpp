#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 80000 + 10;

using ll = long long;

struct Node {
    int left, right, assign;
};

int n, a[maxn], b[maxn], h[maxn];
Node tree[maxn * 4];
vector<int> tmp;

void build(int x, int l, int r) {
    tree[x] = {l, r, 0};
    if (l == r - 1)
        return;
    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid, r);
}

void modify(int x, int l, int r, int v) {
    if (l <= tree[x].left && tree[x].right <= r) {
        tree[x].assign = max(tree[x].assign, v);
        return;
    }
    int mid = (tree[x].left + tree[x].right) / 2;
    if (l < mid)
        modify(x * 2, l, r, v);
    if (mid < r)
        modify(x * 2 + 1, l, r, v);
}

ll query(int x, int v) {
    if (tree[x].left == tree[x].right - 1) {
        int len = tmp[tree[x].right - 1] - tmp[tree[x].left - 1];
        return 1ll * len * max(tree[x].assign, v);
    }
    v = max(v, tree[x].assign);
    return query(x * 2, v) + query(x * 2 + 1, v);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i] >> b[i] >> h[i];
        tmp.push_back(a[i]);
        tmp.push_back(b[i]);
    }
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
    for (int i = 1; i <= n; ++i) {
        a[i] = lower_bound(tmp.begin(), tmp.end(), a[i]) - tmp.begin() + 1;
        b[i] = lower_bound(tmp.begin(), tmp.end(), b[i]) - tmp.begin() + 1;
    }
    build(1, 1, tmp.size());
    for (int i = 1; i <= n; ++i)
        modify(1, a[i], b[i], h[i]);
    cout << query(1, 0) << endl;
    return 0;
}