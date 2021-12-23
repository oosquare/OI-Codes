#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

constexpr int maxn = 300000 + 10;

int t, n;
char str[maxn];
int sa[maxn * 2], buf[2][maxn * 2], *rk = buf[0], *old = buf[1], height[maxn * 2];
int rk2[2][maxn];
int id[maxn * 2], cnt[maxn * 2], tmp[maxn * 2];
int logg[maxn], mi[2][maxn][16];
long long a[maxn], b[maxn];
long long ans;

bool equal(int x, int y, int w) {
    return old[x] == old[y] && old[x + w] == old[y + w];
}

void preprocessSuffixArray(int type) {
    memset(buf, 0, sizeof(buf));
    memset(sa, 0, sizeof(sa));
    memset(height, 0, sizeof(height));
    memset(id, 0, sizeof(id));
    memset(cnt, 0, sizeof(cnt));
    memset(tmp, 0, sizeof(tmp));

    int m = 127;

    for (int i = 0; i <= m; ++i)
        cnt[i] = 0;

    for (int i = 1; i <= n; ++i)
        ++cnt[rk[i] = str[i]];

    for (int i = 1; i <= m; ++i)
        cnt[i] += cnt[i - 1];

    for (int i = n; i >= 1; --i)
        sa[cnt[rk[i]]--] = i;

    for (int w = 1, p;; w *= 2, m = p) {
        p = 0;

        for (int i = n; i > n - w; --i)
            id[++p] = i;

        for (int i = 1; i <= n; ++i)
            if (sa[i] > w)
                id[++p] = sa[i] - w;

        for (int i = 1; i <= m; ++i)
            cnt[i] = 0;

        for (int i = 1; i <= n; ++i)
            ++cnt[tmp[i] = rk[id[i]]];

        for (int i = 1; i <= m; ++i)
            cnt[i] += cnt[i - 1];

        for (int i = n; i >= 1; --i)
            sa[cnt[tmp[i]]--] = id[i];

        swap(rk, old);
        p = 0;

        for (int i = 1; i <= n; ++i)
            rk[sa[i]] = (equal(sa[i - 1], sa[i], w) ? p : ++p);

        if (p == n) {
            for (int i = 1; i <= n; ++i)
                sa[rk[i]] = i;

            for (int i = 1; i <= n; ++i)
                rk2[type][i] = rk[i];

            break;
        }
    }

    for (int i = 1, j = 0; i <= n; ++i) {
        if (j)
            --j;

        while (str[i + j] == str[sa[rk[i] - 1] + j])
            ++j;

        height[rk[i]] = j;
    }
}

void preprocessSparseTable(int type) {
    for (int i = 1; i <= n; ++i)
        mi[type][i][0] = height[i];

    for (int j = 1; j <= 15; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            mi[type][i][j] = min(mi[type][i][j - 1], mi[type][i + (1 << (j - 1))][j - 1]);
}

int query(int type, int l, int r) {
    if (l > r)
        swap(l, r);

    ++l;

    int s = logg[r - l + 1];
    return min(mi[type][l][s], mi[type][r - (1 << s) + 1][s]);
}

void add(int a[], int l, int r, int v) {
    a[l] += v;
    a[r + 1] -= v;
}

int lcp(int x, int y) {
    return query(0, rk2[0][x], rk2[0][y]);
}

int lcs(int x, int  y) {
    return query(1, rk2[1][x], rk2[1][y]);
}

void solve() {
    memset(rk2, 0, sizeof(rk2));
    memset(mi, 0, sizeof(mi));
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));

    cin >> (str + 1);
    n = strlen(str + 1);

    preprocessSuffixArray(0);
    preprocessSparseTable(0);

    for (int i = 1, j = n; i < j; ++i, --j)
        swap(str[i], str[j]);

    preprocessSuffixArray(1);
    preprocessSparseTable(1);

    ans = 0;

    for (int le = 1; le <= n / 2; ++le) {
        for (int i = le; i <= n; i += le) {
            int l = i, r = i + le;
            int ll = n - (r - 1) + 1, rr = n - (l - 1) + 1;
            int p = min(lcp(l, r), le);
            int s = min(lcs(ll, rr), le - 1);

            if (p + s < le)
                continue;
            
            ++a[r + p - (p + s - le + 1)];
            --a[r + p];
            ++b[i - s];
            --b[i - s + (p + s - le + 1)];

        }
    }

    for (int i = 1; i <= n; ++i) {
        a[i] += a[i - 1];
        b[i] += b[i - 1];
    }

    for (int i = 1; i < n; ++i)
        ans += a[i] * b[i + 1];

    cout << ans << endl;
}

int main() {
    logg[0] = -1;

    for (int i = 1; i < maxn; ++i)
        logg[i] = logg[i / 2] + 1;

    logg[0] = 0;

    ios::sync_with_stdio(false);
    cin >> t;

    while (t--)
        solve();

    return 0;
}