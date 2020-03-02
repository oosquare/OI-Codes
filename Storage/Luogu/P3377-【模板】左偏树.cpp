#include <bits/stdc++.h>
#define FILE_IO true
#define TIME_LIMIT 1000
using namespace std;

template <typename T> void read(T &number) {
    number = 0;
    int symbol = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-')
            symbol *= -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        number = (number << 3) + (number << 1) + c ^ '0';
        c = getchar();
    }
    number *= symbol;
}

struct node {
    int l, r, v, d, fa;
};

const int maxn = 100000 + 10;
node heap[maxn << 4];
int tot, root[maxn];
int n, m;

int merge(int x, int y) {
    if (!x || !y)
        return x ^ y;
    if ((heap[x].v > heap[y].v) || (heap[x].v == heap[y].v && x > y))
        swap(x, y);
    heap[x].r = merge(heap[x].r, y);
    if (heap[heap[x].l].d < heap[heap[x].r].d)
        swap(heap[x].l, heap[x].r);
    heap[x].d = heap[heap[x].r].d + 1;
    heap[x].fa = heap[heap[x].l].fa = heap[heap[x].r].fa = x;
    return x;
}

void pop(int x) {
    heap[x].v = -1;
    heap[heap[x].l].fa = heap[x].l;
    heap[heap[x].r].fa = heap[x].r;
    heap[x].fa = merge(heap[x].l, heap[x].r);
}

int find(int x) { return x == heap[x].fa ? x : heap[x].fa = find(heap[x].fa); }

int main(int argc, char *argv[]) {
#if !defined(ONLINE_JUDGE) && FILE_IO
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
    clock_t stime = clock();
#endif
    // [ Codes ] ////////////////////////

    read(n);
    read(m);
    heap[0].d = -1;
    for (int i = 1; i <= n; ++i) {
        int x;
        read(x);
        heap[i].v = x;
        heap[i].fa = i;
    }
    while (m--) {
        int opt, x, y;
        read(opt);
        if (opt == 1) {
            read(x);
            read(y);
            if (heap[x].v == -1 || heap[y].v == -1)
                continue;
            int fx = find(x), fy = find(y);
            if (fx != fy)
                heap[fx].fa = heap[fy].fa = merge(fx, fy);
        } else {
            read(x);
            if (heap[x].v == -1)
                printf("-1\n");
            else {
                printf("%d\n", heap[find(x)].v);
                pop(find(x));
            }
        }
    }

    // [ Codes ] ////////////////////////
#if !defined(ONLINE_JUDGE) && FILE_IO
    clock_t etime = clock();
    printf("\n----------------------------\n");
    printf("Time : %dms\n", etime - stime);
    if (etime - stime >= TIME_LIMIT) {
        printf("<<< Warning >>> Time Limited Exceeded\n");
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
