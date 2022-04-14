#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;

struct Node {
    int len, arr[50];
    
    Node() : len(0) {}
};

Node tree[maxn * 4];
int n, q, a[maxn];

Node pushup(Node lhs, Node rhs) {
    Node res;
    int it1 = 1, it2 = 1;
    while (it1 <= lhs.len && it2 <= rhs.len && res.len < 45) {
        ++res.len;
        if (lhs.arr[it1] > rhs.arr[it2]) {
            res.arr[res.len] = lhs.arr[it1];
            ++it1;
        } else {
            res.arr[res.len] = rhs.arr[it2];
            ++it2;
        }
    }
    while (it1 <= lhs.len && res.len < 45) {
        ++res.len;
        res.arr[res.len] = lhs.arr[it1];
        ++it1;
    }
    while (it2 <= rhs.len && res.len < 45) {
        ++res.len;
        res.arr[res.len] = rhs.arr[it2];
        ++it2;
    }
    return res;
}

void build(int x, int l, int r) {
    if (l == r) {
        tree[x].len = 1;
        tree[x].arr[1] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
    tree[x] = pushup(tree[x * 2], tree[x * 2 + 1]);
}

void modify(int x, int l, int r, int p, int v) {
    if (l == r) {
        tree[x].arr[1] = v;
        return;
    }
    int mid = (l + r) / 2;
    if (p <= mid)
        modify(x * 2, l, mid, p, v);
    else
        modify(x * 2 + 1, mid + 1, r, p, v);
    tree[x] = pushup(tree[x * 2], tree[x * 2 + 1]);
}

Node query(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return tree[x];
    int mid = (l + r) / 2;
    Node res;
    if (ql <= mid)
        res = pushup(res, query(x * 2, l, mid, ql, qr));
    if (mid < qr)
        res = pushup(res, query(x * 2 + 1, mid + 1, r, ql, qr));
    return res;
}

int query(int l, int r) {
    Node res = query(1, 1, n, l, r);
    for (int i = 1; i <= res.len - 2; ++i)
        if (res.arr[i] < res.arr[i + 1] + res.arr[i + 2])
            return res.arr[i] + res.arr[i + 1] + res.arr[i + 2];
    return 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("triangle.in", "r", stdin);
    freopen("triangle.out", "w", stdout);
#endif
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    build(1, 1, n);
    for (int i = 1; i <= q; ++i) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            modify(1, 1, n, x, y);
        } else {
            x = max(x, 1);
            y = min(n, y);
            cout << query(x, y) << endl;
        }
    }
    return 0;
}
