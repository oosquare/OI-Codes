#include <iostream>
#include <bitset>
#include <queue>
#include <algorithm>

constexpr int INFINITY = 0x3f3f3f3f;
constexpr int MAX_N = 150 + 1;

struct Edge {
    int from, to, req;

    bool operator<(const Edge &rhs) const {
        return req < rhs.req;
    }
};

struct Matrix {
    std::bitset<MAX_N> mat[MAX_N];
    int row, column;

    void set(int row, int column) {
        this->row = row;
        this->column = column;
    }

    std::bitset<MAX_N> &operator[](int x) {
        return mat[x];
    }

    const std::bitset<MAX_N> &operator[](int x) const {
        return mat[x];
    }

    friend std::bitset<MAX_N> operator*(const std::bitset<MAX_N> &lhs, const Matrix &rhs) {
        std::bitset<MAX_N> res;
        
        for (int i = 1; i <= rhs.column; ++i)
            res[i] = (lhs & rhs[i]).any();

        return res;
    }

    Matrix operator*(const Matrix &rhs) const {
        Matrix res;
        res.set(row, rhs.column);

        for (int i = 1; i <= row; ++i)
            for (int j = 1; j <= column; ++j)
                if (mat[i][j])
                    res[i] |= rhs[j];

        return res;
    }
};

int n, m;
Edge edges[MAX_N];
std::bitset<MAX_N> now;
Matrix trans;
int dis[MAX_N];
int ans;

void power(Matrix x, int y, std::bitset<MAX_N> &res) {
    for (; y; y /= 2) {
        if (y % 2)
            res = res * x;

        x = x * x;
    }
}

int bfs(Matrix &graph, std::bitset<MAX_N> &sta) {
    std::queue<int> q;

    for (int i = 1; i <= n; ++i) {
        if (sta[i]) {
            q.push(i);
            dis[i] = 0;
        } else {
            dis[i] = INFINITY;
        }
    }

    while (!q.empty()) {
        int x = q.front();
        q.pop();

        for (int y = 1; y <= n; ++y) {
            if (!graph[y][x] || dis[y] <= dis[x] + 1)
                continue;

            dis[y] = dis[x] + 1;
            q.push(y);

            if (y == n)
                return dis[y];
        }
    }

    return INFINITY;
}

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> n >> m;
    trans.set(n, n);

    for (int i = 1; i <= m; ++i) {
        auto &[f, t, r] = edges[i];
        std::cin >> f >> t >> r;
    }

    std::sort(edges + 1, edges + 1 + m);
    ans = INFINITY;
    now[1] = true;

    for (int i = 1; i <= m; ++i) {
        auto [from, to, req] = edges[i];

        if (req >= ans)
            break;

        power(trans, req - edges[i - 1].req, now);
        trans[to][from] = true;
        ans = std::min(ans, bfs(trans, now) + req);
    }

    if (ans == INFINITY)
        std::cout << "Impossible" << std::endl;
    else
        std::cout << ans << std::endl;

    return 0;
}
