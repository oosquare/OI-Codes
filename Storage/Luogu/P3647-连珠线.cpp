#include <iostream>
#include <vector>
#include <set>
using namespace std;

constexpr int MAXN = 200000 + 10;
constexpr int INFINITY = 0x7fffffff;

int n;
vector<pair<int, int>> tree[MAXN];
long long f[MAXN][6];

/**
 * f[x][0]: x is initial
 * f[x][1]: x -> fa
 * f[x][2]: x -> y
 * f[x][3]: y -> x -> fa
 * f[x][4]: y1 -> x -> y2
 * f[x][5]: fa -> x -> y
 */

void link(int x, int y, int l) {
    tree[x].push_back({y, l});
    tree[y].push_back({x, l});
}

void dfs(int x, int fa) {
    if (tree[x].size() == 1 && fa != 0) {
        f[x][2] = f[x][3] = f[x][4] = f[x][5] = -INFINITY;
        return;
    }

    long long sum = 0, delta[4] = {-INFINITY, -INFINITY, -INFINITY, -INFINITY};
    multiset<long long> val;
    val.insert(-INFINITY);

    for (auto [y, l] : tree[x]) {
        if (y == fa)
            continue;

        dfs(y, x);

        long long cont = max(f[y][1], f[y][3] + l);
        sum += cont;

        for (int i = 0; i < 6; ++i)
            f[x][i] += cont;

        delta[0] = max(delta[0], max(max(max(f[y][0], f[y][2]), f[y][4]), f[y][5] + l) - cont);
        delta[1] = max(delta[1], f[y][1] + l - cont);
        delta[3] = max(delta[3], max(max(f[y][0], f[y][2]), f[y][4]) + l - cont);
        val.insert(f[y][1] + l - cont);
    }

    for (auto [y, l] : tree[x]) {
        if (y == fa)
            continue;

        int cont = max(f[y][1], f[y][3] + l);
        val.erase(val.find(f[y][1] + l - cont));
        delta[2] = max(delta[2], *val.rbegin() + max(max(f[y][0], f[y][2]), f[y][4]) + l - cont);
        val.insert(f[y][1] + l - cont);
    }

    f[x][2] += delta[0];
    f[x][3] += delta[1];
    f[x][4] += delta[2];
    f[x][5] += delta[3];

    for (int i = 0; i < 6; ++i)
        if (f[x][i] < 0)
            f[x][i] = -INFINITY;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }

    for (int i = 1; i < n; ++i) {
        int x, y, l;
        cin >> x >> y >> l;
        link(x, y, l);
    }

    dfs(1, 0);
    cout << max(max(f[1][0], f[1][2]), f[1][4]) << endl;
    return 0;
}