#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
#include <unordered_set>
using namespace std;

using ll = long long;

constexpr int maxn = 2e5 + 10;
constexpr ll oo = 0x3f3f3f3f3f3f3f3f;

int n, w[maxn];
vector<int> tree[maxn];
ll f[maxn][3];
unordered_set<int> which[maxn];
unordered_set<int> ans;
bool vis[maxn][3];

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void dfs(int x, int fa) {
    ll delta = oo;

    for (int y : tree[x]) {
        if (y == fa)
            continue;

        dfs(y, x);

        f[x][0] += min(f[y][1], f[y][2]);

        if (delta > f[y][0] - min(f[y][1], f[y][2])) {
            delta = f[y][0] - min(f[y][1], f[y][2]);
            which[x].clear();
            which[x].insert(y);
        } else if (delta == f[y][0] - min(f[y][1], f[y][2])) {
            which[x].insert(y);
        }

        f[x][1] += min(f[y][1], f[y][2]);
    }

    if (!which[x].empty())
        f[x][0] += delta;
    else
        f[x][1] = oo;

    f[x][2] = f[x][0] + w[x];
}

void add(int x, int fa, int now) {
    if (vis[x][now])
        return;

    vis[x][now] = true;

    if (now == 1) {
        for (int y : tree[x]) {
            if (y == fa)
                continue;

            if (f[y][1] < f[y][2]) {
                add(y, x, 1);
            } else if (f[y][1] > f[y][2]) {
                add(y, x, 2);
            } else {
                add(y, x, 1);
                add(y, x, 2);
            }
        }
    } else {
        if (now == 2)
            ans.insert(x);

        if (!which[x].empty())
            for (int y : which[x])
                add(y, x, 0);

        for (int y : tree[x]) {
            if (y == fa || (which[x].size() == 1 && which[x].find(y) != which[x].end()))
                continue;

            if (f[y][1] < f[y][2]) {
                add(y, x, 1);
            } else if (f[y][1] > f[y][2]) {
                add(y, x, 2);
            } else {
                add(y, x, 1);
                add(y, x, 2);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> w[i];

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
    }

    dfs(1, 0);

    if (f[1][1] < f[1][2]) {
        cout << f[1][1] << " ";
        add(1, 0, 1);
    } else if (f[1][1] > f[1][2]) {
        cout << f[1][2] << " ";
        add(1, 0, 2);
    } else {
        cout << f[1][1] << " ";
        add(1, 0, 1);
        add(1, 0, 2);
    }

    cout << ans.size() << endl;
    
    vector<int> tmp;
    
    for (int v : ans)
        tmp.push_back(v);

    sort(tmp.begin(), tmp.end());

    for (int v : tmp)
        cout << v << " ";


    cout << endl;
    return 0;
}