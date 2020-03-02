#include <bits/stdc++.h>
using namespace std;

template <typename T, int MaxSize>
class SegmentTree 
{
public:
    void init(int n) { Size = n; }

    void build(T arr[]) { build(1, 1, Size, arr); }

    void modify(int left, int right, T key) { modify(1, 1, Size, left, right, key); }

    T query(int left, int right) { return query(1, 1, Size, left, right); }

private:
    struct Node 
    {
        T Add, Sum;
    } Tree[MaxSize << 2];
    int Size;

    void pushup(int root) { Tree[root].Sum = Tree[root << 1].Sum + Tree[root << 1 | 1].Sum; }

    void update(int root, int left, int right, T key) {
        Tree[root].Add += key;
        Tree[root].Sum += key * (right - left + 1);
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

template <typename T>
void read(T &number) {
    number = 0; int symbol = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-') symbol *= -1;
        c = getchar();
    }
    while (isdigit(c)) {
        number = (number << 3) + (number << 1) + c - '0';
        c = getchar();
    }
    number *= symbol;
}

const int maxn=100000 + 10;

SegmentTree<int, maxn> tree;
int n, m, a[maxn];

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
    clock_t stime = clock();
#endif
    // [ Codes] ////////////////////////
    
    read(n); read(m);
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
    }
    tree.init(n);
    for (int i = 1; i <= m; ++i) {
        int t;
        read(t);
        if (t == 1) {
            int l, r, k, d;
            read(l); read(r); read(k); read(d);
            tree.modify(l, l, k);
            if (l < r) tree.modify(l + 1, r, d);
            if (r != n) tree.modify(r + 1, r + 1, -(k + (r - l) * d));
        } else {
            int p;
            read(p);
            printf("%d\n", a[p] + tree.query(1, p));
        }
    }

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
//        |                            y = sin x (0 < x < 2π)
//  - -  1| - - - + - - - - - - - - - - - - - -
//        |  +         +
// -------+---------------+---------------+----------> x
//       O|               π  +         +  2π
//  - - -1| - - - - - - - - - - - + - - - - - -
//        |
//        |
//
