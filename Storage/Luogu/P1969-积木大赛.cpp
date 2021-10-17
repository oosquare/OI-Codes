#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;

int n, ans, h[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> h[i];
        ans += max(h[i] - h[i - 1], 0);
    }
    cout << ans << endl;
    return 0;
}