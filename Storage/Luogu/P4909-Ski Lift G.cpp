#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5000 + 10;

int n, k, h[maxn];
int f[maxn], q[maxn], l = 1, r = 0;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
        cin >> h[i];
    f[1] = 1;
    for (int i = 2; i <= n; ++i) {
        f[i] = f[i - 1] + 1;
        int mx = i - 1;
        for (int j = i - 2; j >= 1 && i - j <= k; --j) {
            if (1ll * (h[i] - h[mx]) * (i - j) >= 1ll * (h[i] - h[j]) * (i - mx)) {
                mx = j;
                f[i] = min(f[i], f[j] + 1);
            }
        }
    }
    cout << f[n] << endl;
    return 0;
}