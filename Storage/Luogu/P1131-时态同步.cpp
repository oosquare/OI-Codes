#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 500000 + 10;

using ll = long long;

struct Edge {
    int to, next;
    ll length;
};

Edge tree[maxn * 2];
int uuid, head[maxn];
int n, s;
ll maxl[maxn], f[maxn];

template <typename T>
void update(T &x, T y) {
    if (x < y) x = y;
}

void link(int x, int y, ll l) {
    tree[++uuid] = {y, head[x], l};
    head[x] = uuid;
}

void Dfs(int x, int fa) {
    for (int e = head[x], y; y = tree[e].to, e; e = tree[e].next) {
        if (y == fa) continue;
        Dfs(y, x);
        update(maxl[x], maxl[y] + tree[e].length);
    }
}

void Dp(int x, int fa) {
    for (int e = head[x], y; y = tree[e].to, e; e = tree[e].next) {
        if (y == fa) continue;
        Dp(y, x);
        f[x] += f[y] + maxl[x] - (maxl[y] + tree[e].length);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    cin >> s;
    for (int i = 1; i < n; ++i) {
        int a, b;
        ll t;
        cin >> a >> b >> t;
        link(a, b, t);
        link(b, a, t);
    }
    Dfs(s, 0);
    Dp(s, 0);
    cout << f[s] << endl;
    return 0;
}