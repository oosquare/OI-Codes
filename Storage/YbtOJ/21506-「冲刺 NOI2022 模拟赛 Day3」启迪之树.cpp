#pragma GCC optimize(2)
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
using namespace std;

constexpr int MAX_N = 1e5 + 10;
constexpr int SIZE = 50;

int n, q, k, s;
vector<int> tree[MAX_N];
int sze[MAX_N];
int f[SIZE + 2][MAX_N], g[MAX_N][MAX_N / SIZE + 2], tmp[MAX_N];

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void dfs1(int id, int k, int x, int fa) {
    f[id][x] = 0;

    for (int y : tree[x]) {
        if (y == fa)
            continue;
        
        dfs1(id, k, y, x);
        f[id][x] += max(f[id][y] - k, 1);
    }
}

void dfs2(int x, int fa, int lim) {
    sze[x] = 1;

    for (int y : tree[x]) {
        if (y == fa)
            continue;
        
        dfs2(y, x, lim);

        for (int i = 0; i <= min(lim, sze[x]); ++i) {
            tmp[i] = g[x][i];
            g[x][i] = g[x][i] + 1;
        }
        
        for (int i = 0; i <= min(lim, sze[x]); ++i) {
            for (int j = 0; j <= min(lim, sze[y]); ++j) {
                if (i + j + 1 > lim)
                    continue;
                
                g[x][i + j + 1] = max(g[x][i + j + 1], tmp[i] + g[y][j]);
            }
        }

        sze[x] += sze[y];
    }
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
#else
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    clockid_t st = clock();
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
    }

    for (int i = 0; i <= SIZE; ++i)
        dfs1(i, i, 1, 0);
    
    dfs2(1, 0, MAX_N / SIZE + 1);
    
    cin >> q;

    for (int i = 1; i <= q; ++i) {
        int x, k;
        cin >> x >> k;
        
        if (k <= SIZE) {
            cout << f[k][x] << endl;
        } else {
            int ans = 0;

            for (int i = 0; i <= n / k + 1; ++i)
                ans = max(ans, g[x][i] - i * k);
            
            cout << ans << endl;
        }
    }
    cerr << clock() - st << endl;
    return 0;
}
