#include <bits/stdc++.h>
using namespace std;

constexpr int maxd = 100 + 10;
constexpr int maxg = 100 + 10;
constexpr int maxf = 3000 + 20;

struct garbage {
    int t, h, f;

    bool operator<(const garbage &rhs) const {
        return t < rhs.t;
    }
};

int d, g, ans;
garbage a[maxg];
int f[maxg][maxd];

int main() {
    ios::sync_with_stdio(false);
    cin >> d >> g;
    for (int i = 1; i <= g; ++i) {
        cin >> a[i].t >> a[i].f >> a[i].h;
    }
    sort(a + 1, a + 1 + g);
    memset(f, ~0x3f, sizeof(f));
    f[0][0] = 10;
    for (int i = 1; i <= g; ++i) {
        for (int j = 0; j < maxd; ++j) {
            int dt = a[i].t - a[i - 1].t;
            if (f[i - 1][j] >= dt) {
                f[i][j] = max(f[i][j], f[i - 1][j] + a[i].f - dt);
            }
            if (f[i - 1][j - a[i].h] >= dt && j >= a[i].h) {
                f[i][j] = max(f[i - 1][j - a[i].h] - dt, f[i][j]);
            }
            if (j >= d && f[i][j] >= 0) {
                cout << a[i].t << endl;
                return 0;
            }
            ans = max(ans, a[i].t + f[i][j]);
        }
    }
    cout << ans << endl;
    return 0;
}