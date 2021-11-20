#include <iostream>
#include <cstdlib>

using namespace std;

constexpr int maxn = 20 + 10;
constexpr int maxm = 100 + 10;

int n, m;
char s[maxm][maxn];
int cnt[maxm], now[maxn], ans[maxn], ansc;

void check() {
    bool vaild = true;

    for (int i = 1; i <= m; ++i) {
        int sum = 0;

        for (int j = 1; j <= n; ++j)
            if (s[i][j] == '1')
                sum += now[j];

        if (sum != cnt[i]) {
            vaild = false;
            break;
        }
    }

    if (vaild) {
        ++ansc;

        if (ansc > 1) {
            cout << "NOT UNIQUE" << endl;
            exit(0);
        }

        for (int i = 1; i <= n; ++i)
            ans[i] = now[i];
    }
}

void dfs(int dep) {
    if (dep == n + 1) {
        check();
        return;
    }

    dfs(dep + 1);
    now[dep] = 1;
    dfs(dep + 1);
    now[dep] = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= m; ++i)
        cin >> (s[i] + 1) >> cnt[i];

    dfs(1);

    // if (ansc == 0) {
    //     cout << "IMPOSSIBLE" << endl;
    //     return 0;
    // }

    for (int i = 1; i <= n; ++i)
        cout << ans[i];

    cout << endl;
    return 0;
}