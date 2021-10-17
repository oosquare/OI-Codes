#include <bits/stdc++.h>
using namespace std;

constexpr int oo = 0x3f3f3f3f;

int n, m, all, ans = oo;
int graph[12][12];
int ext[1 << 12], f[1 << 12][13];

int main() {
    ios::sync_with_stdio(false);
    memset(graph, 0x3f, sizeof(graph));
    memset(f, 0x3f, sizeof(f));
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int x, y, v;
        cin >> x >> y >> v;
        --x;
        --y;
        graph[x][y] = graph[y][x] = min(graph[x][y], v);
    }

    for (int i = 0; i < n; ++i)
        graph[i][i] = 0;

    all = (1 << n) - 1;

    for (int s = 0; s <= all; ++s) {
        for (int i = 0; i < n; ++i) {
            if (((s >> i) & 1) == 0)
                continue;

            for (int j = 0; j < n; ++j) {
                if (graph[i][j] == oo)
                    continue;

                ext[s] |= (1 << j);
            }
        }
    }

    for (int i = 0; i < n; ++i)
        f[1 << i][0] = 0;

    for (int s = 2 ; s <= all; ++s) {
        for (int s2 = s - 1; s2; s2 = (s2 - 1) & s) {
            if ((ext[s2] | s) != ext[s2])
                continue;

            int ds = s ^ s2;
            int sum = 0;

            for (int i = 0; i < n; ++i) {
                if (((ds >> i) & 1) == 0)
                    continue;

                int mx = oo;

                for (int j = 0; j < n; ++j) {
                    if (((s2 >> j) & 1) == 0)
                        continue;

                    mx = min(mx, graph[i][j]);
                }

                sum += mx;
            }

            for (int i = 1; i < n; ++i) {
                if (f[s2][i - 1] == oo)
                    continue;

                f[s][i] = min(f[s][i], f[s2][i - 1] + i * sum);
            }
        }
    }

    for (int i = 0; i <= n; ++i)
        ans = min(ans, f[all][i]);

    cout << ans << endl;
    return 0;
}