#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

constexpr int lim = 14;

using ll = long long;

int t, n, m;
int cnt[3], now[lim + 10];
vector<ll> seq;

void check() {
    if (cnt[1] != cnt[2])
        return;

    ll res = 0;

    for (int i = lim; i >= 1; --i)
        res = 3 * res + now[i];

    seq.push_back(res);
}

void dfs(int dep) {
    if (dep == lim + 1) {
        check();
        return;
    }

    for (int i = 0; i < 3; ++i) {
        ++cnt[i];
        now[dep] = i;
        dfs(dep + 1);
        --cnt[i];
    }
}

void solve() {
    cin >> n >> m;
    auto it = lower_bound(seq.begin(), seq.end(), n);

    for (int i = 1; i <= m; ++i) {
        cout << *it << " ";
        ++it;
    }

    cout << endl;
}

int main() {
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    ios::sync_with_stdio(false);
    dfs(1);
    sort(seq.begin(), seq.end());
    cin >> t;

    while (t--)
        solve();

    return 0;
}
