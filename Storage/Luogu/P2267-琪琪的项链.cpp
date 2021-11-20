#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>
#include <vector>
using namespace std;

constexpr int maxn = 500000 + 10;

int n, m;
int a[maxn], f[maxn], sum[maxn], pre[maxn], pos[maxn];
vector<int> val;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        val.push_back(a[i]);
    }

    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());

    for (int i = 1; i <= n; ++i)
        a[i] = lower_bound(val.begin(), val.end(), a[i]) - val.begin() + 1;

    for (int i = 1; i <= n; ++i) {
        pre[i] = pos[a[i]];
        pos[a[i]] = i;
    }

    for (int i = 1; i <= n; ++i) {
        if (pre[i] == 0)
            f[i] = (sum[i - 1] + 1) % m;
        else
            f[i] = ((sum[i - 1] - sum[pre[i] - 1]) % m + m) % m;

        sum[i] = (sum[i - 1] + f[i]) % m;
    }

    cout << sum[n] << endl;
    return 0;
}