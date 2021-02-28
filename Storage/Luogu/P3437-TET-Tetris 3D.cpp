#include <bits/stdc++.h>
using namespace std;

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T = int>
T read() {
    T x = 0, s = 1;
    char c = mygetchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = mygetchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = mygetchar();
    }
    return x * s;
}

int n, m;

struct InSegmentTree {
    int maxv[3005], al[3005];

    int query(int x, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return maxv[x];
        int res = al[x], mid = (l + r) >> 1;
        if (ql <= mid)
            res = max(res, query(x << 1, l, mid, ql, qr));
        if (mid < qr)
            res = max(res, query(x << 1 | 1, mid + 1, r, ql, qr));
        return res;
    }

    void modify(int x, int l, int r, int ml, int mr, int v) {
        maxv[x] = max(maxv[x], v);
        if (ml <= l && r <= mr) {
            al[x] = max(al[x], v);
            return;
        }
        int mid = (l + r) >> 1;
        if (ml <= mid)
            modify(x << 1, l, mid, ml, mr, v);
        if (mid < mr)
            modify(x << 1 | 1, mid + 1, r, ml, mr, v);
    }
};

struct OutSegmentTree {
    InSegmentTree maxv[3005], al[3005];

    int query(int x, int l, int r, int oql, int oqr, int iql, int iqr) {
        if (oql <= l && r <= oqr)
            return maxv[x].query(1, 1, m, iql, iqr);
        int res = al[x].query(1, 1, m, iql, iqr), mid = (l + r) >> 1;
        if (oql <= mid)
            res = max(res, query(x << 1, l, mid, oql, oqr, iql, iqr));
        if (mid < oqr)
            res = max(res, query(x << 1 | 1, mid + 1, r, oql, oqr, iql, iqr));
        return res;
    }

    void modify(int x, int l, int r, int oml, int omr, int iml, int imr,
                int v) {
        maxv[x].modify(1, 1, m, iml, imr, v);
        if (oml <= l && r <= omr) {
            al[x].modify(1, 1, m, iml, imr, v);
            return;
        }
        int mid = (l + r) >> 1;
        if (oml <= mid)
            modify(x << 1, l, mid, oml, omr, iml, imr, v);
        if (mid < omr)
            modify(x << 1 | 1, mid + 1, r, oml, omr, iml, imr, v);
    }
};

OutSegmentTree tree;

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read();
    m = read();
    int q = read(), d, s, w, x, y;
    while (q--) {
        d = read();
        s = read();
        w = read();
        x = read();
        y = read();
        tree.modify(1, 1, n, x + 1, x + d, y + 1, y + s,
                    tree.query(1, 1, n, x + 1, x + d, y + 1, y + s) + w);
    }
    printf("%d\n", tree.query(1, 1, n, 1, n, 1, m));
    return 0;
}