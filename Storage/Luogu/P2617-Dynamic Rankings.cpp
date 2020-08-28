#include <bits/stdc++.h>
using namespace std;

struct op {
    int type, x, y, k, id;
};

constexpr int maxn = 2e5 + 10;
constexpr int oo = 0x3f3f3f3f;

vector<op> ops;
int bitree[maxn], ans[maxn], a[maxn];
int n, m, t, minv = oo, maxv = -oo;

int lowbit(int x) {
    return x & (-x);
}

void init(int p) {
    for (; p <= n; p += lowbit(p))
        if (bitree[p] == 0)
            return;
        else
            bitree[p] = 0;
}

void add(int p, int v) {
    for (; p <= n; p += lowbit(p))
        bitree[p] += v;
}

int query(int p) {
    int res = 0;
    for (; p; p -= lowbit(p))
        res += bitree[p];
    return res;
}

void BinarySolve(const vector<op> &ops, int l, int r) {
    if (ops.size() == 0)
        return;
    if (l == r) {
        for (auto i : ops)
            ans[i.id] = l;
        return;
    }
    int mid = (l + r) / 2;
    vector<op> op1, op2;
    for (auto i : ops) {
        if (i.type == 1) {
            if (i.y <= mid)
                add(i.x, 1), op1.push_back(i);
            else
                op2.push_back(i);
        }
        if (i.type == 2) {
            if (i.y <= mid)
                add(i.x, -1), op1.push_back(i);
            else
                op2.push_back(i);
        }
        if (i.type == 3) {
            int t = query(i.y) - query(i.x - 1);
            if (i.k <= t)
                op1.push_back(i);
            else
                i.k -= t, op2.push_back(i);
        }
    }
    for (auto i : op1)
        if (i.type != 3)
            init(i.x);
    BinarySolve(op1, l, mid);
    BinarySolve(op2, mid + 1, r);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        minv = min(minv, a[i]);
        maxv = max(maxv, a[i]);
        ops.push_back({1, i, a[i], 0, 0});
    }
    for (int i = 1; i <= m; ++i) {
        char ss[10];
        scanf("%s", ss);
        if (ss[0] == 'Q') {
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            ops.push_back({3, l, r, k, ++t});
        } else {
            int p, v;
            scanf("%d%d", &p, &v);
            minv = min(minv, v);
            maxv = max(maxv, v);
            ops.push_back({2, p, a[p], 0, 0});
            ops.push_back({1, p, a[p] = v, 0, 0});
        }
    }
    BinarySolve(ops, minv, maxv);
    for (int i = 1; i <= t; ++i)
        printf("%d\n", ans[i]);
    return 0;
}