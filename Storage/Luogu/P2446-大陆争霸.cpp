#include <iostream>
#include <vector>
#include <utility>
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

constexpr int maxn = 3e3 + 10;
constexpr long long oo = 0x3f3f3f3f3f3f3f3f;

int n, m;
vector<pair<int, int>> graph[maxn];
vector<int> tgraph[maxn];
long long dis[maxn], tim[maxn], in[maxn];
bool vis[maxn], vis2[maxn];

void link(int x, int y, int l) {
    graph[x].push_back({y, l});
}

void link(int x, int y) {
    tgraph[x].push_back(y);
    ++in[y];
}

void dijkstra() {
    priority_queue<pair<long long, int>> q;
    fill(dis + 1, dis + 1 + n, oo);
    dis[1] = 0;
    q.push({0, 1});

    while (!q.empty()) {
        int x = q.top().second;
        q.pop();

        if (vis[x] || in[x])
            continue;

        vis[x] = true;
        dis[x] = max(dis[x], tim[x]);

        for (int y : tgraph[x]) {
            --in[y];
            tim[y] = max(tim[y], dis[x]);

            if (!in[y] && dis[y] != oo)
                q.push({-dis[y], y});
        }

        for (auto [y, l] : graph[x]) {
            if (dis[y] <= dis[x] + l)
                continue;

            dis[y] = dis[x] + l;
            q.push({-dis[y], y});
        }
    }
}

int main() {
    n = read(), m = read();

    for (int i = 1; i <= m; ++i) {
        int x = read(), y = read(), l = read();
        link(x, y, l);
    }

    for (int i = 1; i <= n; ++i) {
        int l = read(), k;

        for (int j = 1; j <= l; ++j) {
            k = read();
            link(k, i);
        }
    }

    dijkstra();
    write(dis[n]);
    return 0;
}