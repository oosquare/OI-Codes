#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 50 + 10;
constexpr int maxk = 4 + 1;
constexpr int oo = 0x3f3f3f3f;

struct Point {
    int x = -1, y = -1;

    bool vaild() const {
        return x != -1 && y != -1;
    }

    friend ostream &operator<<(ostream &os, const Point &p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

struct Rectangle {
    Point pmin, pmax;

    bool vaild() const {
        return pmin.vaild() == true && pmax.vaild() == true;
    }

    bool inside(const Point &p) const {
        return pmin.x <= p.x && p.x <= pmax.x && pmin.y <= p.y && p.y <= pmax.y;
    }

    Rectangle extend(const Point &p) const {
        if (vaild() == false)
            return {p, p};
        return {{min(pmin.x, p.x), min(pmin.y, p.y)}, {max(pmax.x, p.x), max(pmax.y, p.y)}};
    }

    int area() const {
        if (vaild() == false)
            return oo;
        return (pmax.x - pmin.x) * (pmax.y - pmin.y);
    }

    friend ostream &operator<<(ostream &os, const Rectangle &rect) {
        os << "{" << rect.pmin << ", " << rect.pmax << "}";
        return os;
    }
};

int n, k, ans = 0x3f3f3f3f;
Rectangle rect[maxk];
Point point[maxn];

void update() {
    int res = 0;
    for (int i = 1; i <= k; ++i) {
        if (rect[i].vaild() == false)
            return;
        res += rect[i].area();
    }
    ans = min(ans, res);
}

bool rectAnd(const Rectangle &lhs, const Rectangle &rhs) {
    {
        Point tmp[4] = {
            {lhs.pmin.x, lhs.pmin.y},
            {lhs.pmin.x, lhs.pmax.y},
            {lhs.pmax.x, lhs.pmin.y},
            {lhs.pmax.x, lhs.pmin.y}
        };
        for (int i = 0; i < 4; ++i)
            if (rhs.inside({tmp[i].x, tmp[i].y}))
                return true;
    }
    {
        Point tmp[4] = {
            {rhs.pmin.x, rhs.pmin.y},
            {rhs.pmin.x, rhs.pmax.y},
            {rhs.pmax.x, rhs.pmin.y},
            {rhs.pmax.x, rhs.pmin.y}
        };
        for (int i = 0; i < 4; ++i)
            if (lhs.inside({tmp[i].x, tmp[i].y}))
                return true;
    }
    return false;
}

bool check(int ri, int pi) {
    for (int i = 1; i <= k; ++i) {
        if (i == ri)
            continue;
        if (rect[i].inside(point[pi]))
            return false;
    }
    Rectangle newRect = rect[ri].extend(point[pi]);
    for (int i = 1; i <= k; ++i) {
        if (i == ri)
            continue;
        if (rectAnd(newRect, rect[i]) == true)
            return false;
    }
    return true;
}

void dfs(int dep) {
    if (dep == n + 1) {
        update();
        return;
    }
    for (int i = 1; i <= k; ++i) {
        if (check(i, dep) == false)
            continue;
        Rectangle tmp = rect[i];
        rect[i] = rect[i].extend(point[dep]);
        dfs(dep + 1);
        rect[i] = tmp;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
        cin >> point[i].x >> point[i].y;
    dfs(1);
    cout << ans << endl;
    return 0;
}