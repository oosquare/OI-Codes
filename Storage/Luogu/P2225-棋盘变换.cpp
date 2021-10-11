#include <bits/stdc++.h>
using namespace std;

// struct Grid {
//     int size, grid[35][35];

//     Grid(int n = 0) : size(n) {
//         for (int i = 1; i <= size; ++i)
//             for (int j = 1; j <= size; ++j)
//                 grid[i][j] = 0;
//     }

//     int *operator[](int x) {
//         return grid[x];
//     }

//     const int *operator[](int x) const {
//         return grid[x];
//     }

//     Grid rotate() const {
//         Grid res;
//         res.size = size;
//         for (int i = 1; i <= size; ++i)
//             for (int j = 1; j <= size; ++j)
//                 res[j][size - i + 1] = grid[i][j];
//         return res;
//     }

//     Grid filpHorizontal() const {
//         Grid res;
//         res.size = size;
//         for (int i = 1; i <= size; ++i)
//             for (int j = 1; j <= size; ++j)
//                 res[i][size - j + 1] = grid[i][j];
//         return res;
//     }

//     Grid flipVertical() const {
//         Grid res;
//         res.size = size;
//         for (int i = 1; i <= size; ++i)
//             for (int j = 1; j <= size; ++j)
//                 res[size - i + 1][j] = grid[i][j];
//         return res;
//     }
//     bool operator==(const Grid &rhs) const {
//         if (size != rhs.size)
//             return false;
//         for (int i = 1; i <= size; ++i)
//             for (int j = 1; j <= size; ++j)
//                 if (grid[i][j] != rhs[i][j])
//                     return false;
//         return true;
//     }

//     friend ostream &operator<<(ostream &os, const Grid &g) {
//         for (int i = 1; i <= g.size; ++i) {
//             for (int j = 1; j <= g.size; ++j)
//                 os << g[i][j] << " ";
//             os << endl;
//         }
//         return os;
//     }
// };

// struct GridHash {
//     size_t operator()(const Grid& g) const {
//         size_t res = 0;
//         for (int i = 1; i <= g.size; ++i)
//             for (int j = 1; j <= g.size; ++j)
//                 res = res * 2 + (g[i][j] == 1 ? 1 : 0);
//         return res;
//     }
// };

// class Runner {
// public:
//     Runner(int n = 0) : grid(n) {}

//     void exec() {
//         ans.clear();
//         dfs(1);
//         cout << "Task #" + to_string(grid.size) + " finished.\n";
//         cout << flush;
//     }

//     int result() const {
//         return ans.size();
//     }
// private:
//     Grid grid;
//     static constexpr int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
//     unordered_set<Grid, GridHash> ans;

//     bool invaild(int x, int y) {
//         return x < 1 || x > grid.size || y < 1 || y > grid.size;
//     }

//     bool check(int x, int y) {
//         if (invaild(x, y) == true)
//             return true;
//         int res = 1;
//         for (int i = 0; i < 4; ++i) {
//             int nx = x + dir[i][0], ny = y + dir[i][1];
//             if (invaild(nx, ny) == true)
//                 continue;
//             res *= grid[nx][ny];
//         }
//         return res == grid[x][y];
//     }

//     void check() {
//         for (int i = 2; i <= grid.size; ++i) {
//             for (int j = 1; j <= grid.size; ++j) {
//                 grid[i][j] = 1;
//                 if (check(i - 1, j) == false)
//                     grid[i][j] = -1;
//             }
//         }
//         for (int i = 1;i <= grid.size; ++i)
//             if (check(grid.size, i) == false)
//                 return;
//         auto tmp = grid;
//         for (int i = 1; i <= 4; ++i) {
//             tmp = tmp.rotate();
//             if (ans.find(tmp) != ans.end())
//                 return;
//             if (ans.find(tmp.filpHorizontal()) != ans.end())
//                 return;
//             if (ans.find(tmp.flipVertical()) != ans.end())
//                 return;
//         }
//         ans.insert(grid);
//     }

//     void dfs(int dep) {
//         if (dep == grid.size + 1) {
//             check();
//             return;
//         }
//         grid[1][dep] = 1;
//         dfs(dep + 1);
//         grid[1][dep] = -1;
//         dfs(dep + 1);
//         grid[1][dep] = 0;
//     }
// };

// Runner runner[31];
// thread handle[31];

// void exec(int l, int r) {
//     for (int i = l; i <= r; ++i) {
//         runner[i] = Runner(i);
//         handle[i] = thread(Runner::exec, &runner[i]);
//     }
//     for (int i = l; i <= r; ++i)
//         handle[i].join();
// }

// int main() {
//     ios::sync_with_stdio(false);
//     const int maxTask = 30;
//     const int maxThread = 16;
//     for (int l = 1, r; l <= maxTask; l += maxThread) {
//         r = min(l + maxThread - 1, maxTask);
//         exec(l, r);
//     }
//     cout << "{0";
//     for (int i = 1; i <= maxTask; ++i)
//         cout << ", " << runner[i].result();
//     cout << "}" << endl;
//     return 0;
// }

constexpr int ans[30] = {
    1, 1, 1, 5, 3, 1, 1, 1, 43, 1, 21,
    1, 1, 5, 1, 43, 3, 1, 8356, 1, 1,
    1, 2628, 5, 1, 1, 1, 1, 162, 131720
};
int n;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    cout << ans[n - 1] << endl;
    return 0;
}