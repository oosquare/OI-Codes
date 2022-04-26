#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>

constexpr int MAX_N = 100000 + 10;
constexpr int MAX_A = 10000000 + 10;

int t, n;
int a[MAX_N];
int tot, prime[MAX_A];
bool not_prime[MAX_A];
std::unordered_map<int, std::vector<int>> seq;
std::vector<std::pair<int, int>> graph[MAX_N];
int edge_tot;
bool vis[MAX_N];
int dfn[MAX_N], low[MAX_N], timer;
std::stack<int> stk;
int sze[MAX_N];

void link(int x, int y) {
    ++edge_tot;
    graph[x].push_back({ y, edge_tot });
    graph[y].push_back({ x, edge_tot });
}

int count(int sx) {
    std::queue<int> q;
    q.push(sx);
    vis[sx] = true;
    int res = 0;

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        ++res;

        for (auto [y, id] : graph[x]) {
            if (vis[y])
                continue;

            vis[y] = true;
            q.push(y);
        }
    }

    return res;
}

int tarjan(int x, int last, int tot) {
    int ans = 0x3f3f3f3f;
    int res = 0, sum = 1;
    sze[x] = 1;
    dfn[x] = low[x] = ++timer;
    stk.push(x);

    for (auto [y, id] : graph[x]) {
        if (id == last)
            continue;

        if (!dfn[y]) {
            ans = std::min(ans, tarjan(y, id, tot));
            low[x] = std::min(low[x], low[y]);
            sze[x] += sze[y];

            if (dfn[x] <= low[y]) {
                res = std::max(res, sze[y]);
                sum += sze[y];

                while (stk.top() != y)
                    stk.pop();
            }
        } else {
            low[x] = std::min(low[x], dfn[y]);
        }
    }

    res = std::max(res, tot - sum);
    ans = std::min(ans, res);
    return ans;
}

void preprocess(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!not_prime[i])
            prime[++tot] = i;

        for (int j = 1; j <= tot && 1ll * i * prime[j] <= n; ++j) {
            not_prime[i * prime[j]] = true;

            if (i % prime[j] == 0)
                break;
        }
    }
}

void add(int num, int id) {
    std::vector<int> factor;
    int x = num;

    for (int i = 1; 1ll * prime[i] * prime[i] <= x; ++i) {
        if (x % prime[i])
            continue;

        factor.push_back(prime[i]);

        while (x % prime[i] == 0)
            x /= prime[i];
    }

    if (x != 1)
        factor.push_back(x);

    for (int i = 0; i < factor.size(); ++i)
        for (int j = 0; j <= i; ++j)
            if (num % (factor[i] * factor[j]) == 0)
                seq[factor[i] * factor[j]].push_back(id);
}

void solve() {
    std::cin >> n;
    edge_tot = 0;

    for (int i = 1; i <= n; ++i) {
        graph[i].clear();
        dfn[i] = low[i] = 0;
        sze[i] = 0;
        vis[i] = false;
    }

    seq.clear();
    timer = 0;

    while (!stk.empty())
        stk.pop();

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    for (int i = 1; i <= n; ++i)
        add(a[i], i);

    for (auto &[p, nodes] : seq) {
        for (int i = 0; i < nodes.size() - 1; ++i)
            link(nodes[i], nodes[i + 1]);

        if (nodes.size() >= 2)
            link(nodes.back(), nodes.front());
    }

    int ans = 0;
    int msze = 0, msze2 = 0, which = 0;

    for (int i = 1; i <= n; ++i) {
        if (vis[i])
            continue;

        int s = count(i);

        if (s >= msze) {
            msze2 = msze;
            msze = s;
            which = i;
        } else if (s > msze2) {
            msze2 = s;
        }
    }

    ans = std::max(std::min(msze - 1, tarjan(which, 0, msze)), msze2);
    std::cout << ans << std::endl;
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("appoint.in", "r", stdin);
    std::freopen("appoint.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    preprocess(MAX_A - 10);

    std::cin >> t;

    while (t--)
        solve();

    return 0;
}