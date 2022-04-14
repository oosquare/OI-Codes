#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

constexpr int MAX_N = 610;
constexpr double EPSLION = 1e-8;

namespace Graph {

vector<int> graph[MAX_N * 6];
int dis[MAX_N], vis[MAX_N];
int s, t;

void link(int x, int y) {
    graph[x].push_back(y);
}

int bfs() {
    queue<int> q;
    q.push(s), memset(dis, 1, sizeof(dis)), dis[s] = 0, memset(vis, 0, sizeof(vis));

    while (!q.empty()) {
        int x = q.front();
        q.pop();

        if (vis[x])
            continue;

        vis[x] = 1;

        for (int y : graph[x])
            if (dis[x] + 1 < dis[y])
                dis[y] = dis[x] + 1, q.push(y);
    }

    for (int i = 0; i < MAX_N * 6; i++)
        graph[i].clear();

    return dis[t];
}

}  // namespace Graph

namespace Geometry {

struct Vector {
    double x, y;

    Vector(double x = 0, double y = 0) {
        this->x = x;
        this->y = y;
    }

    friend istream & operator>>(istream & is, Vector & v) {
        is >> v.x >> v.y;
        return is;
    }

    Vector operator+(const Vector & b) const {
        return Vector(x + b.x, y + b.y);
    }

    Vector operator-(const Vector & b) const {
        return Vector(x - b.x, y - b.y);
    }

    Vector operator*(const double & b) const {
        return Vector(x * b, y * b);
    }

    Vector operator/(const double & b) const {
        return Vector(x / b, y / b);
    }

    double dot(const Vector & b) const {
        return x * b.x + y * b.y;
    }

    double cross(const Vector & b) const {
        return x * b.y - y * b.x;
    }

    Vector rotate() const {
        return Vector(-y, x);
    }

    bool operator==(const Vector & b) const {
        return abs(b.y - y) < EPSLION && abs(b.x - x) < EPSLION;
    }

    bool same(const Vector & rhs) const {
        return abs(this->cross(rhs)) < EPSLION;
    }
};

struct Line {
    Vector a, b, d;
    int id;
    double alpha;

    void init(const Vector & x, const Vector & y) {
        a = x, b = y, d = b - a, alpha = atan2(d.y, d.x);
    }

    void init(const double & A, const double & B, const double & C) {
        double x, y;

        if (abs(A) > EPSLION)
            y = 0, x = -C / A;
        else
            x = 0, y = -C / B;

        init(Vector(x, y), Vector(x, y) + Vector(-B, A));
    }

    Line() {}

    Line(const Vector & a, const Vector & b) {
        init(a, b);
    }

    bool contain(const Vector & v) const {
        return d.same(v - a) && (a - v).dot(v - b) < EPSLION;
    }

    bool parallel(const Line & rhs) const {
        return d.same(rhs.d);
    }

    bool operator<(const Line & rhs) const {
        return alpha < rhs.alpha;
    }

    Vector intersection(const Line & rhs) const {
        return a + d * ((rhs.d.cross(a - rhs.a)) / (d.cross(rhs.d)));
    }

    bool right(const Vector & rhs) const {
        return ((rhs - a).cross(d)) > -EPSLION;
    }

    static Line midBisector(const Vector & a, const Vector & b) {
        Vector mid = (a + b) / 2;
        Line res;
        res.init(mid, mid + (b - a).rotate());
        return res;
    }
};

Vector a[MAX_N];

bool contain(Vector * a, int n, const Vector & x) {
    a[n + 1] = a[1];
    bool rev = 0;

    for (int i = 1; i <= n; i++) {
        if (Line(a[i], a[i + 1]).contain(x))
            return 1;

        if (x == a[i])
            return 1;

        if (min(a[i + 1].y, a[i].y) > x.y - EPSLION || max(a[i + 1].y, a[i].y) < x.y - EPSLION)
            continue;

        double nx = a[i].x + (x.y - a[i].y) / (a[i + 1].y - a[i].y) * (a[i + 1].x - a[i].x);

        if (nx > x.x)
            rev ^= 1;
    }

    return rev;
}

int get(Line * a, int n, Vector * res, int & l, int & r, int st, const Vector & now) {
    sort(a + 1, a + 1 + n);
    static Line q[MAX_N];
    l = 0, r = -1;
    q[++r] = a[1];

    for (int i = 2; i <= n; i++) {
        while (l < r && a[i].right(res[r]))
            --r;

        while (l < r && a[i].right(res[l + 1]))
            ++l;

        q[++r] = a[i];

        if (l < r && q[r].parallel(q[r - 1])) {
            if (q[r].right(q[r - 1].a) && q[r].d.dot(q[r - 1].d) < EPSLION)
                return 0;

            --r;

            if (!q[r].right(a[i].a))
                q[r] = a[i];
        }

        if (l < r)
            res[r] = q[r].intersection(q[r - 1]);
    }

    while (l < r && q[l].right(res[r]))
        --r;

    if (r - l <= 1)
        return 0;

    res[l] = q[r].intersection(q[l]);

    for (int i = l; i <= r; i++)
        Graph::link(st, q[i].id);

    if (contain(res + l - 1, r - l + 1, now))
        Graph::s = st;

    return r - l + 1;
}

} // namespace Geometry

int n, xx, yy;

int main() {
#ifdef ONLINE_JUDGE
    freopen("sea.in", "r", stdin);
    freopen("sea.out", "w", stdout);
#endif
    cin >> n >> xx >> yy;
    int t = n + 1;
    Geometry::Vector now;
    cin >> now;

    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }

    for (int i = 1; i <= n; i++)
        cin >> Geometry::a[i];

    for (int i = 1; i <= n; i++) {
        static Geometry::Line lines[MAX_N];
        static Geometry::Vector ans[MAX_N];
        int tot = 0;

        if (Geometry::a[i].x > xx || Geometry::a[i].y > yy)
            continue;

        for (int j = 1; j <= n; j++) {
            if (i != j) {
                if (Geometry::a[j].x > xx || Geometry::a[j].y > yy)
                    continue;

                lines[++tot] = Geometry::Line::midBisector(Geometry::a[i], Geometry::a[j]);
                lines[tot].id = j;
            }
        }
        
        lines[++tot].init(Geometry::Vector(0, 0), Geometry::Vector(xx, 0));
        lines[tot].id = t;

        lines[++tot].init(Geometry::Vector(xx, 0), Geometry::Vector(xx, yy));
        lines[tot].id = t;

        lines[++tot].init(Geometry::Vector(xx, yy), Geometry::Vector(0, yy));
        lines[tot].id = t;

        lines[++tot].init(Geometry::Vector(0, yy), Geometry::Vector(0, 0));
        lines[tot].id = t;
        
        int ll, rr;
        get(lines, tot, ans, ll, rr, i, now);
    }

    Graph::t = t;
    cout << Graph::bfs() << endl;
    return 0;
}
