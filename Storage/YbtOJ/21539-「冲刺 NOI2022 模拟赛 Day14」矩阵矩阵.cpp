#include <iostream>

constexpr int MAX_N = 1000 + 10;

int n;
char mat[MAX_N][MAX_N], tmp[MAX_N];
int cntx[MAX_N], cnty[MAX_N], full;
int pos[MAX_N];
int sx, sy, first, ans = -1;

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("matrix.in", "r", stdin);
    std::freopen("matrix.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::cin >> n;

    for (int i = 1; i <= n; ++i) {
        std::scanf("%s", mat[i] + 1);

        for (int j = 1; j <= n; ++j) {
            cntx[i] += (mat[i][j] == 'B');
            cnty[j] += (mat[i][j] == 'B');

            if (mat[i][j] == 'B')
                pos[j] = i;
        }
    }

    for (int i = 1; i <= n; ++i)
        full += (cnty[i] == n);

    for (int j = 1; j <= n; ++j) {
        bool found = false;

        for (int i = 1; i <= n; ++i) {
            if (mat[i][j] == 'W')
                continue;
            
            found = true;

            if (ans == -1 || ans > n - cntx[j] + n - full) {
                ans = n - cntx[j] + n - full;
                sx = i;
                sy = j;
                first = 0;
            }
        }

        if (found)
            continue;
        
        for (int i = 1; i <= n; ++i) {
            if (!pos[i])
                continue;
            
            if (ans == -1 || ans > 1 + n - cntx[j] + n - full) {
                ans = 1 + n - cntx[j] + n - full;
                sx = i;
                sy = j;
                first = pos[i];
            }
        }
    }

    std::cout << ans << std::endl;

    if (ans == -1)
        return 0;
    
    if (first) {
        std::cout << first << " " << sy << std::endl;

        for (int j = 1; j <= n; ++j)
            tmp[j] = mat[first][j];

        cnty[sy] = 0;

        for (int i = 1; i <= n; ++i) {
            mat[i][sy] = tmp[i];
            cnty[sy] += (mat[i][sy] == 'B');
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (mat[sy][i] == 'B' || i == sy)
            continue;

        std::cout << sx << " " << i << std::endl;
    }

    if (mat[sy][sy] == 'W')
        std::cout << sx << " " << sy << std::endl;

    for (int i = 1; i <= n; ++i) {
        if (cnty[i] == n)
            continue;

        std::cout << sy << " " << i << std::endl;
    }

    return 0;
}
