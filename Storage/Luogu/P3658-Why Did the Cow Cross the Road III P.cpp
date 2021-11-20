#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long;

constexpr int maxn = 100000 + 10;

struct Info {
    int a, b, c;
};

int n, k, p[2][maxn], pos[maxn];
ll ans[maxn];
Info info[maxn], tmp[maxn];
ll tree[maxn];

inline int lowbit(int x) {
    return x & (-x);
}

void add(int p, int v) {
    for (; p <= n; p += lowbit(p))
        tree[p] += v;
}

ll query(int p) {
    if (p < 1)
        return 0;

    p = min(p, n);
    ll res = 0;

    for (; p; p -= lowbit(p))
        res += tree[p];

    return res;
}

void cdq1(int l, int r) {
    if (l >= r)
        return;

    int mid = (l + r) / 2, it = l - 1, it1 = l, it2 = mid + 1;
    cdq1(l, mid);
    cdq1(mid + 1, r);

    while (it1 <= mid && it2 <= r) {
        if (info[it1].b > info[it2].b) {
            add(info[it1].c, 1);
            tmp[++it] = info[it1++];
        } else {
            ans[info[it2].a] += query(n) - query(info[it2].c + k);
            tmp[++it] = info[it2++];
        }
    }

    while (it1 <= mid) {
        add(info[it1].c, 1);
        tmp[++it] = info[it1++];
    }

    while (it2 <= r) {
        ans[info[it2].a] += query(n) - query(info[it2].c + k);
        tmp[++it] = info[it2++];
    }

    for (int i = l; i <= mid; ++i)
        add(info[i].c, -1);

    for (int i = l; i <= r; ++i)
        info[i] = tmp[i];
}

void cdq2(int l, int r) {
    if (l >= r)
        return;

    int mid = (l + r) / 2, it = l - 1, it1 = l, it2 = mid + 1;
    cdq2(l, mid);
    cdq2(mid + 1, r);

    while (it1 <= mid && it2 <= r) {
        if (info[it1].b > info[it2].b) {
            add(info[it1].c, 1);
            tmp[++it] = info[it1++];
        } else {
            ans[info[it2].a] += query(info[it2].c - k - 1);
            tmp[++it] = info[it2++];
        }
    }

    while (it1 <= mid) {
        add(info[it1].c, 1);
        tmp[++it] = info[it1++];
    }

    while (it2 <= r) {
        ans[info[it2].a] += query(info[it2].c - k - 1);
        tmp[++it] = info[it2++];
    }

    for (int i = l; i <= mid; ++i)
        add(info[i].c, -1);

    for (int i = l; i <= r; ++i)
        info[i] = tmp[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;

    for (int i = 1; i <= n; ++i)
        cin >> p[0][i];

    for (int i = 1; i <= n; ++i) {
        cin >> p[1][i];
        pos[p[1][i]] = i;
    }

    for (int i = 1; i <= n; ++i) {
        info[i].a = i;
        info[i].b = pos[p[0][i]];
        info[i].c = p[0][i];
    }

    cdq1(1, n);

    for (int i = 1; i <= n; ++i) {
        info[i].a = i;
        info[i].b = pos[p[0][i]];
        info[i].c = p[0][i];
    }

    cdq2(1, n);
    cout << accumulate(ans + 1, ans + 1 + n, 0ll) << endl;
    return 0;
}