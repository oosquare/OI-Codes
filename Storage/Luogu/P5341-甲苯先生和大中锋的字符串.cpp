#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int oo = 0x3f3f3f3f;

int t, n, k;
char str[maxn];
int sa[maxn * 2], rk[maxn * 2], height[maxn * 2];
int cnt[maxn * 2], id[maxn * 2], old[maxn * 2], tmp[maxn * 2];
int q[maxn], fr, bk, mcnt[maxn];

bool equal(int x, int y, int w) {
    return old[x] == old[y] && old[x + w] == old[y + w];
}

void preprocess(char str[], int n) {
    int m = 127;

    for (int i = 1; i <= m; ++i)
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

    height[0] = height[n + 1] = 0;
}

void solve() {
    scanf("%s%d", str + 1, &k);
    n = strlen(str + 1);
    preprocess(str, n);

    q[fr = bk = 1] = 2;

    for (int i = 3; i < k; ++i) {
        while (fr <= bk && height[q[bk]] >= height[i])
            --bk;

        q[++bk] = i;
    }

    for (int i = k; i <= n; ++i) {
        while (fr <= bk && i - q[fr] + 1 > k - 1)
            ++fr;

        while (fr <= bk && height[q[bk]] >= height[i])
            --bk;

        q[++bk] = i;

        int mx = max(height[i - k + 1], height[i + 1]) + 1;
        int mi = (k != 1 ? height[q[fr]] : n - sa[i] + 1);

        if (mx <= mi) {
            ++mcnt[mx];
            --mcnt[mi + 1];
        }
    }

    for (int i = 1; i <= n; ++i)
        mcnt[i] += mcnt[i - 1];

    int mx = 1, ans = -1;

    for (int i = 1; i <= n; ++i) {
        int res = mcnt[i];

        if (mx <= res) {
            mx = res;
            ans = i;
        }
    }

    printf("%d\n", ans);

    for (int i = 1; i <= n; ++i)
        mcnt[i] = 0;
}

int main() {
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}