#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e5 + 10;
constexpr int mod = 1e9 + 7;

int n, q, ans;
int fa[maxn], f[maxn], sze[maxn];
int fac[maxn], inv[maxn];

int power(int x, int y) {
    int res = 1;
    for (; y != 0; y /= 2) {
        if (y % 2)
            res = 1LL * res * x % mod;
        x = 1LL * x * x % mod;
    }
    return res;
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int c(int n, int m) {
    if (n < m)
        return 0;
    return 1LL * fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        sze[i] = 1;
        f[i] = 1;
        fa[i] = i;
    }

    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    inv[n] = power(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; --i)
        inv[i] = 1LL * inv[i + 1] * (i + 1) % mod;

    while (q--) {
        int op, x, y;
        cin >> op >> x;
        if (op == 1) {
            cin >> y;
            x = (x + ans) % n + 1;
            y = (y + ans) % n + 1;
            x = find(x);
            y = find(y);
            fa[x] = y;
            sze[y] += sze[x];
            f[y] = 1LL * f[y] * c(sze[y] - 1, sze[x]) % mod * f[x] % mod;
        } else {
            x = (x + ans) % n + 1;
            x = find(x);
            cout << (ans = f[x]) << endl;
        }
    }
    return 0;
}