#include <cstring>
#include <iostream>
using namespace std;
long long a[30][30];
int vis[30][30];
int nxt[][2] = {{2, 1},   {1, 2},   {-1, 2}, {-2, 1},
                {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
int main() {
    int n, m;
    int x, y;
    int nx, ny;
    int i, j;

    memset(vis, 0, sizeof(vis));
    cin >> n >> m >> x >> y;

    a[0][0] = 0;
    vis[x][y] = 1;
    a[x][y] = 0;
    for (i = 0; i < 8; i++) {
        nx = x + nxt[i][0];
        ny = y + nxt[i][1];
        if (0 <= nx && nx <= n && 0 <= ny && ny <= m) {
            vis[nx][ny] = 1;
            a[nx][ny] = 0;
        }
    }
    for (i = 0; i <= n; i++) {
        if (vis[i][0] == 1)
            while (i <= n) {
                i++;
                a[i][0] = 0;
            }
        else
            a[i][0] = 1;
    }
    for (j = 0; j <= m; j++) {
        if (vis[0][j] == 1)
            while (j <= m) {
                j++;
                a[0][j] = 0;
            }
        else
            a[0][j] = 1;
    }
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            if (vis[i][j] == 0)
                a[i][j] = a[i][j - 1] + a[i - 1][j];
    cout << a[n][m] << endl;
    return 0;
}