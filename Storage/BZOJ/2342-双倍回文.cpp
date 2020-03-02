#include <bits/stdc++.h>
using namespace std;

const int maxn = 500005;
int n = 2, n0, r[2 * maxn], ans;
char s[2 * maxn], s0[maxn];

void manacher() {
    int p = 0, maxx = 0;
    r[0] = 1;
    for (int i = 1; i <= n; ++i) {
        if (maxx > i)
            r[i] = min(maxx - i, r[2 * p - i]);
        else
            r[i] = 1;
        while (s[i - r[i]] == s[i + r[i]])
            ++r[i];
        if (i + r[i] > maxx) {
            for (int j = max(i + 4, maxx); i % 2 == 1 && j < i + r[i]; ++j) {
                if ((j - i) % 4 == 0 && 2 * r[i - (j - i) / 2] > (j - i))
                    ans = max(ans, j - i);
            }
            maxx = i + r[i];
            p = i;
        }
    }
}

int main() {
    scanf("%d%s", &n0, s0 + 1);
    s[0] = '$';
    s[1] = '#';
    for (int i = 1; i <= n0; ++i) {
        s[n++] = s0[i];
        s[n++] = '#';
    }
    s[n] = '^';
    manacher();
    printf("%d\n", ans);
    return 0;
}