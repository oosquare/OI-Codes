#include <bits/stdc++.h>

using namespace std;

const int N = 8e4 + 5;
int n, t;
struct point {
    int x, y;
};
vector<point> a[N];

inline bool check(point p, int k) {
    int cnt = 0;
    for (int i = 0, in = (int)a[k].size(); i < in - 1; ++i) {
        if (a[k][i].y == a[k][i + 1].y) continue;
        if (p.y < min(a[k][i].y, a[k][i + 1].y) || p.y >= max(a[k][i].y, a[k][i + 1].y)) continue;
        long double x = 1.0 * (p.y - a[k][i].y) * (a[k][i + 1].x - a[k][i].x) / (a[k][i + 1].y - a[k][i].y) + a[k][i].x;
        if (x > p.x)
            ++cnt;
    }   
    return cnt % 2 == 1;
}

int main() {
#ifdef ONLINE_JDUGE
    freopen("skip.in", "r", stdin);
    freopen("skip.out", "w", stdout);  
#else
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1, k, lst, fir, sec; i <= n; ++i) {
        cin >> k;
        cin >> fir;
        lst = fir;
        for (int j = 2; j <= k; ++j) {
            cin >> sec;
            a[i].push_back(point{lst, sec});
            lst = sec;
        }
        a[i].push_back(point{fir, sec});
    }
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int x, y, f = 0;
        cin >> x >> y;
        for (int j = 1; j <= n; ++j)
            if (check(point{x, y}, j)) {
                cout << j << '\n';
                f = 1;
                break;
            }
        if (!f) cout << -1 << '\n';
    }
}
