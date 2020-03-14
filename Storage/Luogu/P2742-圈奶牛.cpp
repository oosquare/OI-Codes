#include <bits/stdc++.h>
using namespace std;

struct vec {
    double x, y;
    vec operator+(const vec &rhs) const { return {x + rhs.x, y + rhs.y}; }
    vec operator-(const vec &rhs) const { return {x - rhs.x, y - rhs.y}; }
    double dot(const vec &rhs) const { return x * rhs.x + y * rhs.y; }
    double cross(const vec &rhs) const { return x * rhs.y - y * rhs.x; }
};

constexpr int maxn = 1e5 + 10;
vec points[maxn], stk[maxn];
int n, len;

double dist(const vec &a, const vec &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool cmp(const vec &a, const vec &b) {
    double tmp = (a - points[1]).cross(b - points[1]);
    if (tmp > 0)
        return true;
    if (tmp == 0 && dist(points[0], a) < dist(points[0], b))
        return 1;
    return false;
}

void scan() {
    sort(points + 2, points + n + 1, cmp);
    stk[1] = points[1];
    len = 1;
    for (int i = 2; i <= n; ++i) {
        while (len > 1 &&
               (stk[len] - stk[len - 1]).cross(points[i] - stk[len]) <= 0)
            --len;
        stk[++len] = points[i];
    }
    stk[++len] = stk[1];
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lf%lf", &points[i].x, &points[i].y);
        if (i != 1 && points[i].y < points[1].y)
            swap(points[i], points[1]);
    }
    scan();
    double ans = 0;
    for (int i = 1; i < len; ++i) {
        ans += dist(stk[i], stk[i + 1]);
    }
    printf("%.2lf\n", ans);
    return 0;
}