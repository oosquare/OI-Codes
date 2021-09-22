#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int maxn = 1e6 + 10;
constexpr ll oo = 0x3f3f3f3f3f3f3f3f;

struct Edge {
    int to, next;
};

Edge tree[maxn * 2];
int uuid, head[maxn], fa[maxn], w[maxn];
int n;
bool vis[maxn];
ll f[maxn][2], ans;

void link(int x, int y) {
    tree[++uuid] = {y, head[x]};
    head[x] = uuid;
}

void Dp(int x, int root) {
    vis[x] = true;
    f[x][0] = 0;
    f[x][1] = w[x];
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next) {
        if (y == root) continue;
        Dp(y, root);
        f[x][0] += max(f[y][0], f[y][1]);
        f[x][1] += f[y][0];
    }
}

ll calc(int root) {
    int x = root;
    vis[x] = true;
    while (vis[fa[x]] == false) {
        x = fa[x];
        vis[x] = true;
    }
    ll ans1, ans2;
    Dp(x, x);
    ans1 = f[x][0];
    x = fa[x];
    Dp(x, x);
    ans2 = f[x][0];
    return max(ans1, ans2);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i] >> fa[i];
        // link(i, fa[i]);
        link(fa[i], i);
    }
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) continue;
        ans += calc(i);
    }
    cout << ans << endl;
    return 0;
}