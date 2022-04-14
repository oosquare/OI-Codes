#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

constexpr int maxn = 1e5 + 10;

int n, k, ans, a[maxn];

int main() {
    freopen("ad.in", "r", stdin);
    freopen("ad.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> k;

    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    sort(a + 1, a + 1 + n);
    ans = a[n] - a[1];

    for (int i = 1; i < n; ++i)
        ans = min(ans, max(a[i] + k, a[n] - k) - min(a[1] + k, a[i + 1] - k));

    cout << ans << endl;
    return 0;
}
