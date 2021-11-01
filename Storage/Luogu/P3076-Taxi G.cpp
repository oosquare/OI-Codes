#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;

int n, m, a[maxn], b[maxn];
long long ans;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i] >> b[i];
        ans += abs(a[i] - b[i]);
    }

    ++n;
    a[n] = m;
    b[n] = 0;
    sort(a + 1, a + 1 + n);
    sort(b + 1, b + 1 + n);

    for (int i = 1; i <= n; ++i)
        ans += abs(a[i] - b[i]);

    cout << ans << endl;
    return 0;
}