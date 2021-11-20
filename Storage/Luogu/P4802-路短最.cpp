#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

constexpr int maxn = 18;
constexpr int oo = 0x7fffffff;

int n, m;
vector<pair<int, int>> graph[maxn];
int f[maxn][1 << maxn], ans = -oo;

void link(int x, int y, int l) {
    graph[x].push_back({y, l});
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int x, y, l;
        cin >> x >> y >> l;
        link(x, y, l);
    }

    for (int s = 0; s < (1 << n); ++s)
        for (int i = 0; i < n; ++i)
            f[i][s] = -oo;

    f[0][1] = 0;

    for (int s = 1; s < (1 << n); ++s) {
        for (int x = 0; x < n; ++x) {
            if (!((s >> x) & 1))
                continue;

            for (auto [y, l] : graph[x]) {
                if (((s >> y) & 1) || x == y)
                    continue;

                f[y][s ^ (1 << y)] = max(f[y][s ^ (1 << y)], f[x][s] + l);
            }
        }
    }

    for (int s = 1; s < (1 << n); ++s)
        if ((s & 1) || ((s >> (n - 1)) & 1))
            ans = max(ans, f[n - 1][s]);

    cout << ans << endl;
    return 0;
}