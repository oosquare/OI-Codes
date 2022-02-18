#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
#include <queue>
using std::abs;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;

const int maxn = 610;
const double eps = 1e-8;

struct V {
    double x, y;
    V() {}
    V(double x_, double y_) : x(x_), y(y_) {}
    void in() { cin >> x >> y; }
    void print() { cout << x << " " << y << endl; }
    void print_2() { cout << x << " " << y << " "; }
    inline V operator+(const V &b) const { return V(x + b.x, y + b.y); }
    inline V operator-(const V &b) const { return V(x - b.x, y - b.y); }
    inline V operator*(const double &b) const { return V(x * b, y * b); }
    inline V operator/(const double &b) const { return V(x / b, y / b); }
    inline double operator*(const V &b) const { return x * b.x + y * b.y; }
    inline double operator&(const V &b) const { return x * b.y - y * b.x; }
    inline V rotate_90() { return V(-y, x); }
    inline bool operator==(const V &b) const { return abs(b.y - y) < eps && abs(b.x - x) < eps; }
};

struct line {
    V a, b, d;
    int id;
    double alpha;
    void init(const V &x, const V &y) { a = x, b = y, d = b - a, alpha = atan2(d.y, d.x); }
    void init(const double &A, const double &B, const double &C)  // Ax+By+C=0
    {
        double x, y;
        if (abs(A) > eps)
            y = 0, x = -C / A;
        else
            x = 0, y = -C / B;
        init(V(x, y), V(x, y) + V(-B, A));
    }
    line() {}
    line(const V &a, const V &b) { init(a, b); }
    inline void print() { cout << alpha << " ", a.print_2(), b.print_2(), d.print(); }
};
inline bool same_line(const V &a, const V &b) { return abs(a & b) < eps; }
inline bool on_seg(const line &a, const V &b) {
    return same_line(a.d, b - a.a) && (a.a - b) * (a.b - b) < eps;
}
inline bool parallel(const line &a, const line &b) { return same_line(a.d, b.d); }
inline bool cmp(const line &a, const line &b) { return a.alpha < b.alpha; }
inline V cross_point(const line &a, const line &b) { return a.a + a.d * ((b.d & (a.a - b.a)) / (a.d & b.d)); }
inline bool on_right(const line &a, const V &b) { return ((b - a.a) & a.d) > -eps; }

inline line mid_bisector(const V &a, const V &b) {
    V mid = (a + b) / 2;
    line res;
    res.init(mid, mid + (b - a).rotate_90());
    return res;
}

std::vector<int> e[maxn * 6];
inline void add(int x, int y) { e[x].push_back(y); }

namespace bfs {
int dis[maxn], vis[maxn];
int s, t;
int bfs() {
    std::queue<int> q;
    q.push(s), memset(dis, 1, sizeof(dis)), dis[s] = 0, memset(vis, 0, sizeof(vis));
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (vis[x])
            continue;
        vis[x] = 1;
        for (int v : e[x])
            if (dis[x] + 1 < dis[v])
                dis[v] = dis[x] + 1, q.push(v);
    }
    for (int i = 0; i < maxn * 6; i++) e[i].clear();
    return dis[t];
}
}  // namespace bfs

bool in_poly(V *a, int n, const V &x) {
    a[n + 1] = a[1];
    bool rev = 0;
    for (int i = 1; i <= n; i++) {
        if (on_seg(line(a[i], a[i + 1]), x))
            return 1;
        if (x == a[i])
            return 1;
        if (std::min(a[i + 1].y, a[i].y) > x.y - eps || std::max(a[i + 1].y, a[i].y) < x.y - eps)
            continue;
        double nx = a[i].x + (x.y - a[i].y) / (a[i + 1].y - a[i].y) * (a[i + 1].x - a[i].x);
        if (nx > x.x)
            rev ^= 1;
    }
    return rev;
}

int SI(line *a, int n, V *res, int &l, int &r, int st, V now) {
    std::sort(a + 1, a + 1 + n, cmp);
    // for (int i = 1; i <= n; i++)
    //    a[i].print();
    static line q[maxn];
    l = 0, r = -1;
    q[++r] = a[1];
    for (int i = 2; i <= n; i++) {
        while (l < r && on_right(a[i], res[r])) r--;
        while (l < r && on_right(a[i], res[l + 1])) l++;
        q[++r] = a[i];
        if (l < r && parallel(q[r], q[r - 1])) {
            if (on_right(q[r], q[r - 1].a) && q[r].d * q[r - 1].d < eps)
                return 0;
            r--;
            if (!on_right(q[r], a[i].a))
                q[r] = a[i];
        }
        if (l < r)
            res[r] = cross_point(q[r], q[r - 1]);
    }
    while (l < r && on_right(q[l], res[r])) r--;
    if (r - l <= 1)
        return 0;
    res[l] = cross_point(q[r], q[l]);
    // cout << st << " " << "-----" << endl;
    // for (int i = l; i <= r; i++)
    //    q[i].print();
    // for (int i = l; i <= r; i++)
    //    res[i].print();
    for (int i = l; i <= r; i++) add(st, q[i].id);
    if (in_poly(res + l - 1, r - l + 1, now))
        bfs::s = st;  //, cout << "!!!" << st << endl;
    return r - l + 1;
}

V a[maxn];

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, X, Y;
        cin >> n >> X >> Y;
        int t = n + 1;
        V now;
        now.in();
        if (n == 0) {
            cout << 0 << endl;
            continue;
        }
        for (int i = 1; i <= n; i++) a[i].in();
        for (int i = 1; i <= n; i++) {
            static line l[maxn];
            static V ans[maxn];
            int tot = 0;
            if (a[i].x > X || a[i].y > Y)
                continue;
            for (int j = 1; j <= n; j++)
                if (i != j) {
                    if (a[j].x > X || a[j].y > Y)
                        continue;
                    l[++tot] = mid_bisector(a[i], a[j]), l[tot].id = j;
                }
            l[++tot].init(V(0, 0), V(X, 0)), l[tot].id = t;
            l[++tot].init(V(X, 0), V(X, Y)), l[tot].id = t;
            l[++tot].init(V(X, Y), V(0, Y)), l[tot].id = t;
            l[++tot].init(V(0, Y), V(0, 0)), l[tot].id = t;
            int ll, rr;
            // cerr << "??" << endl;
            SI(l, tot, ans, ll, rr, i, now);
        }
        bfs::t = t;
        cout << bfs::bfs() << endl;
    }
}
