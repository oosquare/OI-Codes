#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
using namespace std;

constexpr int MAX_N = 30 + 5;
constexpr int MAX_NODE = MAX_N * MAX_N * MAX_N;

int n, nn, m;
vector<int> graph[MAX_NODE];
int in[MAX_NODE];
int timer, dfn[MAX_NODE], low[MAX_NODE];
int scc, belong[MAX_NODE];
long long weight[MAX_NODE], cnt[MAX_NODE];
int st[MAX_NODE], top;
long long f[MAX_NODE];
long long co[MAX_N][MAX_N];
int idd[MAX_N][MAX_N][MAX_N], uuid;

inline int id(const tuple<int, int, int, int> & t) {
    auto [a, b, c, d] = t;
    if (idd[a][b][c] == 0)
        idd[a][b][c] = ++uuid;
    return idd[a][b][c];
}

tuple<int, int, int, int> stat(const string & s) {
    auto res = make_tuple(0, 0, 0, 0);

    for (char c : s) {
        if (c == 'A')
            ++get<0>(res);
        else if (c == 'B')
            ++get<1>(res);
        else if (c == 'C')
            ++get<2>(res);
        else
            ++get<3>(res);
    }

    return res;
}

long long comb(int n, int m) {
    static bool first = true;

    if (first) {
        first = false;

        for (int i = 0; i < MAX_N; ++i)
            co[i][0] = co[i][i] = 1;

        for (int i = 1; i < MAX_N; ++i)
            for (int j = 1; j < i; ++j)
                co[i][j] = co[i - 1][j] + co[i - 1][j - 1];
    }

    return co[n][m];
}

inline long long calc(const tuple<int, int, int, int> & t) {
    auto [a, b, c, d] = t;
    return comb(a + b, b) * comb(a + b + c, c) * comb(a + b + c + d, d);
}

inline void link(int x, int y) {
    graph[x].push_back(y);
    ++in[y];
}

void tarjan(int x) {
    dfn[x] = low[x] = ++timer;
    st[++top] = x;

    for (int y : graph[x]) {
        if (!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        } else if (!belong[y]) {
            low[x] = min(low[x], dfn[y]);
        }
    }

    if (low[x] == dfn[x]) {
        ++scc;
        belong[x] = scc;
        weight[scc] = cnt[x];
        while (st[top] != x) {
            belong[st[top]] = scc;
            weight[scc] += cnt[st[top]];
            --top;
        }

        --top;
    }
}

void build() {
    vector<pair<int, int>> edges;

    for (int i = 1; i <= nn; ++i) {
        int x = belong[i];

        for (int j : graph[i]) {
            int y = belong[j];

            if (x == y)
                continue;

            edges.push_back({ x, y });
        }
    }

    sort(edges.begin(), edges.end());
    auto it = unique(edges.begin(), edges.end());
    edges.erase(it, edges.end());

    for (int i = 1; i <= scc; ++i) {
        graph[i].clear();
        in[i] = 0;
    }

    for (auto [x, y] : edges)
        link(x, y);
}

long long dp() {
    long long res = 0;
    queue<int> q;

    for (int i = 1; i <= scc; ++i) {
        if (!in[i]) {
            q.push(i);
            f[i] = weight[i];
        }
    }

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        res = max(res, f[x]);

        for (int y : graph[x]) {
            f[y] = max(f[y], f[x] + weight[y]);
            --in[y];

            if (!in[y])
                q.push(y);
        }
    }

    return res;
}

void connect(const tuple<int, int, int, int> & ta, const tuple<int, int, int, int> & tb) {
    auto [a, b, c, d] = ta;
    int da = get<0>(tb) - a, db = get<1>(tb) - b, dc = get<2>(tb) - c, dd = get<3>(tb) - d;

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n - i; ++j) {
            for (int k = 0; k <= n - i - j; ++k) {
                int l = n - i - j - k;

                if (i >= a && j >= b && k >= c && l >= d)
                    link(id({ i, j, k, l }), id({ i + da, j + db, k + dc, l + dd }));
            }
        }
    }
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("character.in", "r", stdin);
    freopen("character.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        string a, b;
        cin >> a >> b;

        if (a == b)
            continue;

        auto ta = stat(a), tb = stat(b);
        connect(ta, tb);
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n - i; ++j) {
            for (int k = 0; k <= n - i - j; ++k) {
                int l = n - i - j - k;
                cnt[id({ i, j, k, l })] = calc({ i, j, k, l });
            }
        }
    }
    
    nn = uuid;
    
    for (int i = 1; i <= nn; ++i)
        if (!dfn[i])
            tarjan(i);

    build();
    cout << dp() << endl;
    return 0;
}
