#include <bits/stdc++.h>
using namespace std;

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T = int> T read() {
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

class GridSegmentTree {
  public:
    void build(int x, int y) {
        X = x;
        Y = y;
        //build(Root, 1, x, y, 1);
    }

    void modify(int x, int y, int v) { modify(Root, 1, X, Y, 1, x, y, v); }

    int query(int left, int right, int up, int down) {
        return query(Root, 1, X, Y, 1, left, right, up, down);
    }
  private:
    struct Node {
        int Child[4];
        int Sum;
    } Tree[1000000];
    int Root, UUID, X, Y;

    int &which(int x, int w) { return Tree[x].Child[w]; }

    void pushup(int x) {
        Tree[x].Sum = 0;
        for (int i = 0; i < 4; ++i)
            Tree[x].Sum += Tree[which(x, i)].Sum;
    }

    /*void build(int &x, int left, int right, int up, int down) {
        if (right < left || up < down)
            return;
        x = ++UUID;
        if (left == right && up == down) {
            Tree[x].Sum = arr[left][down];
            return;
        }
        int hmid = (left + right) >> 1, vmid = (up + down) >> 1;
        build(which(x, 0), left, hmid, up, vmid);
        build(which(x, 1), hmid + 1, right, up, vmid);
        build(which(x, 2), left, hmid, vmid - 1, down);
        build(which(x, 3), hmid + 1, right, vmid - 1, down);
        pushup(x);
    }*/

    void modify(int &x, int left, int right, int up, int down, int mx, int my,
                int v) {
        if (right < left || up < down)
            return;
        if (!x)
            x = ++UUID;
        if (left == right && up == down) {
            Tree[x].Sum += v;
            return;
        }
        int hmid = (left + right) >> 1, vmid = (up + down) >> 1;
        if (mx <= hmid && my >= vmid)
            modify(which(x, 0), left, hmid, up, vmid, mx, my, v);
        else if (hmid < mx && my >= vmid)
            modify(which(x, 1), hmid + 1, right, up, vmid, mx, my, v);
        else if (mx <= hmid && vmid > my)
            modify(which(x, 2), left, hmid, vmid - 1, down, mx, my, v);
        else
            modify(which(x, 3), hmid + 1, right, vmid - 1, down, mx, my, v);
        pushup(x);
    }

    int query(int x, int left, int right, int up, int down, int qleft,
              int qright, int qup, int qdown) {
        if (right < left || up < down)
            return 0;
        if (qleft <= left && right <= qright && qdown <= down && up <= qup)
            return Tree[x].Sum;
        int res = 0, hmid = (left + right) >> 1, vmid = (up + down) >> 1;
        if (qleft <= hmid && vmid <= qup)
            res += query(which(x, 0), left, hmid, up, vmid, qleft, qright, qup, qdown);
        if (hmid < qright && vmid <= qup)
            res += query(which(x, 1), hmid + 1, right, up, vmid, qleft, qright, qup, qdown);
        if (qleft <= hmid && qdown < vmid)
            res += query(which(x, 2), left, hmid, vmid - 1, down, qleft, qright, qup, qdown);
        if (hmid < qright && qdown < vmid)
            res += query(which(x, 3), hmid + 1, right, vmid - 1, down, qleft, qright, qup, qdown);
        return res;
    }
};

int n, m;
GridSegmentTree tree;

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    tree.build(n, m);
    int op, a, b, c, d;
    while (scanf("%d%d%d%d", &op, &a, &b, &c) != EOF) {
        if (op == 1) {
            tree.modify(a, b, c);
        }
        if (op == 2) {
            scanf("%d", &d);
            printf("%d\n", tree.query(a, b, c, d));
        }
    }
    return 0;
}