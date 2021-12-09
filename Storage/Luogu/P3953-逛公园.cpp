#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();

    for (; c < '0' || '9' < c; c = getchar())
        if (c == '-')
            s = -1;
    
    for (; '0' <= c && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + c - '0';
    
    return x * s;
}

template <typename T> void write(T x, char sep = '\n') {
    if (x == 0) {
        putchar('0');
        putchar(sep);
        return;
    }

    static int st[21];
    int top = 0;

    if (x < 0) {
        x = -x;
        putchar('-');
    }

    while (x) {
        st[++top] = x % 10;
        x /= 10;
    }

    while (top)
        putchar(st[top--] + '0');
    
    putchar(sep);
}

constexpr int maxn = 1e5 + 10;
constexpr int maxk = 50 + 10;
constexpr int oo = 0x3f3f3f3f;

int t, n, m, k, p;
vector<pair<int, int>> graph[maxn], rgraph[maxn];
int dis[maxn], f[maxn][maxk];
bool vis[maxn], vis2[maxn][maxk], invalid;
int ans;

void link(vector<pair<int, int>> graph[], int x, int y, int l) {
    graph[x].push_back({y, l});
}

void dijkstra(int start) {
    priority_queue<pair<int, int>> q;
    fill(dis + 1, dis + 1 + n, oo);
    fill(vis + 1, vis + 1 + n, false);
    dis[start] = 1;
    q.push({0, start});

    while (!q.empty()) {
        int x = q.top().second;
        q.pop();

        if (vis[x])
            continue;
        
        vis[x] = true;

        for (auto [y, l] : graph[x]) {
            if (dis[y] <= dis[x] + l)
                continue;
            
            dis[y] = dis[x] + l;
            q.push({-dis[y], y});
        }
    }
}

int dfs(int x, int i) {
    if (vis2[x][i]) {
        invalid = true;
        return 0;
    }

    if (f[x][i] != -1)
        return f[x][i];

    vis2[x][i] = true;
    f[x][i] = 0;

    for (auto [y, l] : rgraph[x]) {
        int j = (dis[x] + i) - (dis[y] + l);

        if (j < 0 || j > k)
            continue;

        f[x][i] = (f[x][i] + dfs(y, j)) % p;

        if (invalid) {
            vis2[x][i] = false;
            return 0;
        }
    }

    vis2[x][i] = false;
    return f[x][i];
}

void solve() {
    n = read(), m = read(), k = read(), p = read();

    for (int i = 1; i <= n; ++i) {
        graph[i].clear();
        rgraph[i].clear();
    }
    
    for (int i = 1; i <= m; ++i) {
        int x = read(), y = read(), l = read();
        link(graph, x, y, l);
        link(rgraph, y, x, l);
    }

    dijkstra(1);

    invalid = false;
    ans = 0;
    
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= k; ++j)
            f[i][j] = -1;
    
    f[1][0] = 1;
    
    for (int i = 0; i <= k; ++i) {
        ans = (ans + dfs(n, i)) % p;
        
        if (invalid) {
            write(-1);
            return;
        }
    }
    
    write(ans);
}

int main() {
    t = read();

    while (t--)
        solve();

    return 0;
}