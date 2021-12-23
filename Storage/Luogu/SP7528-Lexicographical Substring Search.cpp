#include <iostream>
#include <cstring>
using namespace std;

constexpr int maxn = 90000 + 10;

int t, n, k;
char str[maxn];
int sa[maxn * 2], rk[maxn * 2], height[maxn * 2];
int cnt[maxn * 2], id[maxn * 2], old[maxn * 2], tmp[maxn * 2];
int sum[maxn];

bool equal(int x, int y, int w) {
    return old[x] == old[y] && old[x + w] == old[y + w];
}

void preprocess() {
    int m = 127;

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

    height[0] = 0;
}

void solve() {
    cin >> k;

    int l = 1, r = n;

    while (l < r) {
        int mid = (l + r) / 2;

        if (sum[mid] >= k)
            r = mid;
        else
            l = mid + 1;
    }

    int ed = k - sum[l - 1] + height[l];

    for (int i = 1; i <= ed; ++i)
        putchar(str[sa[l] + i - 1]);
    
    putchar('\n');
}

int main() {
    ios::sync_with_stdio(false);
    cin >> (str + 1);
    n = strlen(str + 1);
    preprocess();

    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + n - sa[i] + 1 - height[i];
    sum[n + 1] = sum[n];
    cin >> t;

    while (t--)
        solve();

    return 0;
}