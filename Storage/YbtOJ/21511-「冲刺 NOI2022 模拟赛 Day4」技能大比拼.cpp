#include <iostream>
#include <queue>

constexpr int MAX_N = 100 + 10;
constexpr int INFINITY = 0x3f3f3f3f;

class Network {
public:
    void init(int n) {
        tot = 1;
        source = 0;
        sink = n + 1;
    }

    int link(int x, int y, int c, int w) {
        net[++tot] = { head[x], y, c, w };
        head[x] = tot;
        net[++tot] = { head[y], x, 0, -w };
        head[y] = tot;
        return tot - 1;
    }

    int getSource() {
        return source;
    }

    int getSink() {
        return sink;
    }

    std::pair<int, int> maxflow() {
        int flow = 0, cost = 0;
        
        while (spfa())
            flow += dfs(source, INFINITY, cost);
        
        return { flow, cost };
    }

    int capacity(int id) {
        return net[id].capacity;
    }
private:
    struct Edge {
        int next, to, capacity, weight;
    };

    Edge net[MAX_N * MAX_N * 20];
    int head[MAX_N * MAX_N], cur[MAX_N * MAX_N], tot;
    int dis[MAX_N * MAX_N];
    bool vis[MAX_N * MAX_N];
    int source, sink;

    bool spfa() {
        std::queue<int> q;

        for (int i = source; i <= sink; ++i) {
            dis[i] = INFINITY;
            vis[i] = false;
        }

        dis[source] = 0;
        q.push(source);

        while (!q.empty()) {
            int x = q.front();
            q.pop();
            vis[x] = false;
            cur[x] = head[x];

            for (int i = head[x], y; y = net[i].to, i; i = net[i].next) {
                if (net[i].capacity <= 0 || dis[y] <= dis[x] + net[i].weight)
                    continue;
                
                dis[y] = dis[x] + net[i].weight;

                if (vis[y])
                    continue;
                
                vis[y] = true;
                q.push(y);
            }
        }

        return dis[sink] != INFINITY;
    }

    int dfs(int x, int in, int & cost) {
        if (x == sink)
            return in;
        
        int res = 0;
        vis[x] = true;

        for (int & i = cur[x], y; y = net[i].to, i; i = net[i].next) {
            if (net[i].capacity <= 0 || vis[y] || dis[y] != dis[x] + net[i].weight)
                continue;
            
            int f = dfs(y, std::min(net[i].capacity, in - res), cost);

            if (f > 0) {
                net[i].capacity -= f;
                net[i ^ 1].capacity += f;
                cost += f * net[i].weight;
                res += f;

                if (res == in)
                    break;
            }
        }

        if (res != in)
            vis[x] = false;

        return res;
    }
};

int n, mat[MAX_N][MAX_N];
int deg[MAX_N];
int id[MAX_N][MAX_N], tot;
std::pair<int, int> nid[MAX_N][MAX_N];
Network net;
int ans;

int main() {
#ifdef ONLINE_JUDGE
    freopen("compete.in", "r", stdin);
    freopen("compete.out", "w", stdout);
#else
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    
    std::cin >> n;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cin >> mat[i][j];
            
            if (mat[i][j] == 1)
                ++deg[j];

            if (i < j && mat[i][j] == 2)
                id[i][j] = ++tot;
        }
    }

    net.init(tot + n);

    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (!id[i][j])
                continue;
            
            auto & [origin, reverse] = nid[i][j];
            origin = net.link(id[i][j], tot + j, 1, 0);
            reverse = net.link(id[i][j], tot + i, 1, 0);
        }
    }

    for (int i = 1; i <= tot; ++i)
        net.link(net.getSource(), i, 1, 0);
    
    for (int i = 1; i <= n; ++i)
        for (int j = deg[i]; j <= n; ++j)
            net.link(tot + i, net.getSink(), 1, j);

    ans = n * (n - 1) * (n - 2) / 6;

    for (int i = 1; i <= n; ++i)
        ans -= deg[i] * (deg[i] - 1) / 2;
    
    ans -= net.maxflow().second;

    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (!id[i][j])
                continue;
            
            auto [origin, reverse] = nid[i][j];

            if (!net.capacity(origin)) {
                mat[i][j] = 1;
                mat[j][i] = 0;
            } else {
                mat[i][j] = 0;
                mat[j][i] = 1;
            }
        }
    }

    std::cout << ans << std::endl;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j)
            std::cout << mat[i][j] << " ";
        
        std::cout << std::endl;
    }
    
    return 0;
}
