#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e5 + 10;

struct robot {
    int a, d, p;

    friend bool operator<(robot i, robot j) {
        return i.p * j.a < j.p * i.a;
    }
};

struct node {
    int x, y, ls, rs, size;
    unsigned priority; 
};

robot rbs[maxn];
int atk, n, ans;
int suma[maxn], sump[maxn];
node tree[maxn];
int uuid, root;
unsigned seed;

int calc(int i) {
    return (sump[i] - 1) * rbs[i].a + rbs[i].p * suma[i + 1];
}

inline int &ls(int x) {
    return tree[x].ls;
}

inline int &rs(int x) {
    return tree[x].rs;
}

void pushup(int x) {
    tree[x].size = tree[ls(x)].size + tree[rs(x)].size + 1;
}

unsigned myrandom() {
    return seed = ((seed + 3) * 53173 + 18543);
}

int create(int x, int y) {
    tree[++uuid] = {x, y, 0, 0, 1, myrandom()};
    return uuid;
}

void splitv(int root, int val, int &x, int &y) {
    if (!root) {
        x = y = 0;
        return;
    }
    if (tree[root].x <= val) {
        x = root;
        splitv(rs(x), val, rs(x), y);
        pushup(x);
    } else {
        y = root;
        splitv(ls(y), val, x, ls(y));
        pushup(y);
    }
}

void splits(int root, int sze, int &x, int &y) {
    if (!root) {
        x = y = 0;
        return;
    }
    if (tree[ls(x)].size + 1 <= sze) {
        x = root;
        splitv(rs(x), val, rs(x), y);
        pushup(x);
    } else {
        y = root;
        splitv(ls(y), val, x, ls(y));
        pushup(y);
    }
}

int merge(int x, int y) {
    if (!x || !y)
        return x + y;
    if (tree[x].priority > tree[y].priority) {
        rs(x) = merge(rs(x), y);
        pushup(x);
        return x;
    } else {
        ls(y) = merge(x, ls(y));
        pushup(y);
        return y;
    }
}

void insert(int x, int y) {
    int id = create(x, y);
    int rtl, rtr;
    splitv(root, x, rtl, rtr);
    int rt1, rt2, rt3;
    while (tree[rtl].size >= 2) {
        splits(rtl, tree[rtl].size - 2, rt1, rt2);
        splits(rt2, 1, rt2, rt3);
        if ((tree[rt3].y - tree[rt2].y) * (x - tree[rt3].x) < (y - tree[rt3].y) * (tree[rt3].x - tree[rt2].x)) {
            rtl = merge(merge(rt1, rt2), rt3);
            break;
        } else {
            int tmp;
            splits(rt1, tree[rt1].size - 1, rt1, tmp);
            rt3 = rt2;
            rt2 = tmp;
        }
    }
    while (tree[rtr].size >= 2) {
        splits(rtr, 1, rt1, rt2);
        splits(rt2, 1, rt2, rt3);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("ENvironment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("fittest.in", "r", stdin);
    freopen("fittest.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> atk;
    for (int i = 1; i <= n; ++i)
        cin >> rbs[i].a >> rbs[i].d, rbs[i].p = (int)ceil(1.0 * rbs[i].d / atk);
    sort(rbs + 1, rbs + 1 + n);
    for (int i = n; i >= 1; --i)
        suma[i] = suma[i + 1] + rbs[i].a;
    for (int i = 1; i <= n; ++i)
        sump[i] = sump[i - 1] + rbs[i].p;
    for (int i = 1; i <= n; ++i)
        ans += (sump[i] - 1) * rbs[i].a;
    


    return 0;
}