#include <iostream>
#include <cstring>

using namespace std;

constexpr int maxn = 200000 + 10;

int n;
char str[maxn], invalid[maxn];
int sa[maxn * 2], rk[maxn * 2], height[maxn * 2];
int old[maxn * 2], id[maxn * 2], cnt[maxn * 2], tmp[maxn * 2];
int st[maxn], top, l[maxn], r[maxn];
long long sum[maxn], ans;

bool equal(int x, int y, int w) {
    return old[x] == old[y] && old[x + w] == old[y + w];
}

void reverse(char str[], int len) {
    for (int i = 1, j = len; i < j; ++i, --j)
        swap(str[i], str[j]);
}

void preprocess(char str[], int len) {
    int m = 127;

    for (int i = 1; i <= len; ++i)
        ++cnt[rk[i] = str[i]];

    for (int i = 1; i <= m; ++i)
        cnt[i] += cnt[i - 1];

    for (int i = len; i >= 1; --i)
        sa[cnt[rk[i]]--] = i;

    for (int w = 1, p;; w *= 2, m = p) {
        p = 0;

        for (int i = len; i > len - w; --i)
            id[++p] = i;

        for (int i = 1; i <= len; ++i)
            if (sa[i] > w)
                id[++p] = sa[i] - w;

        for (int i = 1; i <= m; ++i)
            cnt[i] = 0;

        for (int i = 1; i <= len; ++i)
            ++cnt[tmp[i] = rk[id[i]]];

        for (int i = 1; i <= m; ++i)
            cnt[i] += cnt[i - 1];

        for (int i = len; i >= 1; --i)
            sa[cnt[tmp[i]]--] = id[i];

        swap(rk, old);
        p = 0;

        for (int i = 1; i <= len; ++i)
            rk[sa[i]] = (equal(sa[i - 1], sa[i], w) ? p : ++p);

        if (p == len) {
            for (int i = 1; i <= len; ++i)
                sa[rk[i]] = i;

            break;
        }
    }

    for (int i = 1, j = 0; i <= len; ++i) {
        if (j)
            --j;

        while (str[i + j] == str[sa[rk[i] - 1] + j])
            ++j;

        height[rk[i]] = j;
    }

    height[1] = 0;
}

int main() {
    ios::sync_with_stdio(false);
    
    cin >> n;
    cin >> (str + 1);
    cin >> (invalid + 1);
    reverse(str, n);
    reverse(invalid, n);

    preprocess(str, n);

    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + (invalid[sa[i]] == '0');

    for (int i = 1; i <= n; ++i) {
        while (top && height[st[top]] > height[i]) {
            r[st[top]] = i - 1;
            --top;
        }

        l[i] = st[top] + 1;
        st[++top] = i;
    }

    while (top) {
        r[st[top]] = n;
        --top;
    }

    for (int i = 2; i <= n; ++i)
        ans = max(ans, 1ll * height[i] * (sum[r[i]] - sum[l[i] - 2]));

    for (int i = 1; i <= n; ++i)
        if (invalid[i] == '0')
            ans = max(ans, 1ll * n - i + 1);

    cout << ans << endl;
    return 0;
}