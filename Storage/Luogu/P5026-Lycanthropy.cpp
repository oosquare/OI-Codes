#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6 + 10;
constexpr int delta = 40000;

int n, m, a[maxn * 2];

void print() {
    for (int i = 1; i <= n; ++i)
        cout << a[delta + i] << " ";
    cout << endl;
}

void add0(int l, int r, int k) {
    if (l > r)
        return;
    l += delta;
    r += delta;
    a[l] += k;
    a[r + 1] -= k;
}

void add(int l, int r, int st, int k) {
    if (l > r)
        return;
    add0(l, l, st);
    add0(l + 1, r, k);
    add0(r + 1, r + 1, - st - (r - l) * k);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> m >> n;
    for (int i = 1; i <= m; ++i) {
        int v, x;
        cin >> v >> x;
        add(x - v + 1, x, -1, -1);
        add(x + 1, x + v - 1, -(v - 1), 1);
        add(x - 2 * v, x - v - 1, v, -1);
        add(x - 3 * v + 1, x - 2 * v - 1, 1, 1);
        add(x + v + 1, x + 2 * v, 1, 1);
        add(x + 2 * v + 1, x + 3 * v - 1, v - 1, -1);
    }
    for (int i = 1; i <= 2 * delta + n; ++i)
        a[i] += a[i - 1];
    for (int i = 1; i <= 2 * delta + n; ++i)
        a[i] += a[i - 1];
    print();
    return 0;
}