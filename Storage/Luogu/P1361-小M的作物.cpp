#include <iostream>
#include <queue>
using namespace std;

constexpr int MAX_N = 3e3 + 10;
constexpr long long INFINITY = 0x3f3f3f3f;

class Network {
public:
    void init(int n) {
        tot = 1;
        source = 0;
        sink = n + 1;

        for (int i = 0; i <= n + 1; ++i)
            head[i] = 0;
    }

    void link(int x, int y, long long c) {
        net[++tot] = { head[x], y, c };
        head[x] = tot;
        net[++tot] = { head[y], x, 0 };
        head[y] = tot;
    }

    int getSource() {
        return source;
    }

    int getSink() {
        return sink;
    }

    long long maxflow() {
        long long res = 0;

        while (bfs())
            res += dfs(source, INFINITY);
        
        return res;
    }
private:
    struct Edge {
        int next, to;
        long long cap;
    };

    Edge net[MAX_N * MAX_N];
    int head[MAX_N], cur[MAX_N], tot;
    int dis[MAX_N];
    int source, sink;

    bool bfs() {
        for (int i = source; i <= sink; ++i)
            dis[i] = 0;
        
        queue<int> q;
        q.push(source);
        dis[source] = 1;

        while (!q.empty()) {
            int x = q.front();
            q.pop();
            cur[x] = head[x];

            for (int i = head[x], y; y = net[i].to, i; i = net[i].next) {
                if (net[i].cap <= 0 || dis[y])
                    continue;
                
                dis[y] = dis[x] + 1;
                q.push(y);
            }
        }

        return dis[sink] != 0;
    }

    long long dfs(int x, long long in) {
        if (x == sink)
            return in;
        
        long long res = 0;

        for (int & i = cur[x], y; y = net[i].to, i; i = net[i].next) {
            if (net[i].cap <= 0 || dis[y] != dis[x] + 1)
                continue;
            
            long long f = dfs(y, min(net[i].cap, in - res));

            if (f > 0) {
                net[i].cap -= f;
                net[i ^ 1].cap += f;
                res += f;

                if (res == in)
                    break;
            }
        }

        if (res == in)
            dis[x] = 0;
        
        return res;
    }
};

Network net;
int n, m;
long long a[MAX_N], b[MAX_N], ans;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    
    for (int i = 1; i <= n; ++i)
        cin >> b[i];

    cin >> m;

    net.init(n + 2 * m);

    for (int i = 1; i <= n; ++i) {
        ans += a[i] + b[i];
        net.link(net.getSource(), i, a[i]);
        net.link(i, net.getSink(), b[i]);
    }

    for (int i = 1; i <= m; ++i) {
        int k, a, b, x;
        cin >> k >> a >> b;
        ans += a + b;
        net.link(net.getSource(), n + i, a);
        net.link(n + m + i, net.getSink(), b);

        for (int j = 1; j <= k; ++j) {
            cin >> x;
            net.link(n + i, x, INFINITY);
            net.link(x, n + m + i, INFINITY);
        }
    }

    cout << ans - net.maxflow() << endl;
    return 0;
}