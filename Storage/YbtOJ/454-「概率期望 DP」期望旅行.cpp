#include <cstdio>
using namespace std;

constexpr int MAXN = 3e3 + 10;

int n;
double p[MAXN][MAXN], prod[MAXN], f[MAXN], g[MAXN];
bool vis[MAXN];

int main() {
#ifdef ONLINE_JUDGE
    freopen("trip.in", "r", stdin);
    freopen("trip.out", "w", stdout);
#endif

    scanf("%d", &n);

    if (n == 1) {
        printf("0\n");
        return 0;
    }

    for (int i = 1; i <= n; ++i) {
        prod[i] = 1;

        for (int j = 1; j <= n; ++j)
            scanf("%lf", &p[i][j]);
    }

    vis[n] = true;

    for (int i = 1; i < n; ++i) {
        prod[i] = 1 - p[i][n];
        f[i] = 1;
        g[i] = f[i] / (1 - prod[i]);
    }

    for (int i = 1; i <= n; ++i) {
        int y = 0;
        
        for (int j = 1; j <= n; ++j)
            if (!vis[j] && (!y || g[j] < g[y]))
                y = j;
        
        vis[y] = true;

        if (y == 1) {
            printf("%.10lf\n", g[y]);
            return 0;
        }

        for (int x = 1; x <= n; ++x) {
            f[x] += g[y] * p[x][y] * prod[x];
            prod[x] *= 1 - p[x][y];
            g[x] = f[x] / (1 - prod[x]);
        }
    }

    return 0;
}
