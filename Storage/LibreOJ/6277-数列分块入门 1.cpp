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
        number = (number << 3) + (number << 1) + (c ^ '0');
        c = getchar();
    }
    number *= symbol;
}

constexpr int maxn = 50000 + 10;
int val[maxn], blockid[maxn], add[maxn], blocksize, n;

void modify(int l, int r, int v) {
    for (int i = l; i <= min(blockid[l] * blocksize, r); ++i)
        val[i] += v;
    if (blockid[l] != blockid[r])
        for (int i = (blockid[r] - 1) * blocksize + 1; i <= r; ++i)
            val[i] += v;
    for (int i = blockid[l] + 1; i <= blockid[r] - 1; ++i)
        add[i] += v;
}

inline int query(int x) { return val[x] + add[blockid[x]]; }

int main(int argc, char *argv[]) {
#if !defined(ONLINE_JUDGE) && FILE_IO
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
    clock_t stime = clock();
#endif
    // [ Codes ] ////////////////////////

    read(n);
    blocksize = sqrt(n);
    for (int i = 1; i <= n; ++i)
        read(val[i]);
    for (int i = 1; i <= n; ++i)
        blockid[i] = (i - 1) / blocksize + 1;
    for (int i = 1; i <= n; ++i) {
        int op, x, y, z;
        read(op);
        read(x);
        read(y);
        read(z);
        if (op)
            printf("%d\n", query(y));
        else
            modify(x, y, z);
    }

    // [ Codes ] ////////////////////////
#if !defined(ONLINE_JUDGE) && FILE_IO
    clock_t etime = clock();
    printf("\n----------------------------\n");
    printf("Time : %dms\n", static_cast<int>(etime - stime));
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