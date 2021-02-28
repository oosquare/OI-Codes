#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;

int a[16] = {0, 4, 8, -1, 16, -10, 4, -12, -48, 26, -44, 15, -16, -4, -4, -1};
int f[200000] = {0, 0, 0, 24, 4, 240, 204, 1316, 2988, 6720, 26200, 50248, 174280, 436904, 1140888, 3436404};
int n;

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    cin >> n;
    for (int i = 16; i <= n; ++i)
        for (int j = 0; j <= 15; ++j)
            f[i] = (f[i] + 1LL * a[j] * f[i - j - 1] % mod + mod) % mod;
    cout << f[n] << endl;
    return 0;
}