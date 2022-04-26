#include <array>
#include <iostream>
#include <tuple>

constexpr int MAX_N = 50 + 2;
constexpr int MAX_M = 100000 + 2;

int t;
int fa[MAX_N * MAX_M], next[MAX_N * MAX_M];
bool col[MAX_N * MAX_M];

inline int id(int x, int y) { return (x - 1) * 100000 + y; }

inline int to_y(int id) { return (id - 1) % 100000 + 1; }

int find_fa(int x) { return (x == fa[x] ? x : fa[x] = find_fa(fa[x])); }

int find_next(int x) { return (x == next[x] || next[x] == 0 ? next[x] : next[x] = find_next(next[x])); }

void merge(int x, int y) {
    x = find_fa(x);
    y = find_fa(y);

    if (x != y)
        fa[x] = y;
}

void assign(int x1, int y1, int x2, int y2) {
    for (int i = x1; i <= x2; ++i) {
        for (int j = to_y(find_next(id(i, y1))); j <= y2 && j != 0; j = to_y(find_next(id(i, j)))) {
            col[id(i, j)] = true;
            next[id(i, j)] = (j == 100000 ? 0 : next[id(i, j + 1)]);

            if (i != 1 && col[id(i - 1, j)])
                merge(id(i, j), id(i - 1, j));

            if (i != 50 && col[id(i + 1, j)])
                merge(id(i, j), id(i + 1, j));

            if (j != 1 && col[id(i, j - 1)])
                merge(id(i, j), id(i, j - 1));

            if (j != 100000 && col[id(i, j + 1)])
                merge(id(i, j), id(i, j + 1));
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);

    for (int i = 1; i <= 50 * 100000; ++i)
        fa[i] = next[i] = i;

    std::cin >> t;

    while (t--) {
        int opt, x1, y1, x2, y2;
        std::cin >> opt >> x1 >> y1 >> x2 >> y2;

        if (opt == 0) {
            if (x1 > x2)
                std::swap(x1, x2);

            if (y1 > y2)
                std::swap(y1, y2);

            assign(x1, y1, x2, y2);
        } else {
            if (!col[id(x1, y1)] || !col[id(x2, y2)])
                std::cout << 0 << std::endl;
            else
                std::cout << (find_fa(id(x1, y1)) == find_fa(id(x2, y2)) ? 1 : 0) << std::endl;
        }
    }
    return 0;
}