#include <iostream>
#include <queue>
#include <algorithm>

constexpr int MAX_N = 200000 + 5;
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;

struct Data {
    int id;
    long long val;

    bool operator<(const Data &rhs) const { return val < rhs.val; }
};

class PriorityQueue {
public:
    void set_removed(std::function<bool(int)> func) {
        is_removed = func;
    }

    void push(const Data &d) {
        if (!is_removed(d.id))
            q.push(d);
    }

    Data top() {
        adjust();
        return q.top();
    }

    bool empty() {
        adjust();
        return q.empty();
    }

    void clear() {
        while (!q.empty())
            q.pop();
    }

private:
    std::priority_queue<Data> q;
    std::function<bool(int)> is_removed;

    void adjust() {
        while (!q.empty() && is_removed(q.top().id))
            q.pop();
    }
};

int t, n, k, p;
int a[MAX_N], b[MAX_N];
bool selected_a[MAX_N], selected_b[MAX_N];
PriorityQueue qa0, qa1, qb0, qb1, qab;
int cnt;
long long ans;

void solve() {
    std::cin >> n >> k >> p;
    qa0.clear();
    qa1.clear();
    qb0.clear();
    qb1.clear();
    qab.clear();
    cnt = 0;
    ans = 0;

    for (int i = 1; i <= n; ++i)
        selected_a[i] = selected_b[i] = false;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    for (int i = 1; i <= n; ++i)
        std::cin >> b[i];

    for (int i = 1; i <= n; ++i) {
        qa0.push({ i, a[i] });
        qb0.push({ i, b[i] });
        qab.push({ i, a[i] + b[i] });
    }
 
    for (int i = 1; i <= k; ++i) {
        long long res1 = (!qab.empty() ? qab.top().val : -INF);
        long long res2 = (!qa0.empty() && !qb0.empty() && cnt != k - p ? qa0.top().val + qb0.top().val : -INF);
        long long res3 = (!qa1.empty() && !qb0.empty() ? qa1.top().val + qb0.top().val : -INF);
        long long res4 = (!qa0.empty() && !qb1.empty() ? qa0.top().val + qb1.top().val : -INF);
        long long res5 = (!qa1.empty() && !qb1.empty() ? qa1.top().val + qb1.top().val : -INF);
        long long res = std::max(std::max(std::max(std::max(res1, res2), res3), res4), res5);
        ans += res;

        if (res == res5) {
            --cnt;
            int ida = qa1.top().id;
            int idb = qb1.top().id;
            selected_a[ida] = true;
            selected_b[idb] = true;
        } else if (res == res1) {
            int id = qab.top().id;
            selected_a[id] = selected_b[id] = true;
        } else if (res == res3) {
            int ida = qa1.top().id;
            int idb = qb0.top().id;
            selected_a[ida] = true;
            selected_b[idb] = true;
            qa1.push({ idb, a[idb] });
        } else if (res == res4) {
            int ida = qa0.top().id;
            int idb = qb1.top().id;
            selected_a[ida] = true;
            selected_b[idb] = true;
            qb1.push({ ida, b[ida] });
        } else {
            int ida = qa0.top().id;
            int idb = qb0.top().id;
            ++cnt;
            selected_a[ida] = true;
            selected_b[idb] = true;
            qa1.push({ idb, a[idb] });
            qb1.push({ ida, b[ida] });
        }
    }

    std::cout << ans << std::endl;
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("goods.in", "r", stdin);
    std::freopen("goods.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    qa0.set_removed([](int x) { return selected_a[x]; });
    qa1.set_removed([](int x) { return selected_a[x] || !selected_b[x]; });
    qb0.set_removed([](int x) { return selected_b[x]; });
    qb1.set_removed([](int x) { return selected_b[x] || !selected_a[x]; });
    qab.set_removed([](int x) { return selected_a[x] || selected_b[x]; });

    std::cin >> t;

    while (t--)
        solve();

    return 0;
}
