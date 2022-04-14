#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

constexpr int MAX_N = 100000 + 10;
constexpr int MAX_D = 50 + 2;

int n, m, d;
bool cont[MAX_N][MAX_D];
std::pair<int, int> edges[MAX_N];
char buf[MAX_D];

std::vector<int> graph[MAX_N * MAX_D], ngraph[MAX_N * MAX_D];
std::stack<int> st, tmp;
int vis[MAX_N];
int timer, dfn[MAX_N * MAX_D], low[MAX_N * MAX_D];
int scc, idx[MAX_N * MAX_D], weight[MAX_N * MAX_D];

int deg[MAX_N * MAX_D];
int dis[MAX_N * MAX_D];
int c[MAX_N * MAX_D];
int ans;

inline int id(int x, int l) { return (l - 1) * n + x; }

inline void link(std::vector<int> graph[], int x, int y) {
    graph[x].push_back(y);
    ++deg[y];
}

void tarjan(int x) {
    dfn[x] = low[x] = ++timer;
    st.push(x);

    for (int y : graph[x]) {
        if (!dfn[y]) {
            tarjan(y);
            low[x] = std::min(low[x], low[y]);
        } else if (!idx[y]) {
            low[x] = std::min(low[x], dfn[y]);
        }
    }

    if (low[x] == dfn[x]) {
        ++scc;
        idx[x] = scc;

        if (c[x] == 1) {
            ++vis[(x - 1) % n + 1];

            if (vis[(x - 1) % n + 1] == 1) {
                ++weight[scc];
                tmp.push((x - 1) % n + 1);
            }
        }

        while (st.top() != x) {
            int y = st.top();
            idx[y] = scc;

            if (c[y] == 1) {
                ++vis[(y - 1) % n + 1];

                if (vis[(y - 1) % n + 1] == 1) {
                    ++weight[scc];
                    tmp.push((y - 1) % n + 1);
                }
            }

            st.pop();
        }

        st.pop();

        while (!tmp.empty()) {
            vis[tmp.top()] = 0;
            tmp.pop();
        }
    }
}

void build() {
    std::vector<std::pair<int, int>> e;

    for (int x = 1; x <= n * d; ++x) {
        for (int y : graph[x]) {
            if (idx[x] == idx[y])
                continue;

            e.emplace_back(idx[x], idx[y]);
        }
    }

    std::sort(e.begin(), e.end());
    auto it = std::unique(e.begin(), e.end());
    e.erase(it, e.end());

    for (int i = 1; i <= scc; ++i)
        deg[i] = 0;

    for (auto [x, y] : e)
        link(ngraph, x, y);
}

void calc(std::vector<int> graph[]) {
    std::queue<int> q;

    for (int i = 1; i <= scc; ++i)
        dis[i] = -0x3f3f3f3f;

    dis[idx[1]] = weight[idx[1]];

    for (int i = 1; i <= scc; ++i)
        if (!deg[i])
            q.push(i);

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        ans = std::max(ans, dis[x]);

        for (int y : graph[x]) {
            dis[y] = std::max(dis[y], dis[x] + weight[y]);
            --deg[y];

            if (!deg[y])
                q.push(y);
        }
    }

    std::cout << ans << std::endl;
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("chase.in", "r", stdin);
    std::freopen("chase.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);

    std::cin >> n >> m >> d;

    for (int i = 1; i <= m; ++i) {
        auto &[x, y] = edges[i];
        std::cin >> x >> y;
    }

    for (int i = 1; i <= n; ++i) {
        std::cin >> buf;

        for (int j = 0; j < d; ++j)
            cont[i][j + 1] = buf[j] - '0';
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= d; ++j)
            c[id(i, j)] = cont[i][j];

    for (int i = 1; i <= m; ++i) {
        auto [x, y] = edges[i];

        for (int j = 1; j <= d; ++j)
            link(graph, id(x, j), id(y, (j == d ? 1 : j + 1)));
    }

    for (int i = 1; i <= n * d; ++i)
        if (!dfn[i])
            tarjan(i);

    build();
    calc(ngraph);

    return 0;
}
