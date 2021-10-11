#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2000 + 10;

int n, m, ans, fa[maxn], cnt[maxn];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y)
        return;
    fa[x] = y;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= 2 * n; ++i)
        fa[i] = i;
    for (int i = 1; i <= m; ++i) {
        char op[10];
        int x, y;
        cin >> op >> x >> y;
        if (op[0] == 'F') {
            merge(x, y);
        } else {
            merge(x, y + n);
            merge(x + n, y);
        }
    }
    for (int i = 1; i <= n; ++i)
        ++cnt[find(i)];
    for (int i = 1; i <= 2 * n; ++i)
        ans += (cnt[i] > 0);
    cout << ans << endl;
    return 0;
}