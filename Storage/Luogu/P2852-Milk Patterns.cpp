#include <iostream>
#include <cstring>
using namespace std;

constexpr int maxn = 20000 + 10;

int n, k, dat[maxn];
int sa[maxn * 2], rk[maxn * 2], old[maxn * 2], id[maxn * 2], tmp[maxn * 2], cnt[1000000 + 10], height[maxn * 2];
int q[maxn], fr, bk, ans;

bool equal(int x, int y, int w) {
    return old[x] == old[y] && old[x + w] == old[y + w];
}

void preprocess(int dat[], int n) {
    int m = 1000000;

    for (int i = 1; i <= n; ++i)
        ++cnt[rk[i] = dat[i]];

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

        while (dat[i + j] == dat[sa[rk[i] - 1] + j])
            ++j;

        height[rk[i]] = j;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;

    for (int i = 1; i <= n; ++i)
        cin >> dat[i];

    preprocess(dat, n);

    fr = 1;

    for (int i = 2; i <= n; ++i) {
        while (fr <= bk && i - q[fr] + 2 > k)
            ++fr;

        while (fr <= bk && height[q[bk]] >= height[i])
            --bk;

        q[++bk] = i;
        ans = max(ans, height[q[fr]]);
    }

    cout << ans << endl;
    return 0;
}