#include <iostream>
#include <vector>
using namespace std;

constexpr int MAX_N = 50 + 5;

int t, n;
bool local[MAX_N], home[MAX_N];
vector<int> graph[MAX_N];
int match[MAX_N];
bool vis[MAX_N];

void clear() {
    for (int i = 1; i <= n; ++i) {
        graph[i].clear();
        match[i] = 0;
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

bool hungary() {
    int tot = 0, cnt = 0;

    for (int i = 1; i <= n; ++i) {
        if (local[i] && home[i])
            continue;

        ++tot;

        for (int j = 1; j <= n; ++j)
            vis[j] = false;

        if (augment(i))
            ++cnt;
    }

    return tot == cnt;
}

void solve() {
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> local[i];

    for (int i = 1; i <= n; ++i)
        cin >> home[i];

    clear();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            bool fri;
            cin >> fri;

            if (fri) {
                if (local[j])
                    graph[i].push_back(j);

                if (local[i])
                    graph[j].push_back(i);
            }
        }

        if (local[i] && !home[i])
            graph[i].push_back(i);
    }

    cout << (hungary() ? "^_^" : "T_T") << endl;
}

int main() {
    ios::sync_with_stdio(false);

    cin >> t;

    while (t--)
        solve();

    return 0;
}