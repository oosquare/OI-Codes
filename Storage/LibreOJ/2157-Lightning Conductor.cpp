#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

constexpr int maxn = 5e5 + 10;

int n, a[maxn];
double sq[maxn], f[maxn], g[maxn];

void dp(int l, int r, int pl, int pr, double f[]) {
    if (l > r)
        return;

    int mid = (l + r) / 2, pos = 0;

    for (int i = pl; i <= min(pr, mid - 1); ++i) {
        if (f[mid] < -a[mid] + a[i] + sq[mid - i]) {
            f[mid] = -a[mid] + a[i] + sq[mid - i];
            pos = i;
        }
    }

    dp(l, mid - 1, pl, pos, f);
    dp(mid + 1, r, pos, pr, f);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    for (int i = 0; i <= n; ++i)
        sq[i] = sqrt(i);

    dp(1, n, 1, n, f);
    reverse(a + 1, a + 1 + n);
    dp(1, n, 1, n, g);
    reverse(g + 1, g + 1 + n);

    for (int i = 1; i <= n; ++i)
        cout << (int)ceil(max(f[i], g[i])) << endl;

    return 0;
}