#include <iostream>
#include <algorithm>

constexpr int MAX_N = 100000 + 10;

struct Score {
    long long sum;
    int id;

    bool operator<(const Score &rhs) const {
        return sum > rhs.sum;
    }
};

int n, x;
int b[MAX_N], l[MAX_N], r[MAX_N];
long long goal;
Score scores[MAX_N];

long long calc(int id, long long val) {
    return std::min(val, 1ll * b[id]) * l[id] + std::max(val - b[id], 0ll) * r[id];
}

bool check(long long t) {
    long long sum = 0;
    long long full = std::min(t / x, 1ll * n), rest = t - (t / x) * x;

    for (int i = 1; i <= full; ++i)
        sum += scores[i].sum;

    if (sum >= goal)
        return true;

    for (int i = (int) full + 1; i <= n; ++i)
        if (sum + calc(scores[i].id, rest) >= goal)
            return true;

    for (int i = 1; i <= full; ++i)
        if (sum - scores[i].sum + scores[full + 1].sum + calc(scores[i].id, rest) >= goal)
            return true;

    return false;
}

signed main() {
#ifdef ONLINE_JUDGE
    std::freopen("contest.in", "r", stdin);
    std::freopen("contest.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);

    std::cin >> n >> x;

    for (int i = 1; i <= n; ++i) {
        std::cin >> b[i] >> l[i] >> r[i];
        goal += 1ll * b[i] * l[i];
        scores[i] = { calc(i, x), i };
    }

    std::sort(scores + 1, scores + 1 + n);

    long long al = 0, ar = 1ll * n * x;
    long long ans = 0x3f3f3f3f3f3f3f3f;

    while (al <= ar) {
        long long mid = (al + ar) / 2;

        if (check(mid)) {
            ans = mid;
            ar = mid - 1;
        } else {
            al = mid + 1;
        }
    }

    std::cout << ans << std::endl;
    return 0;
}
