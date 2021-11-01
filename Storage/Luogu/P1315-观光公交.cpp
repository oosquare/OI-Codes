#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e3 + 10;
constexpr int maxm = 1e4 + 10;

struct Range {
    int l, r, cnt;

    bool operator<(const Range &rhs) const {
        return cnt < rhs.cnt;
    }
};

int n, m, k;
long long ans;
int d[maxn], t[maxm], a[maxm], b[maxm];
int last[maxn], arrive[maxn], suf[maxn], sum[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;

    for (int i = 1; i < n; ++i)
        cin >> d[i];

    for (int i = 1; i <= m; ++i) {
        cin >> t[i] >> a[i] >> b[i];
        last[a[i]] = max(last[a[i]], t[i]);
        ++sum[b[i]];
    }

    for (int i = 1; i <= n; ++i)
        sum[i] += sum[i - 1];

    arrive[1] = last[1];

    for (int i = 2; i <= n; ++i)
        arrive[i] = max(arrive[i - 1], last[i - 1]) + d[i - 1];

    for (int i = 1; i <= m; ++i)
        ans += arrive[b[i]] - t[i];

    for (int t = 1; t <= k; ++t) {
        suf[n] = suf[n - 1] = n;

        for (int i = n - 2; i >= 1; --i) {
            if (arrive[i + 1] <= last[i + 1])
                suf[i] = i + 1;
            else            
                suf[i] = suf[i + 1];
        }

        int mx = -1, id = 0;

        for (int i = 1; i < n; ++i) {
            if (d[i] == 0)
                continue;

            if (sum[suf[i]] - sum[i] > mx) {
                mx = sum[suf[i]] - sum[i];
                id = i;
            }
        }

        --d[id];
        ans -= mx;

        for (int i = 2; i <= n; ++i)
            arrive[i] = max(arrive[i - 1], last[i - 1]) + d[i - 1];
    }

    cout << ans << endl;
    return 0;
}