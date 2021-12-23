#include <iostream>
#include <cstring>

using namespace std;

constexpr int maxn = 1e5 + 10;

int t, n;
char str[maxn];
int sa[maxn * 2], rk[maxn * 2], height[maxn * 2];
int old[maxn * 2], sec[maxn * 2], buc[maxn * 2], tmp[maxn * 2];
int st[maxn], top;
long long ans;

bool equal(int x, int y, int w) {
    return old[x] == old[y] && old[x + w] == old[y + w];
}

void preprocess(char str[], int len) {
    int m = 127;

    for (int i = 0; i <= m; ++i)
        buc[i] = 0;

    for (int i = 1; i <= len; ++i)
        ++buc[rk[i] = str[i]];

    for (int i = 1; i <= m; ++i)
        buc[i] += buc[i - 1];

    for (int i = len; i >= 1; --i)
        sa[buc[rk[i]]--] = i;

    for (int w = 1, p;; w *= 2, m = p) {
        p = 0;

        for (int i = len; i > len - w; --i)
            sec[++p] = i;

        for (int i = 1; i <= len; ++i)
            if (sa[i] > w)
                sec[++p] = sa[i] - w;

        for (int i = 1; i <= m; ++i)
            buc[i] = 0;

        for (int i = 1; i <= len; ++i)
            ++buc[tmp[i] = rk[sec[i]]];

        for (int i = 1; i <= m; ++i)
            buc[i] += buc[i - 1];

        for (int i = len; i >= 1; --i)
            sa[buc[tmp[i]]--] = sec[i];

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
}

long long square(long long x) {
    return x * x;
}

void solve() {
    cin >> (str + 1);
    n = strlen(str + 1);
    preprocess(str, n);

    ans = 1ll * n * (n + 1) / 2;
    top = 0;

    for (int i = 2; i <= n + 1; ++i) {
        while (top && height[st[top]] > height[i]) {
            int h = height[st[top]] - max(height[i], top - 1 ? height[st[top - 1]] : 0);
            int c = i - (top - 1 ? st[top - 1] : 1);
            ans += 1ll * h * (square(c) - c);
            --top;
        }

        st[++top] = i;
    }


    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> t;

    while (t--)
        solve();

    return 0;
}