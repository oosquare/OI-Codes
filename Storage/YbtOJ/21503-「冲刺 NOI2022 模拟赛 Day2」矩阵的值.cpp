#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>
#include <algorithm>
using namespace std;

constexpr int MAX_N = 500 + 10;
constexpr long double EPSILON = 1e-7;

int n, tot;
long long sum[MAX_N][MAX_N];
pair<int, int> range[MAX_N * MAX_N];
long double ans = -1e9;

long long calc(int l, int r, int i) {
    return sum[r][i] - sum[l - 1][i];
}

bool check(int l, int r, long double x) {
    long double mi = 0;
    long double val = 2 * x * (r - l + 1);

    for (int i = 1; i <= n; ++i) {
        if ((calc(l, r, i) - 2 * x * i - mi) - val >= -EPSILON)
            return true;

        mi = min(mi, calc(l, r, i) - 2 * x * i);
    }

    return false;
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("otto.in", "r", stdin);
    freopen("otto.out", "w", stdout);
#else
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(1000000);
    cin >> n;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> sum[i][j];

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            sum[i][j] += sum[i][j - 1];

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            sum[i][j] += sum[i - 1][j];

    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j)
            range[++tot] = { i, j };
    
    shuffle(range + 1, range + 1 + tot, mt19937((random_device())()));

    for (int i = 1; i <= tot; ++i) {
        if (!check(range[i].first, range[i].second, ans))
            continue;
        
        long double l = ans, r = 1e12;

        while (abs(r - l) > EPSILON) {
            long double mid = (l + r) / 2;

            if (check(range[i].first, range[i].second, mid))
                l = mid;
            else
                r = mid;
        }

        ans = l;
    }

    cout << ans << endl;
    return 0;
}
