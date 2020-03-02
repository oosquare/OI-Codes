#include <bits/stdc++.h>
using namespace std;

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

struct Edge
{
    int To, Next;
};

struct Node 
{
    int Left, Right;
    long long Sum, Ans;
};

const int maxn = 2e6 + 10;

Node segtree[5000050];
Edge tree[maxn << 1]; int head[maxn];
int n, total, segtotal;
int root[maxn], color[maxn];
long long ans[maxn];

inline void pushup(int x) {
    if (segtree[segtree[x].Left].Sum > segtree[segtree[x].Right].Sum) {
        segtree[x].Sum = segtree[segtree[x].Left].Sum;
        segtree[x].Ans = segtree[segtree[x].Left].Ans;
    } else if (segtree[segtree[x].Left].Sum < segtree[segtree[x].Right].Sum) {
        segtree[x].Sum = segtree[segtree[x].Right].Sum;
        segtree[x].Ans = segtree[segtree[x].Right].Ans;
    } else {
        segtree[x].Sum = segtree[segtree[x].Left].Sum;
        segtree[x].Ans = segtree[segtree[x].Left].Ans + segtree[segtree[x].Right].Ans;
    }
}

void modify(int &x, int l, int r, int p, int v) {
    if (x == 0)
        x = ++segtotal;
    if (l == r && r == p) {
        segtree[x].Sum += v;
        segtree[x].Ans = l;
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) 
        modify(segtree[x].Left, l, mid, p, v);    
    else
        modify(segtree[x].Right, mid + 1, r, p, v);
    pushup(x);
}

int merge(int x, int y, int l, int r) {
    if (x == 0 || y == 0)
        return x + y;
    if (l == r) {
        segtree[x].Sum += segtree[y].Sum;
        segtree[x].Ans = l;
        return x;
    }
    int mid = (l + r) >> 1;
    segtree[x].Left = merge(segtree[x].Left, segtree[y].Left, l, mid);
    segtree[x].Right = merge(segtree[x].Right, segtree[y].Right, mid + 1, r);
    pushup(x);
    return x;
}

void link(int x, int y) {
    tree[++total] = (Edge){y, head[x]}; head[x] = total;
    tree[++total] = (Edge){x, head[y]}; head[y] = total;
}

void DFS(int x, int fa) {
    for (int i = head[x], y; y = tree[i].To, i; i = tree[i].Next) {
        if (y == fa)
            continue;
        DFS(y, x);
        merge(root[x], root[y], 1, 100000);
    }
    modify(root[x], 1, 100000, color[x], 1);
    ans[x] = segtree[root[x]].Ans;
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
    clock_t stime = clock();
#endif
    // [ Codes ] ////////////////////////
    
    read(n);
    for (int i = 1; i <= n; ++i) {
        read(color[i]);
        root[i] = ++segtotal;
    }
    for (int i = 1; i < n; ++i) {
        int x, y;
        read(x); read(y);
        link(x, y);
    }

    DFS(1, 0);
    for(int i = 1; i <= n; ++i) {
        printf("%lld ", ans[i]);
    }
    printf("\n");

    // [ Codes ] ////////////////////////
#ifndef ONLINE_JUDGE
    clock_t etime = clock();
    printf("\n-----------------\n")
    printf("Time : %dms\n", etime - stime);
    if (etime - stime >= 1000)
        printf("<<< Warning >>> Time Limited Exceeded\n");
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
