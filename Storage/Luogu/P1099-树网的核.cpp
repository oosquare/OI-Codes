#include <bits/stdc++.h>
// #define DEBUG
using namespace std;

constexpr int maxn = 300 + 10;

struct Edge {
    int to, length;
};

int n, s, center[2], cnt, l, r, mid, ans;
vector<Edge> tree[maxn];
unordered_set<int> dNodes;
int f[maxn][2], d, dId, from[maxn][2], dis[2][maxn];

void link(int x, int y, int l) {
    tree[x].push_back({y, l});
    tree[y].push_back({x, l});
}

void find(int x, int fa) {
    for (auto [y, l] : tree[x]) {
        if (y == fa)
            continue;
        find(y, x);
        if (f[x][0] <= f[y][0] + l) {
            f[x][1] = exchange(f[x][0], f[y][0] + l);
            from[x][1] = exchange(from[x][0], y);
        } else if (f[x][1] <= f[y][0] + l) {
            f[x][1] = f[y][0] + l;
            from[x][1] = y;
        }
    }
    if (d < f[x][0] + f[x][1]) {
        d = f[x][0] + f[x][1];
        dId = x;
    }
}

void store() {
    dNodes.insert(dId);
    int x = from[dId][0];
    if (x != 0)
        dNodes.insert(x);
    while (from[x][0] != 0) {
        x = from[x][0];
        dNodes.insert(x);
    }
    x = from[dId][1];
    if (x != 0)
        dNodes.insert(x);
    while (from[x][0] != 0) {
        x = from[x][0];
        dNodes.insert(x);
    }
    
    int sum = 0;
    bool found = false;
    int fa = 0;
    for (int i = 1; i <= n; ++i) {
        if (tree[i].size() == 1 && dNodes.find(i) != dNodes.end()) {
            x = i;
            break;
        }
    }
    double d2 = 1.0 * d / 2;
    while (found == false) {
        for (auto [y, l] : tree[x]) {
            if (dNodes.find(y) == dNodes.end() || y == fa)
                continue;
            if (sum + l == d2) {
                center[0] = y;
                cnt = 1;
                found = true;
            } else if (sum < d2 && d2 < sum + l) {
                center[0] = x;
                center[1] = y;
                cnt = 2;
                found = true;
            } else {
                fa = exchange(x, y);
                sum += l;
            }
            break;
        }
    }
}

void dfs(int x, int fa, int id) {
    for (auto [y, l] : tree[x]) {
        if (y == fa)
            continue;
        dfs(y, x, id);
        dis[id][x] = max(dis[id][x], dis[id][y] + l);
    }
}

bool extend(int x, int fa, int id, int &s, int ecc) {
    int cnt = 0;
    Edge ext[3];
    memset(ext, 0, sizeof(ext));
    for (auto [y, l] : tree[x]) {
        if (y == fa)
            continue;
#ifdef DEBUG
        cout << "y = " << y << " l = " << l << " l + dis[id][y] = " << l + dis[id][y] << endl;
#endif
        if (l + dis[id][y] > ecc) {
            ++cnt;
            if (cnt > (x == center[id] ? 2 : 1))
                return false;
        }
        if (dNodes.find(y) != dNodes.end() && l + dis[id][y] > ecc) {
            if (ext[1].to == 0) {
                ext[1] = {y, l};
            } else {
                ext[2] = {y, l};
            }
        }
    }
#ifdef DEBUG
    cout << "x = " << x << " id = " << id << " cnt = " << cnt << endl;
#endif
    if (cnt == 0)
        return true;
    bool res = true;
    for (int i = 1; i <= (x == center[id] ? 2 : 1); ++i) {
        s -= ext[i].length;
        if (s < 0)
            return false;
        res = res && extend(ext[i].to, x, id, s, ecc);
        if (res == false)
            return false;
    }
    return true;
}

bool check(int ecc) {
    int tmp = s;
    if (cnt == 1) {
        return extend(center[0], 0, 1, tmp, ecc);
    } else {
        if (extend(center[0], 0, 0, tmp, ecc))
            return true;
        tmp = s;
#ifdef DEBUG
        cout << endl;
#endif
        if (extend(center[1], 0, 1, tmp, ecc))
            return true;
        return false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> s;
    for (int i = 1; i < n; ++i) {
        int x, y, l;
        cin >> x >> y >> l;
        link(x, y, l);
    }
    find(1, 0);
    store();
    if (cnt == 1) {
        dfs(center[0], 0, 0);
    } else {
        dfs(center[0], 0, 0);
        dfs(center[1], 0, 1);
    }
    l = 0;
    r = d;
    while (l <= r) {
        mid = (l + r) / 2;
        bool res;
        if ((res = check(mid))) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
#ifdef DEBUG
        cout << "mid = " << mid << " check(mid) = " << res << endl;
        cout << endl;
#endif
    }
    cout << ans << endl;
#ifdef DEBUG
    cout << "d = " << d << " cnt = " << cnt << endl;
    cout << "center[0] = " << center[0] << " center[1] = " << center[1] << endl;
    for (int i = 1; i <= n; ++i) {
        if (tree[i].size() == 1 && dNodes.find(i) != dNodes.end()) {
            cout << i << " ";
        }
    }
    cout << endl;
#endif
    return 0;
}