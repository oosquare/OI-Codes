#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;

struct Node {
    int max, assign;
};

int n, q;
Node seg[maxn * 4];
vector<int> tree[maxn];
int timer, dfn[maxn], rev[maxn], sze[maxn];

void modify(int x, int l, int r, int ml, int mr, int v) {
    if (ml <= l && r <= mr) {
        seg[x].assign = max(seg[x].assign, v);
        if (l == r)
            seg[x].max = max(seg[x].max, seg[x].assign);
        return;
    }
    int mid = (l + r) / 2;
    if (ml <= mid)
        modify(x * 2, l, mid, ml, mr, v);
    if (mid < mr)
        modify(x * 2 + 1, mid + 1, r, ml, mr, v);
}

int query(int x, int l, int r, int p) {
    if (l == r)
        return seg[x].max;
    int mid = (l + r) / 2;
    if (p <= mid)
        return max(seg[x].assign, query(x * 2, l, mid, p));
    else
        return max(seg[x].assign, query(x * 2 + 1, mid + 1, r, p));
}

void link(int x, int y) {
    tree[x].push_back(y);
}

void dfs(int x, int fa) {
    dfn[x] = ++timer;
    rev[timer] = x;
    sze[x] = 1;
    for (int y : tree[x]) {
        if (y == fa)
            continue;
        dfs(y, x);
        sze[x] += sze[y];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;
    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
        link(y, x);
    }
    dfs(1, 0);
    modify(1, 1, n, 1, n, 1);
    for (int i = 1; i <= q; ++i) {
        char op[2];
        int x;
        cin >> op >> x;
        if (op[0] == 'C') {
            modify(1, 1, n, dfn[x], dfn[x] + sze[x] - 1, dfn[x]);
        } else {
            cout << rev[query(1, 1, n, dfn[x])] << endl;
        }
    }
    return 0;
}