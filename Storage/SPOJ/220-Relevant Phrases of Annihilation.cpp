#include <iostream>
#include <cstring>

using namespace std;

constexpr int maxl = 150000 + 50;
constexpr int oo = 0x3f3f3f3f;

int t, n, len;
char str0[maxl];
int col[maxl], str[maxl];
int sa[maxl * 2], buf[2][maxl * 2], *rk = buf[0], *old = buf[1], height[maxl * 2];
int cnt[maxl * 2], id[maxl * 2], tmp[maxl * 2];

bool equal(int x, int y, int w) {
    return old[x] == old[y] && old[x + w] == old[y + w];
}

void preprocess(int str[], int len) {
    int m = 127 + 2 * n;

    for (int i = 1; i <= m; ++i)
        cnt[i] = 0;

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
}

bool check(int l) {
    int ht = oo, mx[11], mi[11];
    bool valid[11];

    for (int i = 1; i <= n; ++i) {
        mx[i] = -oo;
        mi[i] = oo;
        valid[i] = false;
    }

    mx[col[sa[1]]] = mi[col[sa[1]]] = sa[1];

    for (int i = 2; i <= len; ++i) {
        if (min(ht, height[i]) >= l) {
            ht = min(ht, height[i]);
            int id = col[sa[i]];
            mx[id] = max(mx[id], sa[i]);
            mi[id] = min(mi[id], sa[i]);

            if (mx[id] - mi[id] >= l)
                valid[id] = true;

            bool found = true;

            for (int i = 1; i <= n; ++i) {
                if (!valid[i]) {
                    found = false;
                    break;
                }
            }

            if (found)
                return true;
        } else {
            ht = oo;

            for (int i = 1; i <= n; ++i) {
                mx[i] = -oo;
                mi[i] = oo;
                valid[i] = false;
            }

            mx[col[sa[i]]] = mi[col[sa[i]]] = sa[i];
        }
    }

    return false;
}

void solve() {
    cin >> n;
    len = 0;
    int l = 0, r = oo, ans = 0;

    for (int i = 1; i <= n; ++i) {
        cin >> (str0 + 1);
        int len0 = strlen(str0 + 1);

        for (int j = 1; j <= len0; ++j) {
            str[++len] = str0[j];
            col[len] = i;
        }

        str[++len] = 127 + i;
        col[len] = 0;
        r = min(r, len0 / 2);
    }

    preprocess(str, len);

    while (l <= r) {
        int mid = (l + r) >> 1;

        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
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