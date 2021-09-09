#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int maxn = 1e5 + 10;

struct Edge {
    int to, next;
    ll length;
};

Edge tree[maxn * 2];
int uuid, head[maxn];
int n;
ll ans = 0x3f3f3f3f3f3f3f3f, sumc, c[maxn], sum[maxn], f[maxn][2];

void link(int x, int y, ll l) {
    tree[++uuid] = {y, head[x], l};
    head[x] = uuid;
}

void DP1(int x, int fa) {
    sum[x] = c[x];
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next) {
        if (y == fa) continue;
        DP1(y, x);
        sum[x] += sum[y];
        f[x][0] += f[y][0] + sum[y] * tree[i].length;
    }
}

void DP2(int x, int fa) {
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next) {
        if (y == fa) continue;
        f[y][1] = f[x][1] + f[x][0] - (f[y][0] + sum[y] * tree[i].length);
        f[y][1] += (sumc - sum[y]) * tree[i].length;
        DP2(y, x);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
        sumc += c[i];
    }
    for (int i = 1; i < n; ++i) {
        int a, b;
        ll l;
        cin >> a >> b >> l;
        link(a, b, l);
        link(b, a, l);
    }
    DP1(1, 0);
    DP2(1, 0);
    for (int i = 1; i <= n; ++i) ans = min(ans, f[i][0] + f[i][1]);
    cout << ans << endl;
    return 0;
}