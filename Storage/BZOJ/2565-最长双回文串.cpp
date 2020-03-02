#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

char s0[maxn], s[2 * maxn];
int n0, n = 2, ll[2 * maxn], rr[2 * maxn], r[2 * maxn];

int main() {
    scanf("%s", s0 + 1);
    s[0] = '$';
    s[1] = '#';
    n0 = strlen(s0 + 1);
    for (int i = 1; i <= n0; ++i) {
        s[n++] = s0[i];
        s[n++] = '#';
    }
    s[n] = '^';
    int p = 0, maxx = 0;
    r[0] = 1;
    for (int i = 1; i <= n; ++i) {
        if (maxx > i)
            r[i] = min(maxx - i, r[2 * p - i]);
        while (s[i - r[i]] == s[i + r[i]])
            ++r[i];
        if (i + r[i] > maxx) {
            maxx = i + r[i];
            p = i;
        }
        ll[i + r[i] - 1] = max(ll[i + r[i] - 1], r[i] - 1);
        rr[i - r[i] + 1] = max(rr[i - r[i] + 1], r[i] - 1);
    }
    int ans = 0;
    for (int i = 3; i <= n; i += 2)
        ll[i] = max(ll[i], ll[i + 2] - 2);
    for (int i = 3; i <= n; i += 2)
        rr[i] = max(rr[i], rr[i - 2] - 2);
    for (int i = 3; i <= n; i += 2)
        if (ll[i] && rr[i])
            ans = max(ans, ll[i] + rr[i]);
    printf("%d\n", ans);
    return 0;
}
