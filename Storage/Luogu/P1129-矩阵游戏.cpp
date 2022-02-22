#include <iostream>
#include <vector>
using namespace std;

constexpr int MAX_N = 200 + 10;

int t, n;
vector<int> graph[MAX_N];
bool vis[MAX_N];
int match[MAX_N];

void link(int x, int y) {
    graph[x].push_back(y);
}

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

int hungary() {
    int res = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j)
            vis[j] = false;
        
        if (augment(i))
            ++res;
    }

    return res;
}

void solve() {
    cin >> n;
    clear();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int col;
            cin >> col;

            if (col)
                link(i, j);
        }
    }

    cout << (hungary() == n ? "Yes" : "No") << endl;
}

int main() {
    ios::sync_with_stdio(false);
    
    cin >> t;

    while (t--)
        solve();
        
    return 0;
}