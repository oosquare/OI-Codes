#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 100000 + 10;

long double lg[256];
int q, a;
string s;

int main() {
    // ios::sync_with_stdio(false);
    for (int i = (int)'0' + 1; i < 256; ++i)
        lg[i - (int)'0'] = log10(i - (int)'0');

    cin >> q;
    while (q--) {
        cin >> a >> s;

        long double log10a = log10(a), ans = 0.5 * a * (a + 1) * log10a;
        for (int i = 0; i <= a; ++i)
            ans += lg[(int)(s[i] - '0')];
        printf("%.0Lf\n", floor(ans) + 1);
    }
    return 0;
}