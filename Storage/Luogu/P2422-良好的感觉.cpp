#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 100000 + 10;

using ll = long long;

int n;
ll a[maxn], f[maxn], sum[maxn], ans;
int st[maxn], top;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1] + a[i];
        
        while (top > 0 && a[st[top]] > a[i]) {
            f[st[top]] += sum[i - 1] - sum[st[top]];
            --top;
        }

        f[i] += sum[i] - sum[st[top]];
        st[++top] = i;
    }

    for (int i = 1; i <= n; ++i)
        ans = max(ans, f[i] * a[i]);

    cout << ans << endl;
    return 0;
}