#include <bits/stdc++.h>

typedef long long ll;

constexpr int maxn = 200 + 10;
constexpr int maxq = 100000 + 10;

struct query {
    int xx, yy, x1, y1, id;
};

int n, m, q, bsize, a[maxn][maxn];
std::vector<int> tmp;
query qs[maxq];
ll cnt[maxn * maxn], res, ans[maxq];
int xx = 1, yy = 1, x, y;

template <typename T>
T square(T x) {
    return x * x;
}

void add(int x, int y) {
    ++cnt[a[x][y]];
    res = res - square(cnt[a[x][y]] - 1) + square(cnt[a[x][y]]);
}

void sub(int x, int y) {
    --cnt[a[x][y]];
    res = res - square(cnt[a[x][y]] + 1) + square(cnt[a[x][y]]);
}

void addrow(int x, int sy, int ey) {
    for (int i = sy; i <= ey; ++i)
        add(x, i);
}

void subrow(int x, int sy, int ey) {
    for (int i = sy; i <= ey; ++i)
        sub(x, i);
}

void addcol(int y, int sx, int ex) {
    for (int i = sx; i <= ex; ++i)
        add(i, y);
}

void subcol(int y, int sx, int ex) {
    for (int i = sx; i <= ex; ++i)
        sub(i, y);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("vegetable.in", "r", stdin);
    freopen("vegetable.out", "w", stdout);
#endif
    std::cin >> n >> m >> q;
    bsize = pow(n * m, 0.5) / pow(q, 0.25) + 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            std::cin >> a[i][j];
            tmp.push_back(a[i][j]);
        }
    }
    for (int i = 1; i <= q; ++i) {
        std::cin >> qs[i].xx >> qs[i].yy >> qs[i].x1 >> qs[i].y1;
        qs[i].id = i;
    }
    std::sort(tmp.begin(), tmp.end());
    tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());
    for (int i = 1; i <= n; ++i) 
        for (int j = 1; j <= m; ++j)
            a[i][j] = std::lower_bound(tmp.begin(), tmp.end(), a[i][j]) - tmp.begin() + 1;
    std::sort(qs + 1, qs + 1 + q, [](query a, query b) {
        if (a.xx / bsize != b.xx / bsize)
            return a.xx < b.xx;
        if (a.yy / bsize != b.yy / bsize)
            return a.yy < b.yy;
        if (a.x1 / bsize != b.x1 / bsize)
            return a.x1 < b.x1;
        return a.y1 < b.y1;  
    });
    for (int i = 1; i <= q; ++i) {
        while (xx > qs[i].xx)
            addrow(--xx, yy, y);
        while (x < qs[i].x1)
            addrow(++x, yy, y);
        while (yy > qs[i].yy)
            addcol(--yy, xx, x);
        while (y < qs[i].y1)
            addcol(++y, xx, x);
        
        while (xx < qs[i].xx)
            subrow(xx++, yy, y);
        while (x > qs[i].x1)
            subrow(x--, yy, y);
        while (yy < qs[i].yy)
            subcol(yy++, xx, x);
        while (y > qs[i].y1)
            subcol(y--, xx, x);
        ans[qs[i].id] = res;
    }
    for (int i = 1; i <= q; ++i)
        std::cout << ans[i] << std::endl;
    return 0;
}
