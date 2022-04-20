#include <iostream>
#include <queue>
#include <tuple>
#include <bitset>
#include <algorithm>
using namespace std;

constexpr int MAX_N = 200 + 10;
// 最大流
struct Network {
    struct Edge {
        int next;
        int to, cap;
        bool del;
    };

    Edge network[MAX_N * MAX_N * 10];
    int head[MAX_N], tot;
    int source, sink;
    int dis[MAX_N], cur[MAX_N];

    void init(int n) {
        tot = 1;
        source = 0;
        sink = n + 1;
    }

    int link(int x, int y, int c) {
        network[++tot] = { head[x], y, c, false };
        head[x] = tot;
        network[++tot] = { head[y], x, 0, false };
        head[y] = tot;
        return tot - 1;
    }

    bool bfs() {
        for (int i = source; i <= sink; ++i)
            dis[i] = 0;

        queue<int> q;
        dis[source] = 1;
        q.push(source);

        while (!q.empty()) {
            int x = q.front();
            q.pop();
            cur[x] = head[x];

            for (int i = head[x], y; y = network[i].to, i; i = network[i].next) {
                if (network[i].del || network[i].cap <= 0 || dis[y])
                    continue;

                dis[y] = dis[x] + 1;
                q.push(y);
            }
        }

        return dis[sink];
    }

    int dfs(int x, int in) {
        if (x == sink)
            return in;

        int res = 0;

        for (int & i = cur[x], y; y = network[i].to, i; i = network[i].next) {
            if (network[i].del || network[i].cap <= 0 || dis[y] != dis[x] + 1)
                continue;

            int f = dfs(y, min(network[i].cap, in - res));

            if (f > 0) {
                network[i].cap -= f;
                network[i ^ 1].cap += f;
                res += f;

                if (res == in)
                    break;
            }
        }

        if (in != res)
            dis[x] = 0;

        return res;
    }

    int maxflow() {
        int flow = 0;
        // cout << "#######\n";
        while (bfs())
            flow += dfs(source, 0x3f3f3f3f);

        return flow;
    }
};

int n, m, k;
int c1, c2, deg[MAX_N];
Network net;
int id[MAX_N][MAX_N];
tuple<int, int, int> edges[MAX_N * MAX_N];
int ans;

struct BipartiteGraph {
    vector<int> graph[MAX_N];
    int mat[MAX_N];
    bool vis[MAX_N], ok[MAX_N];

    void link(int x, int y) {
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    // 删除边
    void erase(int x, int y) {
        auto it = find(graph[x].begin(), graph[x].end(), y);

        if (it != graph[x].end())
            graph[x].erase(it);
    }

    bool augment(int x) {
        for (int y : graph[x]) {
            if (vis[y])
                continue;
            
            vis[y] = true;
            
            if (ok[y] && (!mat[y] || augment(mat[y]))) {
                mat[y] = x;
                mat[x] = y;
                return true;
            }
        }

        return false;
    }

    void match(int l, int r, int deg) {
        for (int i = l; i <= r; ++i) {
            if ((int) graph[i].size() != deg)
                continue;
            
            for (int j = 1; j <= n; ++j)
                vis[j] = false;
            
            ok[i] = augment(i);
        }

        for (int i = l; i <= r; ++i) {
            if ((int) graph[i].size() >= deg)
                continue;
            
            for (int j = 1; j <= n; ++j)
                vis[j] = false;
            
            ok[i] = augment(i);
        }
    }

    void match(int deg) {
        for (int i = 1; i <= n; ++i)
            ok[i] = true;
        
        for (int i = 1; i <= n; ++i)
            mat[i] = 0;
        
        match(1, c1, deg);

        for (int i = 1; i <= n; ++i)
            mat[i] = 0;
        
        match(c1 + 1, n, deg);

        for (int i = n; i >= 1; --i) {
            if (!mat[i])
                continue;
            // 染色后删除这条边
            erase(i, mat[i]);
            
            if (i < mat[i])
                cout << id[i][mat[i]] << " " << deg << endl;
        }
    }
};

BipartiteGraph bigraph;

int main() {
    std::freopen("decorate.in", "r", stdin);
    std::freopen("decorate.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    c1 = n / 2;
    c2 = n - c1;
    net.init(n);

    for (int i = 1; i <= c1; ++i)
        net.link(net.source, i, k);

    for (int i = 1; i <= c2; ++i)
        net.link(i + c1, net.sink, k);

    for (int i = 1; i <= m; ++i) {
        auto & [x, y, t] = edges[i];
        cin >> x >> y;
        id[x][y] = i;
        t = net.link(x, y, 1);
    }

    ans = net.maxflow();

    for (int i = 1; i <= m; ++i) {
        auto [x, y, t] = edges[i];

        if (net.network[t].cap == 0)
            bigraph.link(x, y);
    }

    cout << ans << endl;

    for (int i = k; i >= 1; --i)
        bigraph.match(i);
    
    return 0;
}
