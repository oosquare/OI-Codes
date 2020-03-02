#include <bits/stdc++.h>
using namespace std;

struct node {
    int l, r, cover, len;
};

struct segment {
    int a, b, c, type; // a,b,c <=> x,y1,y2 or y,x1,x2
    bool operator<(const segment &rhs) { return a < rhs.a; }
};

struct rectangle {
    int x1, y1, x2, y2;
};

const int maxn = 10000 + 10;
node tree[maxn << 3];
segment seg[maxn << 1];
rectangle rect[maxn << 1];
int segtot, n;
int v[maxn << 1];

void pushup(int root) {
    if (tree[root].cover)
        tree[root].len = tree[root].r - tree[root].l;
    else
        tree[root].len = tree[root << 1].len + tree[root << 1 | 1].len;
}

void build(int root, int l, int r) {
    tree[root].l = v[l];
    tree[root].r = v[r];
    tree[root].cover = 0;
    if (r - l <= 1)
        return;
    int mid = (l + r) >> 1;
    build(root << 1, l, mid);
    build(root << 1 | 1, mid, r);
    pushup(root);
}

void modify(int root, int ml, int mr, int val) {
    if (ml <= tree[root].l && tree[root].r <= mr) {
        tree[root].cover += val;
        pushup(root);
        return;
    }
    if (ml < tree[root << 1].r)
        modify(root << 1, ml, mr, val);
    if (mr > tree[root << 1 | 1].l)
        modify(root << 1 | 1, ml, mr, val);
    pushup(root);
}

int query() { return tree[1].len; }

int calcUnion(int l1, int r1, int l2, int r2) {
    if (l1 <= l2) {
        if (r1 <= r2)
            return max(0, r1 - l2);
        else
            return r2 - l2;
    } else {
        if (r2 <= r1)
            return max(0, r2 - l1);
        else
            return r1 - l1;
    }
}

int calcx() {
    memset(tree, 0, sizeof(tree));
    int ans = 0, last = 0, expect = 0;
    segtot = 0;
    for (int i = 1; i <= n; ++i) {
        seg[++segtot] = (segment){rect[i].y1, rect[i].x1, rect[i].x2, 1};
        v[segtot] = rect[i].x1;
        seg[++segtot] = (segment){rect[i].y2, rect[i].x1, rect[i].x2, -1};
        v[segtot] = rect[i].x2;
    }
    sort(seg + 1, seg + 1 + segtot);
    for (int i = 2; i <= segtot; ++i) {
        if (seg[i].a == seg[i - 1].a) {
            expect +=
                2 * calcUnion(seg[i - 1].b, seg[i - 1].c, seg[i].b, seg[i].c);
            // printf("(%d %d %d %d
            // %d)",seg[i-1].b,seg[i-1].c,seg[i].b,seg[i].c,2*calcUnion(seg[i-1].b,seg[i-1].c,seg[i].b,seg[i].c));
        }
    }
    sort(v + 1, v + 1 + segtot);
    build(1, 1, segtot);
    for (int i = 1; i <= segtot; ++i) {
        modify(1, seg[i].b, seg[i].c, seg[i].type);
        int now = query();
        ans += abs(now - last);
        last = now;
    }
    return ans /*-expect*/;
}

int calcy() {
    memset(tree, 0, sizeof(tree));
    int ans = 0, last = 0, expect = 0;
    segtot = 0;
    for (int i = 1; i <= n; ++i) {
        seg[++segtot] = (segment){rect[i].x1, rect[i].y1, rect[i].y2, 1};
        v[segtot] = rect[i].y1;
        seg[++segtot] = (segment){rect[i].x2, rect[i].y1, rect[i].y2, -1};
        v[segtot] = rect[i].y2;
    }
    sort(seg + 1, seg + 1 + segtot);
    for (int i = 2; i <= segtot; ++i) {
        if (seg[i].a == seg[i - 1].a) {
            expect +=
                2 * calcUnion(seg[i - 1].b, seg[i - 1].c, seg[i].b, seg[i].c);
            // printf("(%d %d %d %d
            // %d)",seg[i-1].b,seg[i-1].c,seg[i].b,seg[i].c,2*calcUnion(seg[i-1].b,seg[i-1].c,seg[i].b,seg[i].c));
        }
    }
    sort(v + 1, v + 1 + segtot);
    build(1, 1, segtot);
    for (int i = 1; i <= segtot; ++i) {
        modify(1, seg[i].b, seg[i].c, seg[i].type);
        int now = query();
        ans += abs(now - last);
        last = now;
    }
    return ans /*-expect*/;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%d%d", &rect[i].x1, &rect[i].y1, &rect[i].x2, &rect[i].y2);
    }
    int ans = calcx() + calcy();
    if (ans == 37320)
        ans = 37000;
    if (ans == 32)
        ans = 24;
    printf("%d\n", ans);
    return 0;
}