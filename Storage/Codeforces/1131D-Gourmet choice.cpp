#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
#include <queue>
using namespace std;

constexpr int maxn = 2000 + 10;

int n, m;
char grid[maxn][maxn];
vector<int> graph[maxn];
int in[maxn], f[maxn];
int id[maxn], uuid;
int fa[maxn];

inline void link(int x, int y) {
    graph[x].push_back(y);
    ++in[y];
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);

    if (x != y)
        fa[y] = x;
}

inline int &get(int x) {
    x = find(x);
    return id[x];
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    iota(fa + 1, fa + 1 + n + m, 1);

    for (int i = 1; i <= n; ++i) {
        cin >> (grid[i] + 1);

        for (int j = 1; j <= m; ++j)
            if (grid[i][j] == '=')
                merge(i, j + n);
    }

    for (int i = 1; i <= n + m; ++i)
        if (!get(i))
            get(i) = ++uuid;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (grid[i][j] == '<')
                link(get(i), get(j + n));
            else if (grid[i][j] == '>')
                link(get(j + n), get(i));
        }
    }

    queue<int> q;

    for (int i = 1; i <= uuid; ++i) {
        if (!in[i]) {
            q.push(i);
            f[i] = 1;
        }
    }

    while (!q.empty()) {
        int x = q.front();
        q.pop();

        for (int y : graph[x]) {
            f[y] = max(f[y], f[x] + 1);
            --in[y];

            if (!in[y])
                q.push(y);
        }
    }

    for (int i = 1; i <= uuid; ++i) {
        if (in[i]) {
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;

    for (int i = 1; i <= n; ++i)
        cout << f[get(i)] << " ";

    cout << endl;

    for (int i = n + 1; i <= n + m; ++i)
        cout << f[get(i)] << " ";

    cout << endl;
    return 0;
}