#include <cstdio>
using namespace std;

constexpr int MAXN = 3e3 + 10;

int n;
double p[MAXN][MAXN], prod[MAXN], f[MAXN];
bool vis[MAXN];

int main() {
    scanf("%d", &n);

    if (n == 1) {
        printf("0\n");
        return 0;
    }

    for (int i = 1; i <= n; ++i) {
        prod[i] = 1;

        for (int j = 1; j <= n; ++j) {
            scanf("%lf", &p[i][j]);
            p[i][j] /= 100;
        }
    }

    vis[n] = true;

    for (int i = 1; i < n; ++i) {
        prod[i] = 1 - p[i][n];
        f[i] = 1;
    }

    for (int i = 1; i <= n; ++i) {
        int y = 0;
        
        for (int j = 1; j <= n; ++j)
            if (!vis[j] && (!y || f[j] / (1 - prod[j]) < f[y] / (1 - prod[y])))
                y = j;
        
        vis[y] = true;

        if (y == 1) {
            printf("%.10lf\n", f[y] / (1 - prod[y]));
            return 0;
        }

        for (int x = 1; x <= n; ++x) {
            f[x] += f[y] / (1 - prod[y]) * p[x][y] * prod[x];
            prod[x] *= 1 - p[x][y];
        }
    }

    return 0;
}