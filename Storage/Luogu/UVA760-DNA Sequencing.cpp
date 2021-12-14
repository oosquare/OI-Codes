#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int maxn = 300 + 10;
const int oo = 0x3f3f3f3f;

char s1[maxn], s2[maxn], s[maxn * 2];
int len1, len2, len;
int sa[maxn * 4], rk[maxn * 4], height[maxn * 4];
int old[maxn * 4], id[maxn * 4], cnt[maxn * 4], tmp[maxn * 4];

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
            rk[sa[i]] = (equal(sa[i], sa[i - 1], w) ? p : ++p);

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
    int mi = oo, minp = sa[1], maxp = sa[1];

    for (int i = 2; i <= len; ++i) {
        if (min(mi, height[i]) >= mid) {
            mi = min(mi, height[i]);
            minp = min(minp, sa[i]);
            maxp = max(maxp, sa[i]);

            if (minp <= len1 && maxp >= len1 + 2)
                return true;
        } else {
            mi = oo;
            minp = sa[i];
            maxp = sa[i];
        }
    }

    return false;
}

int divide() {
    int l = 0, r = min(len1, len2), ans = 0;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    return ans;
}

vector<int> find(int l) {
    int mi = oo, minp = sa[1], maxp = sa[1];
    vector<int> res;
    bool found = false;

    for (int i = 2; i <= len; ++i) {
        if (min(mi, height[i]) >= l) {
            mi = min(mi, height[i]);
            minp = min(minp, sa[i]);
            maxp = max(maxp, sa[i]);

            if (minp <= len1 && maxp >= len1 + 2 && !found) {
                res.push_back(minp);
                found = true;
            }
        } else {
            found = false;
            mi = oo;
            minp = sa[i];
            maxp = sa[i];
        }
    }

    return res;
}

void print(int start, int len) {
    for (int i = 0; i < len; ++i)
        cout << s[start + i];

    cout << endl;
}

void clear() {
    len1 = len2 = 0;

    memset(s1, 0, sizeof(s1));
    memset(s2, 0, sizeof(s2));
    memset(s, 0, sizeof(s));

    memset(sa, 0, sizeof(sa));
    memset(rk, 0, sizeof(rk));
    memset(height, 0, sizeof(height));
    memset(cnt, 0, sizeof(cnt));
    memset(old, 0, sizeof(old));
    memset(id, 0, sizeof(id));
    memset(tmp, 0, sizeof(tmp));
}

int main() {
    bool first = true;

    while (cin >> (s1 + 1) >> (s2 + 1)) {
        if (!first)
            cout << endl;
        else
            first = false;

        len1 = strlen(s1 + 1);
        len2 = strlen(s2 + 1);
        len = 0;

        for (int i = 1; i <= len1; ++i)
            s[++len] = s1[i];

        s[++len] = '#';

        for (int i = 1; i <= len2; ++i)
            s[++len] = s2[i];

        preprocess(s, len);

        int maxl = divide();

        if (maxl) {
            vector<int> ans = find(maxl);

            for (int p : ans)
                print(p, maxl);
        } else {
            cout << "No common sequence." << endl;
        }

        clear();
    }
    return 0;
}