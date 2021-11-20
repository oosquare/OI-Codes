#include <iostream>
using namespace std;

constexpr int maxn = 5e3 + 10;

int n, l, p[maxn], ans1, ans2;

int main() {
    ios::sync_with_stdio(false);
    cin >> l >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
        ans1 = max(ans1, min(p[i] - 0, l + 1 - p[i]));
        ans2 = max(ans2, max(p[i] - 0, l + 1 - p[i]));
    }

    cout << ans1 << " " << ans2 << endl;
    return 0;
}