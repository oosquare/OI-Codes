#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int maxn = 100000 + 10;

int n, m, t;
int x[maxn], y[maxn];
int r[maxn], c[maxn];
int tmp[maxn];

optional<ll> solve(int n, int a[], int c[]) {
    ll avg = 0;
    for (int i = 1; i <= n; ++i)
        avg += a[i];
    if (avg % n)
        return nullopt;
    avg /= n;
    for (int i = 2; i <= n; ++i)
        c[i] = c[i - 1] + avg - a[i - 1];
    sort(c + 1, c + 1 + n);
    ll k = -c[(n + 1) / 2], ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += abs(c[i] + k);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> t;
    for (int i = 1; i <= t; ++i) {
        cin >> x[i] >> y[i];
        ++r[x[i]];
        ++c[y[i]];
    }
    auto rres = solve(n, r, tmp), cres = solve(m, c, tmp);
    if (rres.has_value()) {
        if (cres.has_value())
            cout << "both " << rres.value() + cres.value() << endl;
        else
            cout << "row " << rres.value() << endl;
    } else {
        if (cres.has_value())
            cout << "column " << cres.value() << endl;
        else
            cout << "impossible" << endl;
    }
    return 0;
}