#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2000;

struct Roller {
    int x, y, r;
    double s;
};

int n, xt, yt, s, t, pre[maxn];
Roller roller[maxn];

long long square(long long x) {
    return x * x;
}

long long dis(int i, int j) {
    return square(roller[i].x - roller[j].x) + square(roller[i].y - roller[j].y);
}

bool connected(int i, int j) {
    return dis(i, j) == square(roller[i].r + roller[j].r);
}

void dfs(int x, int fa) {
    for (int y = 1; y <= n; ++y) {
        if (y == x || y == fa)
            continue;
        if (connected(x, y) == false)
            continue;
        pre[y] = x;
        dfs(y, x);
    }
}

double calc(int x) {
    if (pre[x] == 0) {
        roller[x].s = 10000;
        return roller[x].s;
    }
    auto res = calc(pre[x]);
    roller[x].s = roller[pre[x]].s * roller[pre[x]].r / roller[x].r;
    return res + roller[x].s;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> xt >> yt;
    for (int i = 1; i <= n; ++i) {
        auto &[x, y, r, a] = roller[i];
        cin >> x >> y >> r;
        if (x == 0 && y == 0)
            s = i;
        if (x == xt && y == yt)
            t = i;
    }
    dfs(s, 0);
    cout << (int)calc(t) << endl;
    return 0;
}