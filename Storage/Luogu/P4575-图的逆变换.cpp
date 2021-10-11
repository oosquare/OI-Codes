#include <bits/stdc++.h>
using namespace std;

constexpr int maxm = 300 + 10;

int t, m, k;
bool graph[maxm][maxm];

void solve() {
    memset(graph, 0, sizeof(graph));
    cin >> m >> k;
    for (int i = 1; i <= k; ++i) {
        int x, y;
        cin >> x >> y;
        graph[x + 1][y + 1] = true;
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = i + 1; j <= m; ++j) {
            bool f1 = false, f2 = false;
            for (int k = 1; k <= m; ++k) {
                f1 |= graph[i][k] & graph[j][k];
                f2 |= graph[i][k] ^ graph[j][k];
                if (f1 == true && f2 == true) {
                    cout << "No" << endl;
                    return;
                }
            }
        }
    }
    cout << "Yes" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> t;
    while (t--)
        solve();
    return 0;
}