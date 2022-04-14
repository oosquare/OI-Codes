#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int maxn = 100000 + 10;

int n, k;
ll sum[maxn];

struct Span {
    int l, r;

    bool operator<(const Span &rhs) const {
        return sum[r] - sum[l - 1] < sum[rhs.r] - sum[rhs.l - 1];
    }
};

priority_queue<Span> q;

int main() {
    freopen("ksum.in", "r", stdin);
    freopen("ksum.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> sum[i];
        sum[i] += sum[i - 1];
    }
    for (int i = 1; i <= n; ++i)
        q.push({1, i});
    for (int i = 1; i <= k; ++i) {
        Span s = q.top();
        q.pop();
        cout << sum[s.r] - sum[s.l - 1] << " ";
        if (s.l == s.r)
            continue;
        q.push({s.l + 1, s.r});
    }
    return 0;
}
