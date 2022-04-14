#include <iostream>
#include <cmath>
#include <algorithm>

constexpr int MAX_N = 100000 + 10;

struct Query {
    int l, r, vl, vr, id;
};

int n, m, q;
int a[MAX_N], b[MAX_N];
int nsize, msize, ntot, mtot, nblock[MAX_N], mblock[MAX_N], nr[MAX_N], mr[MAX_N];
long long ans[MAX_N], mx[MAX_N], sum[MAX_N], backup[MAX_N], buc[MAX_N];
Query qs[MAX_N];

void add(int x, bool type) {
    if (type)
        backup[x] = mx[mblock[a[x]]];

    sum[a[x]] += b[x];
    mx[mblock[a[x]]] = std::max(mx[mblock[a[x]]], sum[a[x]]);
}

void rollback(int x) {
    sum[a[x]] -= b[x];
    mx[mblock[a[x]]] = backup[x];
}

long long query(int ql, int qr) {
    int ld = mblock[ql], rd = mblock[qr];
    long long res = 0;

    if (ld == rd) {
        for (int i = ql; i <= qr; i++)
            res = std::max(res, sum[i]);

        return res;
    }

    for (int i = ld + 1; i < rd; i++)
        res = std::max(mx[i], res);

    for (int i = ql; i <= mr[ld]; i++)
        res = std::max(res, sum[i]);

    for (int i = mr[rd - 1] + 1; i <= qr; i++)
        res = std::max(res, sum[i]);

    return res;
}

void preprocess() {
    nsize = (int) std::sqrt(n);
    msize = (int) std::sqrt(m);

    for (int i = 1; i <= n; i++) {
        nblock[i] = (i - 1) / nsize + 1;
        nr[nblock[i]] = i;
    }

    for (int i = 1; i <= m; i++) {
        mblock[i] = (i - 1) / msize + 1;
        mr[mblock[i]] = i;
    }

    ntot = nblock[n];
    mtot = mblock[m];

    std::sort(qs + 1, qs + 1 + q, [](const Query &lhs, const Query &rhs) {
        return (nblock[lhs.l] != nblock[rhs.l] ? lhs.l < rhs.l : lhs.r < rhs.r);
    });
}

void handleSingle(int t) {
    long long res = 0;

    for (int i = qs[t].l; i <= qs[t].r; ++i) {
        buc[a[i]] += b[i];

        if (qs[t].vl <= a[i] && qs[t].vr >= a[i])
            res = std::max(res, buc[a[i]]);
    }

    for (int j = qs[t].l; j <= qs[t].r; ++j)
        buc[a[j]] -= b[j];

    ans[qs[t].id] = res;
}

void handleMultiple(int t, int ld, int &rd) {
    while (rd < qs[t].r) {
        ++rd;
        add(rd, false);
    }

    for (int j = ld; j >= qs[t].l; --j)
        add(j, true);

    ans[qs[t].id] = query(qs[t].vl, qs[t].vr);

    for (int j = qs[t].l; j <= ld; ++j)
        rollback(j);
}

void solve() {
    for (int l = 1, r = 1; l <= q; l = r + 1, r = l) {
        for (int i = 1; i <= mtot; i++)
            mx[i] = 0;

        while (r + 1 <= q && nblock[qs[r + 1].l] == nblock[qs[l].l])
            ++r;

        int ld = nr[nblock[qs[l].l]], rd = nr[nblock[qs[l].l]];

        for (int i = l; i <= r; ++i) {
            if (nblock[qs[i].l] == nblock[qs[i].r])
                handleSingle(i);
            else
                handleMultiple(i, ld, rd);
        }

        for (int i = nr[nblock[qs[l].l]] + 1; i <= rd; ++i)
            sum[a[i]] -= b[i];
    }
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("GOAT.in", "r", stdin);
    std::freopen("GOAT.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m >> q;

    for (int i = 1; i <= n; i++)
        std::cin >> a[i];

    for (int i = 1; i <= n; i++)
        std::cin >> b[i];

    for (int i = 1; i <= q; i++) {
        auto &[l, r, vl, vr, id] = qs[i];
        id = i;
        std::cin >> l >> r >> vl >> vr;
    }

    preprocess();
    solve();

    for (int i = 1; i <= q; i++)
        std::cout << ans[i] << std::endl;

    return 0;
}
