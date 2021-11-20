#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>
#include <vector>
using namespace std;

constexpr int maxn = 3000 + 10;

struct Item {
    int w, r;

    bool operator<(const Item &rhs) const {
        return r < rhs.r;
    }
};

int n, ans, f[maxn][maxn];
Item items[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> items[i].w >> items[i].r;

    sort(items + 1, items + 1 + n);

    f[n][1] = items[n].w;

    for (int i = n; i >= 1; --i) {
        for (int j = 1; j <= n - i + 1; ++j) {
            f[i][j] = max(f[i + 1][j], f[i + 1][j - 1] + items[i].w - (j - 1) * items[i].r);
        }
    }

    for (int i = 1; i <= n; ++i)
        ans = max(ans, f[1][i]);

    cout << ans << endl;
    return 0;
}