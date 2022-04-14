#include <iostream>
#include <vector>
using namespace std;

constexpr int MAX_N = 100 + 10;

int n, m;
bool closure[MAX_N][MAX_N];

vector<int> graph[MAX_N];
int match[MAX_N];
bool vis[MAX_N], exist[MAX_N];

int ans, col[MAX_N];
bool valid[MAX_N], sol[MAX_N];

void link(int x, int y) {
    graph[x].push_back(y);
}

bool augment(int x) {
    for (int y : graph[x]) {
        if (vis[y] || !exist[y])
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

    for (int i = 1; i <= n; ++i)
        match[i] = 0;

    for (int i = 1; i <= n; ++i) {
        if (!exist[i])
            continue;

        for (int j = 1; j <= n; ++j)
            vis[j] = false;

        res += augment(i);
    }

    return res;
}

int main() {
    freopen("isolated.in", "r", stdin);
    freopen("isolated.out", "w", stdout);
    ios::sync_with_stdio(false);

    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;
        closure[x][y] = true;
    }

    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                closure[i][j] |= (closure[i][k] && closure[k][j]);
    
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (closure[i][j])
                link(i, j);
    
    for (int i = 1; i <= n; ++i)
        exist[i] = true;

    ans = n - hungary();

    for (int i = 1; i <= n; ++i) {
        int tot = 0;

        for (int j = 1; j <= n; ++j) {
            exist[j] = (j != i && !closure[i][j] && !closure[j][i]);
            tot += exist[j];
        }

        int tmp = tot - hungary();
        valid[i] = (ans - tmp == 1);
    }

    for (int i = 1, tot = 0; i <= n; ++i) {
        if (!valid[i] || col[i])
            continue;

        ++tot;
        sol[i] = true;
        col[i] = tot;

        for (int j = 1; j <= n; ++j)
            if (closure[i][j] || closure[j][i])
                col[j] = tot;
    }

    cout << ans << endl;
    
    for (int i = 1; i <= n; ++i)
        cout << (sol[i] ? 1 : 0);
    
    cout << endl;

    for (int i = 1; i <= n; ++i)
        cout << (valid[i] ? 1 : 0);
}
