#include <iostream>
#include <cstring>

using namespace std;

constexpr int maxl = 20000 + 10;
constexpr int oo = 0x3f3f3f3f;

int n, len0[5], len;
char str0[5][maxl], str[maxl * 5];
int sa[maxl * 10], rk[maxl * 10], height[maxl * 10];
int cnt[maxl * 10], id[maxl * 10], old[maxl * 10], tmp[maxl * 10];
int pos[maxl * 5];
int l, r = oo, ans;

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

        for (int i = 1; i <= len; ++i)
            old[i] = rk[i];

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

bool check(int mid) {
    int mi = oo, buc[6] = {0};
    ++buc[pos[sa[1]]];

    for (int i = 2; i <= len; ++i) {
        if (min(mi, height[i]) >= mid) {
            mi = min(mi, height[i]);
            ++buc[pos[sa[i]]];

            bool valid = true;

            for (int j = 0; j < n; ++j) {
                if (buc[j] == 0) {
                    valid = false;
                    break;
                }
            }

            if (valid)
                return true;
        } else {
            for (int j = 0; j < n; ++j)
                buc[j] = 0;

            mi = oo;
            ++buc[pos[sa[i]]];
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> (str0[i] + 1);
        len0[i] = strlen(str0[i] + 1);
        r = min(r, len0[i]);

        for (int j = 1; j <= len0[i]; ++j) {
            str[++len] = (int)str0[i][j];
            pos[len] = i;
        }

        str[++len] = i + '0';
        pos[len] = 5;
    }

    preprocess(str, len);

    while (l <= r) {
        int mid = (l + r) / 2;

        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    cout << ans << endl;
    return 0;
}