#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 31 + 10;

long long n, l, k, f[maxn][maxn], c[maxn][maxn], ans[maxn];

void preprocess() {
    for (int i = 0; i <= 32; ++i)
        c[i][0] = c[i][i] = 1;
    for (int i = 1; i <= 32; ++i)
        for (int j = 1; j < i; ++j)
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];

    for (int i = 0; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            for (int t = 0; t <= i; ++t)
                f[i][j] += c[j - 1][t];
}

void solve() {
    --k;
    int last = n + 1;
    while (k > 0 && l > 0) {
        int i;
        for (i = last - 1; i >= 0; --i) {
            if (f[l][i] <= k)
                break;
        }
        ans[i] = 1;
        k -= f[l][i];
        last = i;
        --l;
    }
    for (int i = n; i >= 1; --i)
        cout << ans[i];
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> l >> k;
    preprocess();
    solve();
    return 0;
}