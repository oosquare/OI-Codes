#include <bits/stdc++.h>
using namespace std;

int n, m, st[50][50], ans;
/* status:
 - 0 none
 - 1 (x, y) + (x, y + 1)
 - 2 (x, y) + (x + 1, y)
 - 3 (x, y) + (x - 1, y) & (x, y) + (x, y - 1)  
*/

bool check() {
    for (int i = 1; i <= m; ++i)
        if (st[n][i] == 0)
            return false;
    return true;
}

void DFS(int x, int y) {
    if (x > n) {
        if (check())
            ++ans;
        return;
    }
    if (y > m) {
        DFS(x + 1, 1);
        return;
    }
    if (st[x][y])
        DFS(x, y + 1);
    else {
        bool vaild = (((st[x - 2][y] == 2) || (st[x - 1][y] == 1)) && 
            ((st[x - 2][y - 1] == 2) || (st[x - 1][y - 2] == 1))) == false;
        if (vaild) {
            if (y + 1 <= m && st[x][y + 1] == 0) {
                st[x][y] = 1;
                st[x][y + 1] = 3;
                DFS(x, y + 2);
                st[x][y] = st[x][y + 1] = 0;
            }
            if (x + 1 <= n) {
                st[x][y] = 2;
                st[x + 1][y] = 3;
                DFS(x, y + 1);
                st[x][y] = st[x + 1][y] = 0;
            }
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("floor.in", "r", stdin);
    freopen("floor.out", "w", stdout);
#endif
    cin >> n >> m;
    if (n % 2 == 1 && m % 2 == 1) {
        cout << 0 << endl;
        return 0;
    }
    DFS(1, 1);
    cout << ans << endl;
}
