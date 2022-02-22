#include <iostream>
#include <vector>
using namespace std;

constexpr int MAX_N = 1000 + 10;
constexpr int MAX_M = 2000 + 10;

int n, m;
int col[MAX_N];
vector<int> tmp[MAX_N], graph[MAX_N];
bool vis[MAX_N];
int match[MAX_N];

void link(vector<int> graph[], int x, int y) {
    graph[x].push_back(y);
}

void coloring(int x, int now) {
    if (vis[x])
        return;

    col[x] = now;
    vis[x] = true;

    for (int y : tmp[x]) {
        if (!now)
            link(graph, x, y);
        
        coloring(y, now ^ 1);
    }
}

bool augment(int x) {
    for (int y : graph[x]) {
        if (vis[y])
            continue;

        vis[y] = true;

        if (!match[y] || augment(match[y])) {
            match[y] = x;
            return true;
        }
    }

    return false;
}

int hungary() {
    int res = 0;

    for (int i = 1; i <= n; ++i) {
        if (col[i])
            continue;
        
        for (int j = 1; j <= n; ++j)
            vis[j] = false;
        
        if (augment(i))
            ++res;
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;
        ++x;
        ++y;
        link(tmp, x, y);
        link(tmp, y, x);
    }

    for (int i = 1; i <= n; ++i)
        if (!vis[i])
            coloring(i, 0);
        
    cout << n - hungary() << endl;
    return 0;
}