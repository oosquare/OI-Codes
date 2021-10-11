#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 100000 + 10;

using ll = long long;

int n;
ll a[maxn], b[maxn], c[maxn], k, ans;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i] >> b[i];
    for (int i = 2; i <= n; ++i)
        c[i] = c[i - 1] + b[i] - a[i];
    sort(c + 1, c + 1 + n);
    k = -c[(n + 1) / 2];
    for (int i = 1; i <= n; ++i)
        ans += abs(c[i] + k);
    cout << ans << endl;
    return 0;
}