#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

constexpr int maxn = 2e6 + 10;
constexpr int mod = 998244353;

int t, m, a, b, c, d, p[maxn];
unsigned seed;
bool purchased[maxn], in[maxn];
int now, q[maxn], l, r;
int del[maxn], fr, bk;
int ans;

unsigned randnum() {
    seed = seed ^ (seed << 13);
    seed = seed ^ (seed >> 17);
    seed = seed ^ (seed << 5);
    return seed;
}

void input() {
    cin >> m >> seed >> a >> b >> c >> d;

    for (int i = 1; i <= m; ++i)
        if (randnum() % c == 0)
            p[i] = -1;
        else
            p[i] = randnum() % b;
}

void solve() {
    input();
    fr = bk = 0;
    l = 1;
    r = 0;
    ans = 0;
    now = a + 1;

    for (int i = 0; i <= a; ++i)
        purchased[i] = in[i] = true;

    for (int i = a + 1; i <= b; ++i)
        purchased[i] = in[i] = false;

    for (int i = 1; i <= m; ++i) {
        if (p[i] != -1 && !purchased[p[i]]) {
            purchased[p[i]] = in[p[i]] = true;

            while (purchased[now])
                ++now;
        } else if (p[i] != -1 && in[p[i]]) {
            if (d == 1)
                continue;

            in[p[i]] = false;
            del[++bk] = p[i];

            while (l <= r && del[q[r]] >= p[i])
                --r;

            q[++r] = bk;
        } else {
            if (d == 1)
                continue;

            if (fr >= bk)
                continue;

            ++fr;
            in[del[fr]] = true;

            while (l <= r && q[l] <= fr)
                ++l;
        }

        int res = min(now, (l <= r ? del[q[l]] : 0x3f3f3f3f));
        ans ^= (1ll * res * (1ll * i * i % mod + 7ll * i % mod) % mod);
    }

    cout << ans << endl;
}

int main() {
    freopen("knowledge.in", "r", stdin);
    freopen("knowledge.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> t;

    while (t--)
        solve();
    return 0;
}
