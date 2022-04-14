#include <iostream>
#include <vector>
#include <cassert>

constexpr int MAX_N = 100 + 1;

int n, m;
char mat[MAX_N][MAX_N];
std::vector<int> graph[MAX_N * MAX_N];
int match[MAX_N * MAX_N];
bool vis[MAX_N * MAX_N], sel[MAX_N * MAX_N];

int color(int x, int y) { return (x + y) % 2; }

int color(int x) { return color((x + n - 1) / m, (x - 1) % m + 1); }

int id(int x, int y) { return (x - 1) * m + y; }

void link(int x, int y) {
    graph[x].push_back(y);
    graph[y].push_back(x);
}

bool augment(int x) {
    for (int y : graph[x]) {
        if (vis[y])
            continue;

        vis[y] = true;

        if (!match[y] || augment(match[y])) {
            match[x] = y;
            match[y] = x;
            return true;
        }
    }

    return false;
}

void mark(int x) {
    if (vis[x])
        return;

    vis[x] = true;
    sel[x] = true;

    for (int y : graph[x]) {
        if (y == match[x])
            continue;

        mark(match[y]);
    }
}

void find() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (mat[i][j] == 'X' || color(i, j))
                continue;

            for (int k = 1; k <= n * m; ++k)
                vis[k] = false;

            augment(id(i, j));
        }
    }

    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= m; ++j) {
    //         std::cout << id(i, j) << " " << match[id(i, j)] << std::endl;
    //     }
    // }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (mat[i][j] == 'X' || match[id(i, j)])
                continue;
            
            for (int k = 1; k <= n * m; ++k)
                vis[k] = false;
            
            mark(id(i, j));
        }
    }
}

void solve() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            graph[id(i, j)].clear();
            sel[id(i, j)] = false;
            match[id(i, j)] = 0;
        }
    }

    for (int i = 1; i <= n; ++i)
        std::cin >> (mat[i] + 1);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < m; ++j) {
            if (mat[i][j] == 'X' || mat[i][j + 1] == 'X')
                continue;

            link(id(i, j), id(i, j + 1));
            // std::cout << id(i, j) << " " << id(i, j + 1) << std::endl;
        }
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (mat[i][j] == 'X' || mat[i + 1][j] == 'X')
                continue;

            link(id(i, j), id(i + 1, j));
            // std::cout << id(i, j) << " " << id(i + 1, j) << std::endl;
        }
    }

    find();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (mat[i][j] == 'X')
                std::cout.put('X');
            else if (sel[id(i, j)])
                std::cout.put('B');
            else
                std::cout.put('A');
        }

        std::cout << std::endl;
    }
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("a.in", "r", stdin);
    std::freopen("a.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);

    while (true) {
        std::cin >> n >> m;

        if (!n && !m)
            break;

        solve();
    }

    return 0;
}
