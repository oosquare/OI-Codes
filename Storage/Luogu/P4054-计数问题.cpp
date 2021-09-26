#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 300 + 10;
constexpr int maxc = 100 + 10;

int n, m, q, arr0[maxn][maxn], arr[maxc][maxn][maxn];

inline int lowbit(int x) {
    return x & (-x);
}

void add(int c, int x, int y, int v) {
    for (int i = x; i <= n; i += lowbit(i)) {
        for (int j = y; j <= m; j += lowbit(j)) {
            arr[c][i][j] += v;
        }
    }
}

int sum(int c, int x, int y) {
    int res = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
        for (int j = y; j > 0; j -= lowbit(j)) {
            res += arr[c][i][j];
        }
    }
    return res;
}

int sum(int c, int x1, int y1, int x2, int y2) {
    return sum(c, x2, y2) - sum(c, x1 - 1, y2) - sum(c, x2, y1 - 1) + sum(c, x1 - 1, y1 - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> arr0[i][j];
            add(arr0[i][j], i, j, 1);
        }
    }
    cin >> q;
    for (int i = 1; i <= q; ++i) {
        int op, a, b, c, d, e;
        cin >> op >> a >> b >> c;
        if (op == 1) {
            add(arr0[a][b], a, b, -1);
            arr0[a][b] = c;
            add(c, a, b, 1);
        } else {
            cin >> d >> e;
            cout << sum(e, a, c, b, d) << endl;
        }
    }
    return 0;
}