/*#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
#include <queue>
using namespace std;

using ll = long long;
using PairType = pair<ll, int>;

constexpr int maxn = 1e5 + 10;
constexpr ll oo = 0x3f3f3f3f3f3f3f3f;

int n, m, cnt;
vector<PairType> graph[maxn];
ll dis[maxn], dis2[maxn], ans[maxn], anss;
int id[maxn];
PairType pre[maxn];
int vis[maxn], timer;
int color[maxn];

void link(int x, int y, int z) {
    graph[x].push_back({y, z});
    graph[y].push_back({x, z});
}

void apply(int x, int f, ll s) {
    auto [l, y] = pre[x];

    if (y) {
        dis[y] = s + l;

        if (pre[y].second)
            ans[y] = 0;

        id[y] = f;
        apply(y, f, s + l);
        pre[y] = {oo, 0};
    }
}

void dijkstra(int start) {
    ++timer;
    priority_queue<PairType, vector<PairType>, greater<PairType>> q;
    q.push({0, start});
    dis2[start] = 0;
    pre[start] = {oo, 0};

    while (!q.empty()) {
        auto [len, x] = q.top();
        q.pop();

        if (vis[x] == timer)
            continue;

        vis[x] = timer;

        for (auto [y, l] : graph[x]) {
            if (color[y] == 0 && id[y] != 0) {
                if (dis[start] > dis[y] + len + l) {
                    dis[start] = dis[y] + len + l;
                    ans[start] = len + l;
                    id[start] = y;
                    pre[y] = {l, x};
                } else if (dis[start] == dis[y] + len + l && ans[start] > len + l) {
                    ans[start] = len + l;
                    id[start] = y;
                    pre[y] = {l, x};
                }
            } else if (color[y] == 1) {
                if (dis[start] > len + l) {
                    dis[start] = len + l;
                    ans[start] = len + l;
                    id[start] = y;
                    pre[y] = {l, x};
                } else if (dis[start] == len + l && ans[start] > len + l) {
                    ans[start] = len + l;
                    id[start] = y;
                    pre[y] = {l, x};
                }
            } else {
                if (dis2[y] > dis2[x] + l) {
                    dis2[y] = dis2[x] + l;
                    pre[y] = {l, x};
                    q.push({dis2[y], y});
                }
            }
        }
    }

    // if (start != 5)
    apply(id[start], id[start], 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cin >> color[i];
        cnt += color[i];
    }

    if (cnt == 0) {
        cout << "impossible" << endl;
        return 0;
    }

    for (int i = 1; i <= m; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        link(x, y, z);
    }

    fill(dis + 1, dis + 1 + n, oo);
    fill(dis2 + 1, dis2 + 1 + n, oo);
    fill(ans + 1, ans + 1 + n, oo);

    for (int i = 1; i <= n; ++i)
        if (color[i] == 0 && id[i] == 0)
            dijkstra(i);
    // dijkstra(1);

    for (int i = 1; i <= n; ++i)
        cout << i << " " << dis[i] << " " << ans[i] << " " << id[i] << endl;

    for (int i = 1; i <= n; ++i)
        if (color[i] == 0)
            anss += ans[i];

    cout << anss << endl;
    return 0;
}*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int maxn = 1e6 + 5;
constexpr ll oo = 0x3f3f3f3f3f3f3f3f;

int n, m;
vector<pair<int, ll>> graph[maxn];

vector<int> black, white;
bool vis[maxn];
ll dis[maxn], lasdis[maxn];

void link(int x, int y, int z) {
    graph[x].push_back({y, z});
    graph[y].push_back({x, z});
}

void dijkstra() {
    fill(dis + 1, dis + 1 + n, oo);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    
    for (auto x : black)
        q.push(make_pair(dis[x] = 0, x));

    while (!q.empty()) {
        int x= q.top().second;
        q.pop();
        if (vis[x])
            continue;
        vis[x] = true;
        for (auto [y, l] : graph[x]) {
            if (dis[y] > dis[x] + l) {
                lasdis[y] = dis[x];
                q.push(make_pair(dis[y] = dis[x] + l, y));
            } else if (dis[y] == dis[x] + l)
                lasdis[y] = max(lasdis[y], dis[x]);
        }
    }
    ll ans = 0;
    
    for (auto u : white) {
        if (dis[u] < 1e18 / 2)
            ans += dis[u] - lasdis[u];
        else {
            cout << "impossible" << endl;
            return;
        }
    }

    cout << ans << endl;
}

int main() {
    freopen("minimum.in","r",stdin);
    freopen("minimum.out","w",stdout);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;

        if (x)
            black.push_back(i);
        else white.push_back(i);
    }

    for (int i = 1; i <= m; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        link(x, y, z);
        link(y, x, z);
    }
    
    dijkstra();
    return 0;
}
