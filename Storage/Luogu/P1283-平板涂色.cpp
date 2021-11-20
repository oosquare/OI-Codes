#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

constexpr int maxn = 16 + 1;
constexpr int oo = 0x3f3f3f3f;

struct Rectangle {
    int x1, y1, x2, y2, c;

    bool above(const Rectangle &rhs) const {
        return x1 == rhs.x2 && (!(rhs.y2 <= y1 || y2 <= rhs.y1));
    }
};

int n, ans = oo;
Rectangle rect[maxn];
int pre[1 << maxn], f[maxn][1 << maxn];

bool isSubset(int s1, int s2) {
    for (int i = 1; i <= n; ++i)
        if (((s1 >> (i - 1)) & 1) && (!((s2 >> (i - 1)) & 1)))
            return false;

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        auto &[x1, y1, x2, y2, c] = rect[i];
        cin >> x1 >> y1 >> x2 >> y2 >> c;
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (rect[i].above(rect[j]))
                pre[1 << (i - 1)] |= (1 << (j - 1));

    for (int s = 0; s < (1 << n); ++s)
        for (int i = 1; i <= n; ++i)
            if ((s >> (i - 1)) & 1)
                pre[s] |= pre[1 << (i - 1)];

    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < (1 << n); ++j)
            f[i][j] = oo;

    for (int i = 1; i <= n; ++i)
        if (pre[1 << (i - 1)] == 0)
            f[i][1 << (i - 1)] = 1;

    for (int s = 0; s < (1 << n); ++s) {
        if (!isSubset(pre[s], s))
            continue;

        for (int i = 1; i <= n; ++i) {
            if ((!(s >> (i - 1)) & 1))
                continue;

            for (int j = 1; j <= n; ++j) {
                if ((!(s >> (j - 1)) & 1) || i == j)
                    continue;

                f[i][s] = min(f[i][s], f[j][s ^ (1 << (i - 1))] + (rect[i].c != rect[j].c));
            }
        }
    }

    for (int i = 1; i <= n; ++i)
        ans = min(ans, f[i][(1 << n) - 1]);

    cout << ans << endl;
    return 0;
}