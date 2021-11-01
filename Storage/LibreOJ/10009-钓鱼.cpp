#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>
#include <queue>
using namespace std;

constexpr int maxn = 100 + 10;

struct Pool {
    int id, now;

    bool operator<(const Pool &rhs) const {
        return now < rhs.now;
    }
};

int n, h, ans, f[maxn], d[maxn], t[maxn];

int solve(int last) {
    priority_queue<Pool> q;
    int rest = h, ans = 0;

    for (int i = 1; i < last; ++i)
        rest -= t[i];

    if (rest <= 0)
        return 0;

    for (int i = 1; i <= last; ++i)
        q.push({i, f[i]});

    for (int i = 1; i <= rest && !q.empty(); ++i) {
        auto [id, now] = q.top();
        q.pop();
        ans += now;
        now -= d[id];

        if (now > 0)
            q.push({id, now});
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    cin >> h;
    h = h * 60 / 5;

    for (int i = 1; i <= n; ++i)
        cin >> f[i];

    for (int i = 1; i <= n; ++i)
        cin >> d[i];

    for (int i = 1; i < n; ++i)
        cin >> t[i];

    for (int i = 1; i <= n; ++i)
        ans = max(ans, solve(i));

    cout << ans << endl;
    return 0;
}