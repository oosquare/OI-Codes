#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e5 + 10;
constexpr int oo = 0x3f3f3f3f;

int n, arr[maxn], pos[maxn];
long long ans;
int tag[maxn * 10];

struct node {
    int minv, cminv, sminv, csminv;
} tree[maxn * 10];

node pushup(node lhs, node rhs) {
    node ls = lhs;
    if (ls.minv > rhs.minv)
        ls = rhs, rhs = lhs;
    if (ls.sminv < rhs.minv)
        return ls;
    if (rhs.minv == ls.sminv) {
        ls.csminv += rhs.cminv;
        return ls;
    } else if (rhs.minv == ls.minv) {
        ls.cminv += rhs.cminv;
        if (rhs.sminv < ls.sminv)
            return node{ls.minv, ls.cminv, rhs.sminv, rhs.csminv};
        else {
            if (rhs.sminv == ls.sminv)
                ls.csminv += rhs.csminv;
            return ls;
        }
    } else
        return node{ls.minv, ls.cminv, rhs.minv, rhs.cminv};
}

void build(int x, int l, int r) {
    if (l == r) {
        tree[x] = node{0, 1, oo, 1};
        return;
    }

    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
    tree[x] = pushup(tree[x * 2], tree[x * 2 + 1]);
}

void update(int x, int v) {
    tag[x] += v;
    tree[x].minv += v;
    tree[x].sminv += v;
}

void pushdown(int x) {
    if (!tag[x])
        return;
    update(x * 2, tag[x]);
    update(x * 2 + 1, tag[x]);
    tag[x] = 0;
}

void add(int x, int l, int r, int ml, int mr, int v) {
    if (ml <= l && r <= mr)
        return update(x, v);
    pushdown(x);
    int mid = (l + r) / 2;
    if (ml <= mid)
        add(x * 2, l, mid, ml, mr, v);
    if (mr > mid)
        add(x * 2 + 1, mid + 1, r, ml, mr, v);
    tree[x] = pushup(tree[x * 2], tree[x * 2 + 1]);
}

node query(int x, int l, int r, int ql) {
    if (ql <= l)
        return tree[x];
    pushdown(x);
    int mid = (l + r) / 2;
    return ql <= mid ? pushup(query(x * 2, l, mid, ql), tree[x * 2 + 1])
                    : query(x * 2 + 1, mid + 1, r, ql);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("interval.in", "r", stdin);
    freopen("interval.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        pos[arr[i]] = i;
    }
    build(1, 1, n);
    for (int i = n; i >= 1; --i) {
        // print();
        int lv = arr[pos[i] - 1], rv = arr[pos[i] + 1];
        if (lv > rv)
            swap(lv, rv);
        if (rv < i) {
            add(1, 1, n, i, n, 1);
        } else if (lv < i) {
            add(1, 1, n, i, rv - 1, 1);
        } else {
            add(1, 1, n, i, lv - 1, 1);
            add(1, 1, n, rv, n, -1);
        }
        if (i == n)
            continue;
        node res = query(1, 1, n, i + 1);
        if (res.minv <= 2) {
            ans += res.cminv;
            if (res.sminv == 2)
                ans += res.csminv;
        }
    }
    cout << ans << endl;
    return 0;
}
