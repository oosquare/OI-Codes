#include <iostream>
#include <iterator>
#include <vector>

constexpr int MAX_N = 100 + 1;

int n, m;
char mat[MAX_N][MAX_N];
std::vector<int> graph[MAX_N * MAX_N];
int match[MAX_N * MAX_N];
bool vis[MAX_N * MAX_N], selected[MAX_N * MAX_N];
std::vector<std::pair<int, int>> solutions;

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
    selected[x] = true;

    for (int y : graph[x]) {
        if (y == match[x])
            continue;

        mark(match[y]);
    }
}

void find() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (mat[i][j] == '#' || color(i, j))
                continue;

            for (int k = 1; k <= n * m; ++k)
                vis[k] = false;

            augment(id(i, j));
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (mat[i][j] == '#' || match[id(i, j)])
                continue;

            for (int k = 1; k <= n * m; ++k)
                vis[k] = false;

            mark(id(i, j));
        }
    }
}

void build() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < m; ++j) {
            if (mat[i][j] == '#' || mat[i][j + 1] == '#')
                continue;

            link(id(i, j), id(i, j + 1));
        }
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (mat[i][j] == '#' || mat[i + 1][j] == '#')
                continue;

            link(id(i, j), id(i + 1, j));
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        std::cin >> (mat[i] + 1);

    build();
    find();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (mat[i][j] == '#' || !selected[id(i, j)])
                continue;

            solutions.emplace_back(i, j);
        }
    };

    if (!solutions.empty())
        std::cout << "WIN" << std::endl;
    else
        std::cout << "LOSE" << std::endl;

    for (auto [x, y] : solutions)
        std::cout << x << " " << y << std::endl;

    return 0;
}
