#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int MAX_N = 2e3 + 10;
const double PI = acos(-1.0);

struct Point {
    int x, y;
};

struct Range {
    double l, r;
    int dl, dr;

    bool operator<(const Range &rhs) const { return dl != rhs.dl ? dl < rhs.dl : dr < rhs.dr; }
};

int n, r;
Point points[MAX_N];
Range ranges[MAX_N];
int len, arr[2 * MAX_N];
int f[MAX_N], ans;

inline int lowbit(int x) { return x & (-x); }

void update(int x, int y) {
    for (; x <= len; x += lowbit(x)) arr[x] = max(arr[x], y);
}

int query(int x) {
    int res = 0;

    for (; x; x -= lowbit(x)) res = max(res, arr[x]);

    return res;
}

void discretize() {
    vector<double> vals;

    for (int i = 1; i <= n; ++i) {
        vals.push_back(ranges[i].l);
        vals.push_back(ranges[i].r);
    }

    sort(vals.begin(), vals.end());
    auto it = unique(vals.begin(), vals.end());
    vals.erase(it, vals.end());
    len = vals.size();

    for (int i = 1; i <= n; ++i) {
        ranges[i].dl = lower_bound(vals.begin(), vals.end(), ranges[i].l) - vals.begin() + 1;
        ranges[i].dr = lower_bound(vals.begin(), vals.end(), ranges[i].r) - vals.begin() + 1;
    }
}

int dp(int start) {
    int ans = 1;

    for (int i = 1; i <= len; ++i) arr[i] = 0;

    for (int i = start + 1; i <= n; ++i) f[i] = 0;

    f[start] = 1;
    update(ranges[start].dr, f[start]);

    for (int i = start + 1; i <= n && ranges[i].dl <= ranges[start].dr; ++i) {
        if (ranges[i].dr <= ranges[start].dr)
            continue;

        f[i] = query(ranges[i].dr - 1) + 1;
        update(ranges[i].dr, f[i]);
        ans = max(ans, f[i]);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> r;

    for (int i = 1; i <= n; ++i) {
        auto &[x, y] = points[i];
        cin >> x >> y;
        double g = atan2(y, x);
        double d = acos(r / sqrt(x * x + y * y));
        ranges[i].l = g - d;
        ranges[i].r = g + d;

        while (ranges[i].l <= -PI) ranges[i].l += 2 * PI;

        while (ranges[i].r > PI) ranges[i].r -= 2 * PI;

        if (ranges[i].l > ranges[i].r)
            swap(ranges[i].l, ranges[i].r);
    }

    discretize();
    sort(ranges + 1, ranges + 1 + n);

    for (int i = 1; i <= n; ++i) ans = max(ans, dp(i));

    cout << ans << endl;
    return 0;
}