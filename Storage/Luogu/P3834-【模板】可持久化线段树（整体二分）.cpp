#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 200000 + 10;
constexpr int oo = 0x3f3f3f3f;

struct num {
    int v, p;
};

struct querys {
    int l, r, k, id;
};

vector<num> ns;
vector<querys> qs;
int n, m, minv = oo, maxv = -oo, ans[maxn], bitree[maxn];

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

void (const vector<num> &ns, const vector<querys> qs, int l, int r) {
    if (l == r) {
        for (auto i : qs)
            ans[i.id] = l;
        return;
    }
    int mid = (l + r) / 2;
    vector<num> nsl, nsr;
    vector<querys> qsl, qsr;
    for (auto i : ns) {
        if (i.v <= mid)
            nsl.push_back(i), add(i.p, 1);
        else
            nsr.push_back(i);
    }
    for (auto i : qs) {
        int t = query(i.r) - query(i.l - 1);
        if (i.k <= t)
            qsl.push_back(i);
        else
            i.k -= t, qsr.push_back(i);
    }
    for (auto i : nsl)
        init(i.p);
    (nsl, qsl, l, mid);
    (nsr, qsr, mid + 1, r);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        minv = min(minv, x);
        maxv = max(maxv, x);
        ns.push_back({x, i});
    }
    for (int i = 1; i <= m; ++i) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        qs.push_back({l, r, k, i});
    }
    (ns, qs, minv, maxv);
    for (int i = 1; i <= m; ++i)
        printf("%d\n", ans[i]);
    return 0;
}