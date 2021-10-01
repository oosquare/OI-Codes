#include <bits/stdc++.h>
using namespace std;

constexpr int maxs = 400 + 10;
constexpr double oo = 1e18;

struct Edge {
    int to;
    double legnth;
};

struct Vector {
    int x, y;

    Vector(int x0 = 0, int y0 = 0) : x(x0), y(y0) {}

    Vector operator+(const Vector &rhs) {
        return Vector(x + rhs.x, y + rhs.y);
    }

    Vector operator-(const Vector &rhs) {
        return Vector(x - rhs.x, y - rhs.y);
    }

    long long operator*(const Vector &rhs) {
        return 1LL * x * rhs.x + 1LL * y * rhs.y; 
    }

    double distance() {
        return sqrt(1.0 * x * x + 1.0 * y * y);
    }

    friend istream &operator>>(istream &is, Vector &v) {
        is >> v.x >> v.y;
        return is;
    }
};

int n, s, t, a, b, ts[maxs];
vector<Edge> graph[maxs];
Vector pos[maxs];
double dis[maxs], ans = oo;
bool vis[maxs];

void link(int x, int y, double l) {
    graph[x].push_back({y, l});
    graph[y].push_back({x, l});
}

Vector calc(Vector a, Vector b, Vector c) {
    if ((a - b) * (c - b) == 0)
        swap(a, b);
    else if ((a - c) * (b - c) == 0)
        swap(a, c);
    return b - a + c;
}

void dijkstra(int start) {
    priority_queue<pair<double, int>> q;
    for (int i = 1; i <= 4 * s; ++i) {
        vis[i] = false;
        dis[i] = oo;
    }
    dis[start] = 0;
    q.push({0, start});
    while (!q.empty()) {
        int x = q.top().second;
        q.pop();
        if (vis[x] == true)
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

int id(int c, int i) {
    return (c - 1) * 4 + i;
}

void solve() {
    cin >> s >> t >> a >> b;
    for (int i = 1; i <= s; ++i) {
        cin >> pos[id(i, 1)] >> pos[id(i, 2)] >> pos[id(i, 3)];
        cin >> ts[i];
        pos[id(i, 4)] = calc(pos[id(i, 1)], pos[id(i, 2)], pos[id(i, 3)]);
    }

    for (int i = 1; i <= s; ++i) {
        for (int j = i + 1; j <= s; ++j) {
            for (int x = 1; x <= 4; ++x) {
                for (int y = 1; y <= 4; ++y) {
                    link(id(i, x), id(j, y), t * (pos[id(i, x)] - pos[id(j, y)]).distance());
                }
            }
        }
        for (int x = 1; x <= 4; ++x) {
            for (int y = x + 1; y <= 4; ++y) {
                link(id(i, x), id(i, y), ts[i] * (pos[id(i, x)] - pos[id(i, y)]).distance());
            }
        }
    }

    for (int i = 1; i <= 4; ++i) {
        dijkstra(id(a, i));
        for (int j = 1; j <= 4; ++j)
            ans = min(ans, dis[id(b, j)]);
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(1);
    cin >> n;
    while (n--)
        solve();
    return 0;
}