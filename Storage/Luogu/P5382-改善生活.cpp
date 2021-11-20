#include <iostream>
#include <algorithm>
#include <utility>
#include <queue>
#include <vector>
using namespace std;

constexpr int maxn = 700 + 10;

int n, m, c[maxn], w[maxn];
vector<int> graph[maxn];
int reach[maxn][maxn], sum[maxn];
int ans;

void link(int x, int y) {
    graph[x].push_back(y);
}

void dfs(int start, int x) {
    if (reach[start][x])
        return;

    reach[start][x] = true;

    for (int y : graph[x])
        dfs(start, y);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)   
        cin >> c[i];

    for (int i = 1; i <= n; ++i)
        cin >> w[i];

    for (int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
    }

    for (int i = 1; i <= n; ++i)
        if (c[i] == 1)
            dfs(i, i);

    for (int i = 1; i <= n; ++i) {
        if (c[i] != 1)
            continue;

        for (int j = 1; j <= n; ++j)
            sum[j] = 0;

        for (int j = 1; j <= n; ++j)
            if (reach[i][j])
                sum[c[j]] += w[j];

        for (int j = 2; j <= n; ++j)
            ans = max(ans, sum[j] / w[i]);
    }

    cout << ans << endl;
    return 0;
}