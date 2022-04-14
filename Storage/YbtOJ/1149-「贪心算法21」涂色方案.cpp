#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>
#include <vector>
using namespace std;

constexpr int oo = 0x3f3f3f3f;
constexpr int maxn = 1e5 + 10;

struct Rectangle {
    int x1, y1, x2, y2;

    bool invaild() {
        return x1 > x2 || y1 > y2;
    }

    void update(int x, int y) {
        x1 = min(x1, x);
        y1 = min(y1, y);
        x2 = max(x2, x);
        y2 = max(y2, y);
    }
};

int n, m, k, ans;
vector<int> a[maxn], c[maxn];
Rectangle rect[maxn];
bool vis[maxn];

int main() {
    freopen("paint.in", "r", stdin);
    freopen("paint.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;

    for (int i = 1; i <= k; ++i)
        rect[i] = {n + 1, m + 1, 0, 0};

    for (int i = 0; i <= n + 2; ++i) {
        a[i] = vector<int>(m + 10);
        c[i] = vector<int>(m + 10);
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            
            if (a[i][j])
                rect[a[i][j]].update(i, j);
        }
    }

    bool sp = true;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (a[i][j] != a[1][1])
                sp = false;

    if (k == 1)
        sp = false;

    if (sp) {
        cout << k - 1 << endl;
        return 0;
    }

    for (int i = 1; i <= k; ++i) {
        if (rect[i].invaild())
            continue;

        auto [x1, y1, x2, y2] = rect[i];
        ++c[x1][y1];
        --c[x1][y2 + 1];
        --c[x2 + 1][y1];
        ++c[x2 + 1][y2 + 1];
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            c[i][j] = c[i][j] + c[i - 1][j] + c[i][j - 1] - c[i - 1][j - 1];

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (c[i][j] > 1)
                vis[a[i][j]] = true;

    for (int i = 1; i <= k; ++i)
        ans += (vis[i] == false);

    cout << ans << endl;
    return 0;
}
