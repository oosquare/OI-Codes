#include <bits/stdc++.h>
using namespace std;

struct line {
    double k, b;
    double operator()(int x) const { return k * (x - 1) + b; }
};

const int maxn = 100000 + 10;
line tree[maxn << 2];
int n;
char cmd[10];

void insert(int root, int l, int r, const line &f) {
    if (f(l) > tree[root](l) && f(r) > tree[root](r)) {
        tree[root] = f;
        return;
    }
    if (f(l) <= tree[root](l) && f(r) <= tree[root](r)) {
        return;
    }
    int mid = (l + r) >> 1;
    if (f.k > tree[root].k) {
        if (f(mid) > tree[root](mid)) {
            insert(root << 1, l, mid, tree[root]);
            tree[root] = f;
        } else {
            insert(root << 1 | 1, mid + 1, r, f);
        }
    } else {
        if (f(mid) > tree[root](mid)) {
            insert(root << 1 | 1, mid + 1, r, tree[root]);
            tree[root] = f;
        } else {
            insert(root << 1, l, mid, f);
        }
    }
}

double query(int root, int l, int r, int x) {
    if (l == r && r == x)
        return tree[root](x);
    int mid = (l + r) / 2;
    if (x <= mid)
        return max(tree[root](x), query(root << 1, l, mid, x));
    else
        return max(tree[root](x), query(root << 1 | 1, mid + 1, r, x));
}

int main() {
    scanf("%d", &n);
    while (n--) {
        scanf("%s", cmd);
        if (cmd[0] == 'P') {
            line l;
            scanf("%lf%lf", &l.b, &l.k);
            insert(1, 1, 50005, l);
        } else {
            int x;
            scanf("%d", &x);
            printf("%d\n", (int)(query(1, 1, 50005, x) / 100));
        }
    }
    return 0;
}
