#include <bits/stdc++.h>
using namespace std;

int n, m, a[30], b[30], logn;
double avg, ans = 1e18;

double solve() {
    for (int i = 1; i <= m; ++i)
        b[i] = a[i];
    for (int i = m + 1; i <= n; ++i) {
        int mx = 0;
        for (int j = 1; j <= m; ++j)
            if (mx == 0 || b[j] + a[i] < b[mx] + a[i])
                mx = j;
        b[mx] += a[i];
    }
    double res = 0;
    for (int i = 1; i <= m; ++i)
        res += (b[i] - avg) * (b[i] - avg);
    return res;
}

inline void run() {
    for (int i = 1; i <= 10; ++i) {
        random_shuffle(a + 1, a + 1 + n);
        ans = min(ans, solve());
    }
}

int main() {
    ios::sync_with_stdio(false);
    srand(time(nullptr));
    auto st = clock();
    cin >> n >> m;
    logn = log(n);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        avg += a[i];
    }
    avg /= m;
    while (clock() - st < 900000)
        run();
    cout << fixed << setprecision(2) << sqrt(ans / m) << endl;
    return 0;
}