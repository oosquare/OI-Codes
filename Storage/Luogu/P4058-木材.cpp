#include <bits/stdc++.h>
using namespace std;

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = mygetchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = mygetchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = mygetchar();
    }
    return x * s;
}

constexpr int maxn = 1000000 + 5;
typedef long long ll;
ll height[maxn], m, mx;
int n;

bool check(ll x) {
    ll res = 0LL;
    for (int i = 1; i <= n; ++i)
        res += max(0LL, height[i] - x);
    return res >= m;
}

ll solve() {
    ll l = 0, r = mx, res = 0;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        if (check(mid)) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    n = read();
    m = read<ll>();
    for (int i = 1; i <= n; ++i)
        mx = max(mx, height[i] = read<ll>());
    printf("%lld\n", solve());
    return 0;
}