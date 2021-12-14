#include <iostream>
#include <cstring>

using namespace std;

constexpr int maxn = 200000 + 10;

char s1[maxn], s2[maxn], s[maxn * 2];
int n1, n2;
int sa[maxn * 4], rk[maxn * 4], old[maxn * 4], id[maxn * 4], height[maxn * 2];
int cnt[maxn * 4], tmp[maxn * 4];
int st[maxn], top;

bool equal(int x, int y, int w) {
    return old[x] == old[y] && old[x + w] == old[y + w];
}

void preprocess(char str[], int len) {
    int m = 127;

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
            rk[sa[i]] = (equal(sa[i - 1], sa[i], w) ? p: ++p);

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

long long calc(int len) {
    top = 0;
    long long sum = 0, res = 0;

    for (int i = 1; i <= len; ++i) {
        while (top && height[st[top]] >= height[i]) {
            sum -= 1ll * height[st[top]] * (st[top] - st[top - 1]);
            --top;
        }

        st[++top] = i;
        sum += 1ll * height[i] * (i - st[top - 1]);
        res += sum;
    }

    return res;
}

inline long long solve(char str[], int len) {
    preprocess(str, len);
    return calc(len);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> (s1 + 1) >> (s2 + 1);
    n1 = strlen(s1 + 1);
    n2 = strlen(s2 + 1);

    for (int i = 1; i <= n1; ++i)
        s[i] = s1[i];

    s[n1 + 1] = '#';

    for (int i = 1; i <= n2; ++i)
        s[n1 + 1 + i] = s2[i];

    cout << solve(s, n1 + n2 + 1) - solve(s1, n1) - solve(s2, n2) << endl;
    return 0;
}