#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 300000 + 10;

struct Node {
    int left, right;
    int id, sum;
};

struct Range {
    int left, right;
};

int n, ans;
Node tree[maxn * 4];
vector<int> val;
Range range[maxn];
int delta[maxn];

void pushup(int x) {
    if (tree[x * 2].id == tree[x * 2 + 1].id)
        tree[x].id = tree[x * 2].id;
    else
        tree[x].id = 0;
    tree[x].sum = tree[x * 2].sum + tree[x * 2 + 1].sum;
}

void build(int x, int l, int r) {
    tree[x].left = l;
    tree[x].right = r;
    if (l == r - 1)
        return;
    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid, r);
}

void modify(int x, int l, int r, int v) {
    if (tree[x].left == tree[x].right - 1) {
        if (tree[x].id == 0) {
            tree[x].id = v;
            delta[v] += val[tree[x].right - 1] - val[tree[x].left - 1];
            tree[x].sum = val[tree[x].right - 1] - val[tree[x].left - 1];
        } else if (tree[x].id != -1) {
            delta[tree[x].id] -= val[tree[x].right - 1] - val[tree[x].left - 1];
            tree[x].id = -1;
        }
        return;
    }
    if (l <= tree[x].left && tree[x].right <= r) {
        if (tree[x].id == -1) {
            return;
        }
    }
    int mid = (tree[x].left + tree[x].right) / 2;
    if (l < mid)
        modify(x * 2, l, r, v);
    if (mid < r)
        modify(x * 2 + 1, l, r, v);
    pushup(x);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        auto &[l, r] = range[i];
        cin >> l >> r;
        val.push_back(l);
        val.push_back(r);
    }
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    for (int i = 1; i <= n; ++i) {
        auto &[l, r] = range[i];
        l = lower_bound(val.begin(), val.end(), l) - val.begin() + 1;
        r = lower_bound(val.begin(), val.end(), r) - val.begin() + 1;
    }
    build(1, 1, val.size());
    for (int i = 1; i <= n; ++i) {
        auto &[l, r] = range[i];        
        modify(1, l, r, i);
    }
    for (int i = 1; i <= n; ++i)
        ans = max(ans, tree[1].sum - delta[i]);
    cout << ans << endl;
    return 0;
}