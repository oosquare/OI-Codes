#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
using namespace std;

constexpr int MAXN = 2000 + 10;

struct Vector {
public:
    Vector(int x = 0, int y = 0, int id = 0) {
        this->x = x;
        this->y = y;
        this->id = id;
    }

    friend istream &operator>>(istream &is, Vector &v) {
        is >> v.x >> v.y;
        return is;
    }

    friend ostream &operator<<(ostream &os, const Vector &v) {
        os << v.x << " " << v.y;
        return os;
    }

    Vector operator+(const Vector &rhs) const {
        return Vector(x + rhs.x, y + rhs.y);
    }

    Vector operator-(const Vector &rhs) const {
        return Vector(x - rhs.x, y - rhs.y);
    }

    long long dot(const Vector &rhs) const {
        return 1ll * x * rhs.x + 1ll * y * rhs.y;
    }

    long long cross(const Vector &rhs) const {
        return 1ll * x * rhs.y - 1ll * y * rhs.x;
    }

    Vector rotate() const {
        return Vector(-y, x);
    }

    int x, y, id;
};

struct Segment {
public:
    Segment(const Vector & p1 = Vector(), const Vector & p2 = Vector()) {
        this->p1 = p1;
        this->p2 = p2;
        d = p2 - p1;
    }

    long long area(const Vector &p) const {
        return abs((p - p1).cross(p2 - p1));
    }

    double slope() const {
        if (p2.x == p1.x)
            return 1e40;
        
        return 1.0 * (p2.y - p1.y) / (p2.x - p1.x);
    }

    bool operator<(const Segment &rhs) const {
        return slope() < rhs.slope();
    }

    Vector p1, p2, d;
};

int n, tot;
long long m;
Vector p[MAXN];
Segment s[MAXN * MAXN];
int pos[MAXN], seq[MAXN];

int findLeft(int x, int now) {
    int l = 1, r = x, pos = -1;

    while (l < r) {
        int mid = (l + r) / 2;
        if (s[now].area(p[seq[mid]]) >= m) {
            pos = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    return pos;
}

int findRight(int x, int now) {
    int l = x, r = n, pos = -1;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (s[now].area(p[seq[mid]]) >= m) {
            pos = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    return pos;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    m *= 2;

    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
        p[i].id = i;
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < i; ++j)
            s[++tot] = Segment(p[i], p[j]);


    sort(s + 1, s + 1 + tot);
    iota(seq + 1, seq + 1 + n, 1);

    sort(seq + 1, seq + 1 + n, [](int l, int r) {
        return p[l].x != p[r].x ? p[l].x < p[r].x : p[l].y < p[r].y;
    });

    for (int i = 1; i <= n; ++i)
        pos[seq[i]] = i;
    
    for (int i = 1; i <= tot; ++i) {
        auto [mi, mx] = minmax(pos[s[i].p1.id], pos[s[i].p2.id]);

        int q1 = findLeft(mi, i);

        if (q1 != -1 && s[i].area(p[seq[q1]]) == m) {
            cout << "Yes" << endl;
            cout << p[seq[q1]] << endl;
            cout << p[seq[mi]] << endl;
            cout << p[seq[mx]] << endl;
            return 0;
        }

        int q2 = findRight(mx, i);

        if (q2 != -1 && s[i].area(p[seq[q2]]) == m) {
            cout << "Yes" << endl;
            cout << p[seq[q2]] << endl;
            cout << p[seq[mi]] << endl;
            cout << p[seq[mx]] << endl;
            return 0;
        }

        swap(seq[mi], seq[mx]);
        swap(pos[s[i].p1.id], pos[s[i].p2.id]);
    }

    cout << "No" << endl;
    return 0;
}