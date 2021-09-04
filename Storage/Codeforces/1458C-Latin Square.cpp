#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e3 + 10;

int t, n, m, mat[maxn][maxn][3], ans[maxn][maxn], from[3], delta[3];
char s[maxn * maxn];

void solve() {
    cin >> n >> m;
    for (int i = 0; i < 3; ++i) {
        from[i] = i;
        delta[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> mat[i][j][2];
            --mat[i][j][2];
            mat[i][j][0] = i;
            mat[i][j][1] = j;
        }
    }
    cin >> s;
    for (int i = 0; i < m; ++i) {
        switch (s[i]) {
            case 'L':
                --delta[1];
                break;
            case 'R':
                ++delta[1];
                break;
            case 'U':
                --delta[0];
                break;
            case 'D':
                ++delta[0];
                break;
            case 'I':
                swap(from[1], from[2]);
                swap(delta[1], delta[2]);
                break;
            case 'C':
                swap(from[0], from[2]);
                swap(delta[0], delta[2]);
                break;
        }
    }
    for (int i = 0; i < 3; ++i) {
        delta[i] = (delta[i] % n + n) % n;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int tmp[3];
            for (int k = 0; k < 3; ++k) {
                tmp[k] = (mat[i][j][from[k]] + delta[k]) % n;
            }
            ans[tmp[0]][tmp[1]] = tmp[2] + 1;
        }
    }
    for (int i = 0; i < n; ++i, cout << endl) {
        for (int j = 0; j < n; ++j) {
            cout << ans[i][j] << " ";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> t;
    while (t--) solve();
    return 0;
}