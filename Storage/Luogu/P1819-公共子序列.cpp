#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 150 + 10;
constexpr int mod = 1e8;

int n, nxt[3][maxn][26], f[maxn][maxn][maxn];
char str[3][maxn];

int dfs(int x, int y, int z) {
    if (f[x][y][z])
        return f[x][y][z];
    int res = 0;
    for (int i = 0; i < 26; ++i)
        if (nxt[0][x][i] && nxt[1][y][i] && nxt[2][z][i])
            (res += dfs(nxt[0][x][i], nxt[1][y][i], nxt[2][z][i])) %= mod;
    if (x || y || z)
        ++res;
    f[x][y][z] = res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < 3; ++i) {
        cin >> (str[i] + 1);

        for (int j = n - 1; j >= 0; --j) {
            for (int k = 0; k < 26; ++k)
                nxt[i][j][k] = nxt[i][j + 1][k];
            nxt[i][j][str[i][j + 1] - 'a'] = j + 1;
        }
    }
    cout << dfs(0, 0, 0) << endl;
    return 0;
 }