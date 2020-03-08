#include <bits/stdc++.h>
using namespace std;

struct pt {
    double x, y;
};

struct node {
    double x, y;
    int d, l, r;
    double ml, mr, mu, md;
};

constexpr int maxn = 200010;
node tree[maxn];
double ans = 2e18;
int n;

bool cmp1(const node &a, const node &b) { return a.x < b.x; }

bool cmp2(const node &a, const node &b) { return a.y < b.y; }

inline double square(double x) { return x * x; }

inline int &ls(int x) { return tree[x].l; }

inline int &rs(int x) { return tree[x].r; }

inline double dist(int a, int b) {
    return square(tree[a].x - tree[b].x) + square(tree[a].y - tree[b].y);
}

void pushup(int x) {
    tree[x].ml = tree[x].mr = tree[x].x;
    tree[x].mu = tree[x].md = tree[x].y;
    if (ls(x)) {
        tree[x].ml = min(tree[x].ml, tree[ls(x)].ml);
        tree[x].mr = max(tree[x].mr, tree[ls(x)].mr);
        tree[x].md = min(tree[x].md, tree[ls(x)].md);
        tree[x].mu = max(tree[x].mu, tree[ls(x)].mu);
    }
    if (rs(x)) {
        tree[x].ml = min(tree[x].ml, tree[rs(x)].ml);
        tree[x].mr = max(tree[x].mr, tree[rs(x)].mr);
        tree[x].md = min(tree[x].md, tree[rs(x)].md);
        tree[x].mu = max(tree[x].mu, tree[rs(x)].mu);
    }
}

int build(int l, int r) {
    if (l > r)
        return 0;
    int mid = (l + r) >> 1;
    double ax = 0, ay = 0, vx = 0, vy = 0;
    for (int i = l; i <= r; ++i) {
        ax += tree[i].x;
        ay += tree[i].y;
    }
    ax /= 1.0 * (r - l + 1);
    ay /= 1.0 * (r - l + 1);
    for (int i = l; i <= r; ++i) {
        vx += square(tree[i].x - ax);
        vy += square(tree[i].y - ay);
    }
    if (vx > vy) {
        tree[mid].d = 1;
        nth_element(tree + l, tree + mid, tree + r + 1, cmp1);
    } else {
        tree[mid].d = 2;
        nth_element(tree + l, tree + mid, tree + r + 1, cmp2);
    }
    ls(mid) = build(l, mid - 1);
    rs(mid) = build(mid + 1, r);
    pushup(mid);
    return mid;
}

double calculate(int a, int b) {
    double res = 0;
    if (tree[b].ml > tree[a].x)
        res += square(tree[b].ml - tree[a].x);
    if (tree[b].mr < tree[a].x)
        res += square(tree[b].mr - tree[a].x);
    if (tree[b].md > tree[a].y)
        res += square(tree[b].md - tree[a].y);
    if (tree[b].mu < tree[a].y)
        res += square(tree[b].mu - tree[a].y);
    return res;
}

void query(int l, int r, int x) {
    if (l > r)
        return;
    int mid = (l + r) >> 1;
    if (mid != x)
        ans = min(ans, dist(x, mid));
    if (l == r)
        return;
    double dl = calculate(x, ls(mid)), dr = calculate(x, rs(mid));
    if (dl < ans && dr < ans) {
        if (dl < dr) {
            query(l, mid - 1, x);
            if (dr < ans)
                query(mid + 1, r, x);
        } else {
            query(mid + 1, r, x);
            if (dl < ans)
                query(l, mid - 1, x);
        }
    } else {
        if (dl < ans)
            query(l, mid - 1, x);
        if (dr < ans)
            query(mid + 1, r, x);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lf%lf", &tree[i].x, &tree[i].y);
    build(1, n);
    for (int i = 1; i <= n; ++i)
        query(1, n, i);
    printf("%.4lf\n", sqrt(ans));
    return 0;
}