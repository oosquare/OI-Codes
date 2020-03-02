#include <bits/stdc++.h>
using namespace std;

template <typename T> void read(T &number) {
    number = 0;
    int symbol = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-')
            symbol *= -1;
        c = getchar();
    }
    while (isdigit(c)) {
        number = (number << 3) + (number << 1) + c - '0';
        c = getchar();
    }
    number *= symbol;
}

template <typename T, int MaxSize> class SegmentTree {
  public:
    void init(int n) { Size = n; }

    void build(T arr[]) { build(1, 1, Size, arr); }

    void modify(int left, int right, T key) {
        modify(1, 1, Size, left, right, key);
    }

    T query(int left, int right) { return query(1, 1, Size, left, right); }

  private:
    struct Node {
        T Add, Sum;
    } Tree[MaxSize];
    int Size;

    void pushup(int root) {
        Tree[root].Sum = Tree[root << 1].Sum + Tree[root << 1 | 1].Sum;
    }

    void update(int root, int left, int right, T key) {
        Tree[root].Add = key;
        Tree[root].Sum = key * (right - left + 1);
    }

    void pushdown(int root, int left, int right) {
        if (Tree[root].Add == 0)
            return;
        int mid = left + right >> 1;
        update(root << 1, left, mid, Tree[root].Add);
        update(root << 1 | 1, mid + 1, right, Tree[root].Add);
        Tree[root].Add = 0;
    }

    void build(int root, int left, int right, T arr[]) {
        if (left == right) {
            Tree[root].Sum = arr[left];
            return;
        }
        int mid = left + right >> 1;
        build(root << 1, left, mid, arr);
        build(root << 1 | 1, mid + 1, right, arr);
        pushup(root);
    }

    void modify(int root, int left, int right, int mleft, int mright, T key) {
        if (mleft <= left && right <= mright) {
            update(root, left, right, key);
            return;
        }
        int mid = left + right >> 1;
        pushdown(root, left, right);
        if (mleft <= mid)
            modify(root << 1, left, mid, mleft, mright, key);
        if (mid < mright)
            modify(root << 1 | 1, mid + 1, right, mleft, mright, key);
        pushup(root);
    }

    T query(int root, int left, int right, int qleft, int qright) {
        if (qleft <= left && right <= qright)
            return Tree[root].Sum;
        int mid = left + right >> 1;
        pushdown(root, left, right);
        T res = 0;
        if (qleft <= mid)
            res += query(root << 1, left, mid, qleft, qright);
        if (mid < qright)
            res += query(root << 1 | 1, mid + 1, right, qleft, qright);
        return res;
    }
};

struct Platform {
    int Height, Left, Right;
    bool operator<(const Platform &rhs) { return Height < rhs.Height; }
};

const int maxn = 1000000 + 10;

SegmentTree<int, maxn << 2> tree;
Platform pl[maxn];
int nxt[maxn][2], nxtForAns;
int f[maxn][2];
int n, maxHeight, maxRight, startX, startY, ans;

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
    clock_t stime = clock();
#endif
    // [ Codes ] ////////////////////////

    read(n);
    read(maxHeight);
    read(startX);
    read(startY);
    for (int i = 1; i <= n; ++i) {
        read(pl[i].Height);
        read(pl[i].Left);
        read(pl[i].Right);
        maxRight = max(maxRight, pl[i].Right);
    }

    sort(pl + 1, pl + 1 + n);
    tree.init(maxRight);
    for (int i = 1; i <= n; ++i) {
        nxt[i][0] = tree.query(pl[i].Left, pl[i].Left);
        if (pl[i].Height - pl[nxt[i][0]].Height > maxHeight)
            nxt[i][0] = n + 1;
        nxt[i][1] = tree.query(pl[i].Right, pl[i].Right);
        if (pl[i].Height - pl[nxt[i][1]].Height > maxHeight)
            nxt[i][1] = n + 1;
        tree.modify(pl[i].Left, pl[i].Right, i);
    }
    nxtForAns = tree.query(startX, startX);
    f[n + 1][0] = f[n + 1][1] = 0x3f3f3f3f;

    for (int i = 1; i <= n; ++i) {
        int j = nxt[i][0], k = nxt[i][1];
        if (j == 0)
            f[i][0] = min(f[j][0] + pl[i].Height, f[j][1] + pl[i].Height);
        else
            f[i][0] = min(f[j][0] + pl[i].Left - pl[j].Left + pl[i].Height -
                              pl[j].Height,
                          f[j][1] + pl[j].Right - pl[i].Left + pl[i].Height -
                              pl[j].Height);
        if (k == 0)
            f[i][1] = min(f[k][0] + pl[i].Height, f[k][1] + pl[i].Height);
        else
            f[i][1] = min(f[k][0] + pl[i].Right - pl[k].Left + pl[i].Height -
                              pl[k].Height,
                          f[k][1] + pl[k].Right - pl[i].Right + pl[i].Height -
                              pl[k].Height);
    }

    ans = startY - pl[nxtForAns].Height;
    ans += min(f[nxtForAns][0] + startX - pl[nxtForAns].Left,
               f[nxtForAns][1] + pl[nxtForAns].Right - startX);
    printf("%d\n", ans);

    // [ Codes ] ////////////////////////
#ifndef ONLINE_JUDGE
    clock_t etime = clock();
    printf("Time : %dms", etime - stime);
    if (etime - stime >= 1000) {
        printf("Warning : Time Limited Exceeded\n");
    }
#endif
    return 0;
}

//
//        ^ y
//       1|                            y = sin x (0 < x < 2π)
//  - - - | - - - + - - - - - - - - - - - - - -
//        |  +         +
// -------+---------------+---------------+----------> x
//       O|               π  +         +  2π
//  - - - | - - - - - - - - - - - + - - - - - -
//      -1|
//        |
//
