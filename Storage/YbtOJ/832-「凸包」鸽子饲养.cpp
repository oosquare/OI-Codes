#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 10;
const int maxm = 500 + 10;

typedef long long ll;

struct point {
    ll x, y;

    point() {}
    point(int X, int Y) : x(X), y(Y) {}

    point operator+(point const rhs) const {
        return point(x + rhs.x, y + rhs.y);
    }

    point operator-(point const rhs) const {
        return point(x - rhs.x, y - rhs.y);
    }

    point operator*(ll const k) const { return point(x * k, y * k); }

    ll operator^(point const rhs) const { return x * rhs.y - y * rhs.x; }
} ps1[maxm], ps2[maxn];

struct gerham {
    point p[maxn];
    int tot;

    bool inside(point ps2) {
        bool ret = 0;

        for (int i = 1; i < tot; ++i)
            ret ^= (p[i].y - ps2.y >= 0 && p[i + 1].y - ps2.y < 0) ||
                   (p[i].y - ps2.y < 0 && p[i + 1].y - ps2.y >= 0);

        return ret;
    }
} ch;

bool cmp1(int x, int y) {
    return ps2[y].x - ps2[x].x > 0 ||
           ps2[x].x == ps2[y].x && ps2[y].y - ps2[x].y > 0;
}

bool cmp2(int x, int y) {
    return ps2[x].x - ps2[y].x > 0 ||
           ps2[x].x == ps2[y].x && ps2[x].y - ps2[y].y > 0;
}

int kth[maxn], stk[maxn];
bool able[maxm][maxm];
int f[maxm][maxm];
int n, m, ans, top;

void ckmin(int &x, int y) { x = x < y ? x : y; }

void get() {
    for (int i = 1; i <= n; ++i)
        kth[i] = i;

    sort(kth + 1, kth + 1 + n, cmp1);
    top = 0;

    for (int i = 1; i <= n; ++i) {
        point p = ps2[kth[i]];

        for (; top > 1 && ((ps2[stk[top]] - ps2[stk[top - 1]]) ^
                           (p - ps2[stk[top - 1]])) <= 0;
             --top)
            ;

        stk[++top] = kth[i];
    }

    for (int i = 1; i <= top; ++i)
        ch.p[++ch.tot] = ps2[stk[i]];

    for (int i = 1; i <= n; ++i)
        kth[i] = i;

    sort(kth + 1, kth + 1 + n, cmp2);
    top = 0;

    for (int i = 1; i <= n; ++i) {
        point p = ps2[kth[i]];

        for (; top > 1 && ((ps2[stk[top]] - ps2[stk[top - 1]]) ^
                           (p - ps2[stk[top - 1]])) <= 0;
             --top)
            ;

        stk[++top] = kth[i];
    }

    for (int i = 2; i <= top; ++i)
        ch.p[++ch.tot] = ps2[stk[i]];
}

void preprocess() {
    for (int i = 1; i <= m; ++i) {
        if (ch.inside(ps1[i]))
            continue;

        point v1 = ch.p[1] - ps1[i], v2 = ch.p[1] - ps1[i];

        for (int j = 2; j <= ch.tot; ++j) {
            point v = ch.p[j] - ps1[i];

            if (!v.x && !v.y)
                continue;

            if (!v1.x && !v1.y || (v ^ v1) > 0)
                v1 = v;

            if (!v2.x && !v2.y || (v2 ^ v) > 0)
                v2 = v;
        }

        v2 = v2 * (-1.0);

        for (int j = 1; j <= m; ++j) {
            point v = ps1[j] - ps1[i];

            if (i != j)
                able[i][j] = (v ^ v1) >= 0 && (v2 ^ v) >= 0;
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("lo.in", "r", stdin);
    freopen("lo.out", "w", stdout);
#endif
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        int x, y;
        cin >> x >> y, ps2[i] = {x, y};
    }

    for (int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y, ps1[i] = {x, y};
    }

    get();
    preprocess();

    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= m; ++j)
            f[i][j] = m * 2;

    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= m; ++j)
            if (able[i][j])
                f[i][j] = 1;

    for (int k = 1; k <= m; ++k)
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= m; ++j)
                ckmin(f[i][j], f[i][k] + f[k][j]);

    ans = m * 2;

    for (int i = 1; i <= m; ++i)
        ckmin(ans, f[i][i]);

    if (ans == m * 2)
        ans = -1;

    printf("%d\n", ans);

    return 0;
}
