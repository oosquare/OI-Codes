#include <iostream>
#include <bitset>

constexpr int MAX_N = 500 + 2;

int n, m, q, type;
char grid[MAX_N][MAX_N];
std::bitset<MAX_N> bs[10][MAX_N][MAX_N];
int id[MAX_N], dep[MAX_N * 4];
int ans, last;

void build(int x, int l, int r) {
    if (l > r)
        return;

    int mid = (l + r) / 2;
    int d = dep[x];

    for (int i = 1; i <= m; ++i) {
        if (grid[mid][i] == '.') {
            bs[d][mid][i][i] = true;

            if (i > 0 && grid[mid][i - 1] == '.')
                bs[d][mid][i] |= bs[d][mid][i - 1];
        }
    }

    for (int i = mid + 1; i <= r; ++i)
        for (int j = 1; j <= m; ++j)
            if (grid[i][j] == '.')
                bs[d][i][j] = bs[d][i - 1][j] | bs[d][i][j - 1];

    for (int i = m; i >= 1; --i) {
        bs[d][mid][i].reset();

        if (grid[mid][i] == '.') {
            bs[d][mid][i][i] = true;

            if (i < m && grid[mid][i + 1] == '.')
                bs[d][mid][i] |= bs[d][mid][i + 1];
        }
    }

    for (int i = mid - 1; i >= l; --i)
        for (int j = m; j >= 1; --j)
            if (grid[i][j] == '.')
                bs[d][i][j] = bs[d][i + 1][j] | bs[d][i][j + 1];

    if (l == r) {
        id[l] = x;
        return;
    }

    dep[x * 2] = dep[x * 2 + 1] = dep[x] + 1;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
}

int lca(int x, int y) {
    int ix = id[x], iy = id[y];

    while (dep[ix] > dep[iy])
        ix /= 2;

    while (dep[ix] < dep[iy])
        iy /= 2;

    while (ix != iy) {
        ix /= 2;
        iy /= 2;
    }

    return ix;
}

bool query(int x1, int y1, int x2, int y2) {
    int l = lca(x1, x2);
    return (bs[dep[l]][x1][y1] & bs[dep[l]][x2][y2]).any();
}

int power(int x, int y) {
    int res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = 1ll * res * x % 1000000007;

        x = 1ll * x * x % 1000000007;
    }

    return res;
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("walk.in", "r", stdin);
    std::freopen("walk.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::scanf("%d%d", &n, &type);
    m = n;

    for (int i = 1; i <= n; ++i)
        std::scanf("%s", grid[i] + 1);

    build(1, 1, n);

    std::scanf("%d", &q);

    for (int i = 1; i <= q; ++i) {
        int x1, y1, x2, y2;
        std::scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        x1 ^= last * type;
        y1 ^= last * type;
        x2 ^= last * type;
        y2 ^= last * type;

        if (x1 > x2 || y1 > y2 || grid[x1][y1] == '#' || grid[x2][y2] == '#')
            ans = 0;
        else
            ans = query(x1, y1, x2, y2);

        std::printf(ans ? "Yes\n" : "No\n");
        last = (last + power(ans + 1, i)) % 1000000007;
    }

    return 0;
}
