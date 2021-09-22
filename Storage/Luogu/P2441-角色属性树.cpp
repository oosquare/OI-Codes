#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 200000 + 10;

int fa[maxn], w[maxn];
int n, k;

int gcd(int x, int y) {
    return y == 0 ? x : gcd(y, x % y);
}

int query(int x) {
    int f = fa[x];
    while (f != 0 && gcd(w[f], w[x]) == 1) f = fa[f];
    return f == 0 ? -1 : f;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> w[i];
    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        fa[y] = x;
    }
    for (int i = 1; i <= k; ++i) {
        int op, x, y;
        cin >> op >> x;
        if (op == 1) {
            cout << query(x) << endl;
        } else {
            cin >> y;
            w[x] = y;
        }
    }
    return 0;
}