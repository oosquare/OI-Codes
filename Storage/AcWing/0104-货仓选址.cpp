#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 100000 + 10;

int n, a[maxn];
long long ans;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ++i)
        ans += abs(a[i] - a[(n + 1) / 2]);
    cout << ans << endl;
    return 0;
}