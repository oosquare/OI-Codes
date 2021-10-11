#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int maxn = 1000000 + 10;

int n;
ll t, c, ans, v[maxn], l[maxn], sum, mx;
ll arr[maxn], tree[maxn];

int lowbit(int x) {
    return x & (-x);
}

void add(int p, int a) {
    for (; p <= mx; p += lowbit(p))
        tree[p] += a;
}

ll query(int p) {
    ll res = 0;
    for (; p; p -= lowbit(p))
        res += tree[p];
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> t >> c;
    for (int i = 1; i <= n; ++i)
        cin >> v[i];
    sort(v + 1, v + n + 1);
    for (int i = 1; i <= n; ++i) {
        l[i] = (v[i] * t) / v[n];
        arr[i] = (v[i] * t) % v[n] + 1;
        mx = max(mx, arr[i]);
    }
    for (int i = 1; i <= n; ++i) {
        sum += l[i];
        ans += i * l[i] - sum;
    }
    for (int i = 1; i <= n; ++i) {
        ans -= query(mx) - query(arr[i]);
        add(arr[i], 1);
    }
    cout << ans << endl;
    return 0;
}