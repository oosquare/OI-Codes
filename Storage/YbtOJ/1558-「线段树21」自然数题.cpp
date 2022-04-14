#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int maxn = 200000 + 10;

struct Node {
    ll sum, assign, max;
};

Node tree[maxn * 4];
int n, a[maxn], mex0[maxn], nxt[maxn];
unordered_map<int, int> s;
ll ans;

void update(int x, int l, int r, ll v) {
    tree[x].sum = (r - l + 1) * v;
    tree[x].assign = v;
    tree[x].max = v;
}

void pushup(int x) {
    tree[x].assign = -1;
    tree[x].sum = tree[x * 2].sum + tree[x * 2 + 1].sum;
    tree[x].max = max(tree[x * 2].max, tree[x * 2 + 1].max);
}

void pushdown(int x, int l, int r) {
    if (tree[x].assign == -1)
        return;
    int mid = (l + r) / 2;
    update(x * 2, l, mid, tree[x].assign);
    update(x * 2 + 1, mid + 1, r, tree[x].assign);
    tree[x].assign = -1;
}

void modify(int x, int l, int r, int ml, int mr, ll v) {
    if (ml <= l && r <= mr) {
        update(x, l, r, v);
        return;
    }
    pushdown(x, l, r);
    int mid = (l + r) / 2;
    if (ml <= mid)
        modify(x * 2, l, mid, ml, mr, v);
    if (mid < mr)
        modify(x * 2 + 1, mid + 1, r, ml, mr, v);
    pushup(x);
}

int find(int x, int l, int r, ll v) {
    if (l == r)
        return l;
    pushdown(x, l, r);
    int mid = (l + r) / 2;
    if (tree[x * 2].max > v)
        return find(x * 2, l, mid, v);
    else
        return find(x * 2 + 1, mid + 1, r, v);
}

void build(int x, int l, int r) {
    if (l == r) {
        tree[x].assign = -1;
        tree[x].sum = mex0[l];
        tree[x].max = mex0[l];
        return;
    }
    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
    pushup(x);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("mex.in", "r", stdin);
    freopen("mex.out", "w", stdout);
#endif
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        s[a[i]] = 1;
        mex0[i] = mex0[i - 1];
        if (mex0[i] == a[i]) {
            do {
                ++mex0[i];
            } while (s.find(mex0[i]) != s.end());
        }
    }
    s.clear();
    for (int i = n; i >= 1; --i) {
        if (s.find(a[i]) == s.end())
            nxt[i] = n + 1;
        else
            nxt[i] = s[a[i]];
        s[a[i]] = i;
    }
    build(1, 1, n);
    for (int i = 1; i <= n; ++i) {
        ans += tree[1].sum;
        if (tree[1].max > a[i]) {
            int l = find(1, 1, n, a[i]), r = nxt[i] - 1;
            if (l <= r)
                modify(1, 1, n, l, r, a[i]);
        }
        modify(1, 1, n, i, i, 0);
    }
    cout << ans << endl;
    return 0;
}
