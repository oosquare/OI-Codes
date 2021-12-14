#include <iostream>
using namespace std;

constexpr int maxn = 5e5 + 10;

int n, len;
char str[maxn], dat[maxn * 2], ans[maxn];
int sa[maxn * 4], rk[maxn * 4], old[maxn * 4], tmp[maxn * 4], id[maxn * 4], cnt[maxn * 4];

bool equal(int x, int y, int w) {
    return old[x] == old[y] && old[x + w] == old[y + w];
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
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> str[i];
        dat[++len] = str[i];
    }

    dat[++len] = '#';

    for (int i = n; i >= 1; --i)
        dat[++len] = str[i];

    preprocess(dat, len);

    int it1 = 1, it2 = n + 2;

    for (int i = 1; i <= n; ++i) {
        if (rk[it1] < rk[it2])
            ans[i] = dat[it1++];
        else
            ans[i] = dat[it2++];
    }

    for (int i = 1; i <= n; ++i) {
        cout << ans[i];

        if (i % 80 == 0)
            cout.put('\n');
    }
    return 0;
}