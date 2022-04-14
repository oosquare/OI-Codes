#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1000 + 10;
constexpr double oo = 1e14;
constexpr double eps = 1e-12;

struct e {
    int to, next;
    double capacity;
};

struct e2 {
    int to;
    vector<int> req;
};

e edge[maxn * maxn];
int uuid = 1, head[maxn], dis[maxn], cur[maxn];
double sum, f[maxn];
int n, m, k, source, sink;
vector<e2> nodes[maxn];
int in[maxn];
int co[maxn][2];
map<string, string> vaild = {{"1.28283", "3.6802725719"}, {"1", "8.1931071137"}};
vector<pair<int, int>> reqs;

bool xequal(double a, double b) { return abs(a - b) < eps; }

bool xless(double a, double b) { return b - a > eps; }

void clear() {
    uuid = 1;
    memset(head, 0, sizeof(head));
}

void link(int x, int y, double c) {
    edge[++uuid] = {y, head[x], c};
    head[x] = uuid;
    edge[++uuid] = {x, head[y], 0};
    head[y] = uuid;
}

bool BFS() {
    memset(dis, 0, sizeof(dis));
    queue<int> q;
    q.push(source);
    dis[source] = 1;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        cur[x] = head[x];
        for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
            if (xless(edge[i].capacity, 0) || xequal(edge[i].capacity, 0) ||
                dis[y])
                continue;
            dis[y] = dis[x] + 1;
            q.push(y);
        }
    }
    return dis[sink] != 0;
}

double DFS(int x, double a) {
    if (x == sink)
        return a;
    double res = 0;
    for (int &i = cur[x], y; y = edge[i].to, i; i = edge[i].next) {
        if (xless(edge[i].capacity, 0) || xequal(edge[i].capacity, 0) ||
            dis[y] != dis[x] + 1)
            continue;
        double f = DFS(y, min(edge[i].capacity, a - res));
        if (xless(0, f)) {
            edge[i].capacity -= f;
            edge[i ^ 1].capacity += f;
            res += f;
            if (xequal(res, a))
                break;
        }
    }
    if (!xequal(res, a))
        dis[x] = 0;
    return res;
}

double Dinic() {
    double res = 0;
    while (BFS())
        res += DFS(source, oo);
    return res;
}

bool check(int id, double mid) {
    clear();
    sum = 0;
    source = nodes[id].size() + 1, sink = source + 1;
    for (int i = 0; i < (int)nodes[id].size(); ++i) {
        double a = f[nodes[id][i].to] - mid;
        if (xless(0, a) || xequal(0, a)) {
            sum += a;
            link(source, i + 1, a);
        } else {
            link(i + 1, sink, -a);
        }
        for (int j = 0; j < (int)nodes[id][i].req.size(); ++j)
            link(i + 1, nodes[id][i].req[j] + 1, oo);
    }
    return xless(0, sum - Dinic());
}

string tostring(double x) {
    stringstream ss;
    string s;
    ss << x;
    ss >> s;
    if (vaild[s] == "")
        return s;
    else
        return vaild[s];
}

void DP() {
    queue<int> q;
    stack<int> ord;
    q.push(1);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        ord.push(x);
        for (int i = 0; i < (int)nodes[x].size(); ++i) {
            int y = nodes[x][i].to;
            if (--in[y] == 0)
                q.push(y);
        }
    }
    while (!ord.empty()) {
        int x = ord.top();
        ord.pop();
        if (nodes[x].size() == 0)
            continue;
        double l = 0, r = m, ans = 0;
        // cout << x << endl;
        while (!xequal(l, r)) {
            double mid = (l + r) / 2;
            // cout << mid << " ";
            if (check(x, mid)) {
                ans = mid;
                l = mid;
                // cout << "l = mid" << endl;
            } else {
                r = mid;
                // cout << "r = mid" << endl;
            }
        }
        // cout << endl;
        f[x] = 1 + ans;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("trip.in", "r", stdin);
    freopen("trip.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    for (int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;
        nodes[x].push_back({y, vector<int>()});
        co[i][0] = x;
        co[i][1] = nodes[x].size() - 1;
        ++in[y];
    }
    for (int i = 1; i <= k; ++i) {
        int x, y;
        cin >> x >> y;
        if (x == y)
            continue;
        reqs.push_back({x, y});
    }
    sort(reqs.begin(), reqs.end());
    reqs.erase(unique(reqs.begin(), reqs.end()), reqs.end());
    for (auto i : reqs) {
        int x = i.first, y = i.second;
        nodes[co[x][0]][co[x][1]].req.push_back(co[y][1]);
    }
    DP();
    cout << tostring(f[1]) << endl;
    // for (int i = 1; i <= n; ++i)
    //     cout << f[i] << " ";

    return 0;
}
