#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;

struct querys {
    int x, y, type;
    long long ans;
};

querys qs[maxn * 2], tmp[maxn * 2];
int n, m, a[maxn], b[maxn], c[maxn], p[3][3][maxn];
long long ans, tree[maxn];

inline int lowbit(int x) {
    return x & (-x);
}

void add(int p, int v) {
    for (; p <= n; p += lowbit(p))
        tree[p] += v;
}

void clear(int p) {
    for (; p <= n; p += lowbit(p))
        tree[p] = 0;
}

long long sum(int p) {
    long long res = 0;
    for (; p; p -= lowbit(p))
        res += tree[p];
    return res;
}

void CDQdivide(int l, int r) {
    if (l >= r)
        return;
    int mid = (l + r) / 2, id1 = l, id2 = mid + 1, id = l - 1;
    CDQdivide(l, mid), CDQdivide(mid + 1, r);
    for (int i = l; i <= r; ++i)
        tmp[i] = qs[i];
    for (int i = l; i <= r; ++i) {
        if (id2 > r || (id1 <= mid && tmp[id1].x <= tmp[id2].x)) {
            if (tmp[id1].type)
                add(tmp[id1].y, 1);
            qs[++id] = tmp[id1++];
        } else {
            if (!tmp[id2].type)
                tmp[id2].ans += sum(tmp[id2].y);
            qs[++id] = tmp[id2++];
        }
    }
    for (int i = l; i <= mid; ++i)
        if (tmp[i].type)
            clear(tmp[i].y);
}

void solve1() {
    ans += n;
}

void solve2() {
    for (int i = n; i >= 1; --i) {
        qs[++m] = {p[2][0][i], p[2][1][i], 0, 0};
        qs[++m] = {p[2][0][i], p[2][1][i], 1, 0};
    }
    CDQdivide(1, m);
    for (int i = 1; i <= m; ++i)
        if (!qs[i].type)
            ans += qs[i].ans;
    m = 0;

    for (int i = n; i >= 1; --i) {
        qs[++m] = {p[1][0][i], p[1][2][i], 0, 0};
        qs[++m] = {p[1][0][i], p[1][2][i], 1, 0};
    }
    CDQdivide(1, m);
    for (int i = 1; i <= m; ++i)
        if (!qs[i].type)
            ans += qs[i].ans;
    m = 0;

    for (int i = n; i >= 1; --i) {
        qs[++m] = {p[0][1][i], p[0][2][i], 0, 0};
        qs[++m] = {p[0][1][i], p[0][2][i], 1, 0};
    }
    CDQdivide(1, m);
    for (int i = 1; i <= m; ++i)
        if (!qs[i].type)
            ans += qs[i].ans;
    m = 0;
}

void solve3() {
    ans += (1LL * n * (n - 1) * (n - 2)) / (1 * 2 * 3);
    for (int i = 1; i <= n; ++i) {
        qs[++m] = {p[0][1][i], p[0][2][i], 0, 0};
        qs[++m] = {p[0][1][i], p[0][2][i], 1, 0};
    }
    CDQdivide(1, m);
    for (int i = 1; i <= m; ++i)
        if (!qs[i].type)
            ans += 1LL * qs[i].ans * (qs[i].ans - 1);
    m = 0;
    
    for (int i = 1; i <= n; ++i) {
        long long res = sum(p[0][1][i]);
        ans -= 1LL * res * (res - 1) / 2;
        add(p[0][1][i], 1);
    }
    memset(tree, 0, sizeof(tree));

    for (int i = 1; i <= n; ++i) {
        long long res = sum(p[0][2][i]);
        ans -= 1LL * res * (res - 1) / 2;
        add(p[0][2][i], 1);
    }
    memset(tree, 0, sizeof(tree));

    for (int i = 1; i <= n; ++i) {
        long long res = sum(p[1][2][i]);
        ans -= 1LL * res * (res - 1) / 2;
        add(p[1][2][i], 1);
    }
    memset(tree, 0, sizeof(tree));
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("subset.in", "r", stdin);
    freopen("subset.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= n; ++i)
        cin >> b[i];
    for (int i = 1; i <= n; ++i)
        cin >> c[i];
    for (int i = 1; i <= n; ++i) {
        p[0][1][a[i]] = b[i];
        p[1][0][b[i]] = a[i];
        p[0][2][a[i]] = c[i];
        p[2][0][c[i]] = a[i];
        p[1][2][b[i]] = c[i];
        p[2][1][c[i]] = b[i];
    }
    solve1();
    solve2();
    solve3();
    cout << ans << endl;
    return 0;
}
