#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <numeric>

constexpr int MAX_N = 1000 + 10;

class Vector {
public:
    Vector(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator==(const Vector &rhs) const { return x == rhs.x && y == rhs.y; }
    bool operator!=(const Vector &rhs) const { return x != rhs.x || y != rhs.y; }
    bool operator<(const Vector &rhs) const { return (x != rhs.x ? x < rhs.x : y < rhs.y); }

    friend std::istream &operator>>(std::istream &is, Vector &v) { return (is >> v.x >> v.y); }
    friend std::ostream &operator<<(std::ostream &os, const Vector &v) { return (os << v.x << " " << v.y); }

    Vector operator+(const Vector &rhs) const { return { x + rhs.x, y + rhs.y }; }
    Vector operator-(const Vector &rhs) const { return { x - rhs.x, y - rhs.y }; }
    long long dot(const Vector &rhs) const { return 1ll * x * rhs.x + 1ll * y * rhs.y; }
    long long cross(const Vector &rhs) const { return 1ll * x * rhs.y - 1ll * y * rhs.x; }
    long long norm() const { return 1ll * x * x + 1ll * y * y; }
    Vector rotate() const { return { -y, x }; }

    Vector fix() const {
        Vector v(*this);
        int d = std::gcd(v.x, v.y);
        v.x /= d;
        v.y /= d;

        if (v.x < 0 || (v.x == 0 && v.y < 0)) {
            v.x = -v.x;
            v.y = -v.y;
        }

        return v;
    }

    bool is_down() const { return (y < 0 || (y == 0 && x < 0)); }

private:
    int x, y;
};

class Segment {
public:
    Segment(const Vector &start = Vector(), const Vector &direction = Vector()) : start(start), direction(direction) {}

    bool operator<(const Segment &rhs) const {
        if (direction != rhs.direction)
            return direction < rhs.direction;

        if (start.cross(direction) != rhs.start.cross(rhs.direction))
            return start.cross(direction) < rhs.start.cross(rhs.direction);

        return start < rhs.start;
    }

private:
    Vector start, direction;
};

int n, tot;
Vector points[MAX_N], tmp[MAX_N * 2];
Segment seg[MAX_N * MAX_N];
long long ans;

long long find(Vector a, Vector b) {
    if (b < a)
        std::swap(a, b);

    Segment seg1(a + a, (b - a).fix()), seg2(b + b, (b - a).fix());

    int l = (int) (std::upper_bound(seg + 1, seg + 1 + tot, seg1) - seg);
    int r = (int) (std::lower_bound(seg + 1, seg + 1 + tot, seg2) - seg);

    return std::max(r - l, 0);
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("C.in", "r", stdin);
    std::freopen("C.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);

    std::cin >> n;

    for (int i = 1; i <= n; ++i) {
        std::cin >> points[i];

        for (int j = 1; j < i; ++j)
            seg[++tot] = { points[j] + points[i], (points[i] - points[j]).rotate().fix() };
    }

    std::sort(seg + 1, seg + 1 + tot);

    for (int D = 1; D <= n; ++D) {
        int cnt = 0;

        for (int i = 1; i <= n; ++i)
            if (i != D)
                tmp[++cnt] = points[i] - points[D];

        std::sort(tmp + 1, tmp + 1 + cnt, [](const Vector &a, const Vector &b) {
            if (a.is_down() != b.is_down())
                return a.is_down() < b.is_down();

            return a.cross(b) > 0;
        });

        for (int i = 1; i <= cnt; ++i)
            tmp[cnt + i] = tmp[i];

        std::unordered_map<long long, int> mp;

        long long sum = 0;
        int l = 1, r = 1;

        for (int A = 1; A <= cnt; ++A) {
            while (tmp[A].cross(tmp[r]) > 0 || (tmp[A].cross(tmp[r]) == 0 && r <= cnt) || tmp[A].dot(tmp[r]) < 0)
                sum += mp[tmp[r++].norm()]++;

            while (l < r && tmp[l].dot(tmp[A]) >= 0)
                sum -= --mp[tmp[l++].norm()];

            if (sum)
                ans += sum * find(points[D], points[D] + tmp[A]);
        }
    }

    std::cout << 4 * ans << std::endl;
    return 0;
}