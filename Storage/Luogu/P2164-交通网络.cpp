#include <iostream>
#include <iomanip>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();

    for (; c < '0' || c > '9'; c = getchar())
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

    static int st[50];
    int top = 0;

    if (x < 0) {
        putchar('-');
        x = -x;
    }

    while (x) {
        st[++top] = x % 10;
        x /= 10;
    }

    while (top)
        putchar(st[top--] + '0');

    putchar(sep);
}

constexpr int maxn = 300 + 10;

int n, m, from[maxn * maxn], to[maxn * maxn];
vector<pair<int, int>> graph[maxn];
int dis[maxn], vis[maxn];
long double cnt[maxn], c[maxn][maxn], ans[maxn][maxn];

struct Comparer {
    bool operator()(int l, int r) const {
        return dis[l] < dis[r];
    }
};

void link(int x, int y, int id) {
    graph[x].push_back({y, id});
    graph[y].push_back({x, id});
    from[id] = x;
    to[id] = y;
}

void solve(int start) {
    queue<int> q;
    priority_queue<int, vector<int>, Comparer> pq;

    fill(dis + 1, dis + 1 + n, 0x3f3f3f3f);
    fill(cnt + 1, cnt + 1 + n, 0);
    q.push(start);
    dis[start] = 0;
    cnt[start] = 1;

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        bool found = false;

        for (auto [y, id] : graph[x]) {
            if (dis[y] > dis[x] + 1) {
                dis[y] = dis[x] + 1;
                cnt[y] = cnt[x];
                q.push(y);
                found = true;
            } else if (dis[y] == dis[x] + 1) {
                cnt[y] += cnt[x];
                found = true;
            }
        }

        if (!found)
            pq.push(x);
    }

    fill(vis + 1, vis + 1 + n, false);
    vis[start] = true;

    while (!pq.empty()) {
        int y = pq.top();
        pq.pop();

        for (auto [x, id] : graph[y]) {
            if (dis[y] == dis[x] + 1) {
                long double cc = (long double)c[start][y] * cnt[x] / cnt[y];
                ans[x][y] += cc;
                ans[y][x] += cc;
                c[start][x] += cc;

                if (!vis[x]) {
                    vis[x] = true;
                    pq.push(x);
                }
            }
        }
    }
}

int main() {
    n = read(), m = read();

    for (int i = 1; i <= m; ++i) {
        int x = read(), y = read();
        link(x, y, i);
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            c[i][j] = read();

    for (int i = 1; i <= n; ++i)
        solve(i);

    for (int i = 1; i <= m; ++i)
        cout << fixed << setprecision(1) << ans[from[i]][to[i]] + 1e-8 << endl;

    return 0;
}