#include <iostream>
#include <cstring>

using namespace std;

constexpr int maxn = 1e5 + 10;

int n, m;
char str[maxn], pattern[maxn];
int sa[maxn * 2], rk[maxn * 2];
int old[maxn * 2], id[maxn * 2], cnt[maxn * 2], tmp[maxn * 2];
int minv[maxn][18], maxv[maxn][18], logg[maxn];
int ans;

bool equal(int x, int y, int w) {
    return old[x] == old[y] && old[x + w] == old[y + w];
}

void preprocessSuffixArray(char str[], int len) {
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

void preprocessTable() {
    logg[0] = -1;

    for (int i = 1; i <= n; ++i)
        logg[i] = logg[i / 2] + 1;

    for (int i = 1; i <= n; ++i)
        minv[rk[i]][0] = maxv[rk[i]][0] = i;

    for (int j = 1; j <= 17; ++j) {
        for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
            minv[i][j] = min(minv[i][j - 1], minv[i + (1 << (j - 1))][j - 1]);
            maxv[i][j] = max(maxv[i][j - 1], maxv[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int queryMin(int l, int r) {
    int s = logg[r - l + 1];
    return min(minv[l][s], minv[r - (1 << s) + 1][s]);
}

int queryMax(int l, int r) {
    int s = logg[r - l + 1];
    return max(maxv[l][s], maxv[r - (1 << s) + 1][s]);
}

int compare(char str1[], int len1, char str2[], int len2) {
    bool pre = true;

    if (len1 <= len2) {
        for (int i = 1; i <= len1; ++i) {
            if (str1[i] != str2[i]) {
                pre = false;
                break;
            }
        }

        if (pre)
            return 0;
    }

    return strcmp(str1 + 1, str2 + 1);
}

int findLeft(char pattern[], int len) {
    int l = 1, r = n, pos = n + 1;

    while (l <= r) {
        int mid = (l + r) / 2;
        int res = compare(pattern, len, str + sa[mid] - 1, n - sa[mid] + 1);

        if (res == 0) {
            pos = mid;
            r = mid - 1;
        } else if (res == -1) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    return (pos != n + 1 ? pos : -1);
}

int findRight(char pattern[], int len) {
    int l = 1, r = n, pos = n + 1;

    while (l <= r) {
        int mid = (l + r) / 2;
        int res = compare(pattern, len, str + sa[mid] - 1, n - sa[mid] + 1);

        if (res == 0) {
            pos = mid;
            l = mid + 1;
        } else if (res == -1) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    return (pos != n + 1 ? pos : -1);
}

bool solve(char pattern[], int len) {
    for (int i = 1; i < len; ++i) {
        int l1 = findLeft(pattern, i);
        int l2 = findLeft(pattern + i, len - i);

        if (l1 == -1 || l2 == -1)
            continue;

        int r1 = findRight(pattern, i);
        int r2 = findRight(pattern + i, len - i);

        int a = queryMin(l1, r1), c = queryMax(l2, r2);

        if (a + i - 1 < c)
            return true;
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> (str + 1);
    n = strlen(str + 1);

    preprocessSuffixArray(str, n);
    preprocessTable();

    cin >> m;

    while (m--) {
        cin >> (pattern + 1);
        ans += solve(pattern, strlen(pattern + 1));
    }

    cout << ans << endl;
    return 0;
}