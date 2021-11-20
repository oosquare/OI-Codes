#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
#include <cstring>
using namespace std;

using ll = long long;

constexpr int maxn = 10000 + 10;
constexpr int maxb = 1000 + 10;
constexpr ll oo = 0x3f;

struct Segment {
    int l, r;
    ll v, c;

    bool operator<(const Segment &rhs) const {
        return l < rhs.l;
    }
};

int l, n, b;
Segment s[maxn];
ll f[maxb][maxb], ans = -1;

int main() {
    ios::sync_with_stdio(false);
    cin >> l >> n >> b;

    for (int i = 1; i <= n; ++i) {
        int x, w, v, c;
        cin >> x >> w >> v >> c;
        s[i] = {x, x + w, v, c};
    }

    sort(s + 1, s + 1 + n);
    memset(f, -1, sizeof(f));

    f[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        auto [l, r, v, c] = s[i];

        for (int j = 0; j <= b - c; ++j)
            if (f[l][j] != -1)
                f[r][j + c] = max(f[r][j + c], f[l][j] + v);
    }

    for (int i = 0; i <= b; ++i)
        ans = max(ans, f[l][i]);

    cout << ans << endl;
    return 0;
}