#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const ull mod = 13;
ull power[500100], hasha[500100], hashb[500100];
char s[500100];
int n, mid, l, r;
ll ans;

void preprocess() {
    power[0] = 1;
    for (int i = 1; i <= n; ++i) power[i] = power[i - 1] * mod;
    for (int i = 1; i <= n; ++i) hasha[i] = hasha[i - 1] * mod + s[i] - '0';
    for (int i = n; i; --i) hashb[i] = hashb[i + 1] * mod - (s[i] - '0') + 1;
}

bool vaild(int la, int ra, int lb, int rb) {
    ull h1 = hasha[ra] - hasha[la - 1] * power[ra - la + 1];
    ull h2 = hashb[lb] - hashb[rb + 1] * power[rb - lb + 1];
    return h1 == h2;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("project.in", "r", stdin);
	freopen("project.out", "w", stdout);
#else
	freopen("anti.in", "r", stdin);
	freopen("anti.out","w", stdout);
#endif
    scanf("%d", &n);
    scanf("%s", s + 1);
    preprocess();
    for (int i = 1; i < n; ++i) {
        if (s[i] == s[i + 1]) continue;
        l = 1;
        if (i < n - i)
            r = i;
        else
            r = n - i;
        while (r >= l) {
            mid = l + r >> 1;
            if (vaild(i - mid + 1, i, i + 1, i + mid)) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        ans += r;
    }
    printf("%lld\n", ans);
	return 0;
}
