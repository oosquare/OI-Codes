#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <algorithm>

constexpr int MAX_M = 200000 + 10;

struct String {
    static constexpr int MOD[2] = { 1000000007, 998244353 };
    static constexpr int BASE[2] = { 257, 91 };

    std::string str;
    std::vector<int> power[2], sum[2];

    void set(std::string s) {
        str = " " + std::move(s);
        power[0].resize(str.size());
        power[1].resize(str.size());
        sum[0].resize(str.size());
        sum[1].resize(str.size());

        power[0][0] = power[1][0] = 1;

        for (int i = 1; i <= size(); ++i) {
            power[0][i] = 1ll * power[0][i - 1] * BASE[0] % MOD[0];
            power[1][i] = 1ll * power[1][i - 1] * BASE[1] % MOD[1];
            sum[0][i] = (1ll * sum[0][i - 1] * BASE[0] + str[i] - 'a' + 1) % MOD[0];
            sum[1][i] = (1ll * sum[1][i - 1] * BASE[1] + str[i] - 'a' + 1) % MOD[1];
        }
    }

    int hash(int r, int len, int id) {
        return (sum[id][r] - 1ll * sum[id][r - len] * power[id][len] % MOD[id] + MOD[id]) % MOD[id];
    }

    std::pair<int, int> hash(int r, int len) { return { hash(r, len, 0), hash(r, len, 1) }; }

    int size() { return str.size() - 1; }

    char &operator[](int x) { return str[x]; }
};

struct Graph {
    int tot;
    int in[MAX_M];
    std::vector<int> graph[MAX_M];
    int dis[MAX_M], prev[MAX_M];

    void init(int tot) { this->tot = tot; }

    void clear(int tot) {
        for (int i = 1; i <= tot; ++i) {
            graph[i].clear();
            in[i] = 0;
        }
    }

    void link(int x, int y) {
        graph[x].push_back(y);
        ++in[y];
    }

    template <typename Func>
    std::pair<int, int> topo(bool sol_type, Func less) {
        std::queue<int> q;
        int cnt = 0, dest = 0, res = 0;

        for (int i = 1; i <= tot; ++i) {
            if (!in[i])
                q.push(i);

            prev[i] = 0;
            dis[i] = 0;
        }

        while (!q.empty()) {
            int x = q.front();
            q.pop();
            ++cnt;

            if (sol_type && !dis[x])
                prev[x] = x;

            if (dis[x] + 1 > res) {
                res = dis[x] + 1;
                dest = x;
            } else if (sol_type && dis[x] + 1 == res) {
                if (less(x, dest))
                    dest = x;
            }

            for (int y : graph[x]) {
                if (dis[y] < dis[x] + 1) {
                    dis[y] = dis[x] + 1;

                    if (sol_type)
                        prev[y] = x;
                } else if (sol_type && dis[y] == dis[x] + 1) {
                    if (less(x, prev[y]))
                        prev[y] = x;
                }

                --in[y];

                if (!in[y])
                    q.push(y);
            }
        }

        if (cnt == tot)
            return { res, dest };
        else
            return { -1, dest };
    }
};

struct Hash {
    std::hash<int> h;

    unsigned long long operator()(const std::pair<int, int> &p) const {
        return h(p.first) * 19260817u + h(p.second);
    }
};

int t, m;
String s[MAX_M];
int slen;
Graph g;
char buf[MAX_M];
int len;
int tot, k;
std::unordered_map<std::pair<int, int>, int, Hash> mp;
int id[MAX_M], ed[MAX_M];

bool comp(int lhs, int rhs) {
    int l = 1, r = k - 1, pos = 0;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (s[id[lhs]].hash(ed[lhs], mid) == s[id[rhs]].hash(ed[rhs], mid)) {
            pos = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    if (r == k - 1)
        return true;
    else
        return (s[id[lhs]][ed[lhs] - pos] < s[id[rhs]][ed[rhs] - pos]);
}

void get_solution(int dest) {
    len = 0;

    if (dest == 0 || g.prev[dest] == 0) {
        len = k - 1;

        for (int i = 1; i <= len; ++i)
            buf[i] = 'a';

        return;
    }

    int x = dest;

    for (; g.prev[x] != x; x = g.prev[x]) {
        buf[++len] = s[id[x]][ed[x]];
    }

    for (int i = 1; i <= k - 1; ++i)
        buf[++len] = s[id[x]][ed[x] - i + 1];
}

int get_id(std::pair<int, int> x, int i, int e) {
    if (mp.count(x) == 0) {
        mp[x] = ++tot;
        id[tot] = i;
        ed[tot] = e;
    }

    return mp[x];
}

int check(bool sol_type, int mid) {
    k = mid;
    tot = 0;
    mp.clear();

    for (int i = 1; i <= m; ++i) {
        for (int j = k - 1; j < s[i].size(); ++j) {
            int x = get_id(s[i].hash(j, k - 1), i, j);
            int y = get_id(s[i].hash(j + 1, k - 1), i, j + 1);
            g.link(x, y);
        }
    }
    g.init(tot);

    auto [res, dest] = g.topo(sol_type, comp);

    if (res > 0)
        res += k - 2;

    if (tot == 0)
        res = k - 1;

    if (sol_type)
        get_solution(dest);

    g.clear(tot);
    return (res >= 0);
}

void solve() {
    std::cin >> m;
    slen = 1;

    for (int i = 1; i <= m; ++i) {
        std::string str;
        std::cin >> str;
        slen += str.size();
        std::reverse(str.begin(), str.end());
        s[i].set(std::move(str));
    }

    int l = 0, r = slen, ans = 0;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (check(false, mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    check(true, ans);

    std::cout << ans << std::endl;

    for (int i = 1; i <= len; ++i)
        std::cout.put(buf[i]);

    std::cout << std::endl;
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("string.in", "r", stdin);
    std::freopen("string.out", "w", stdout);
#else    
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);

    std::cin >> t;

    for (int i = 1; i <= t; ++i)
        solve();

    return 0;
}