#include <bits/stdc++.h>
#define FILE_IO true
#define TIME_LIMIT 1000
using namespace std;

template <typename T> T read() {
    T number = 0;
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
    return number * symbol;
}

struct node {
    int l, r, sum;
};

const int maxn = 100000 + 5;
node tree[maxn << 6];
int root[maxn], uuid;
int arr[maxn], n, m;
vector<int> mapping;

inline int &ls(int x) { return tree[x].l; }

inline int &rs(int x) { return tree[x].r; }

void insert(int &x, int y, int l, int r, int v) {
    tree[x = ++uuid] = tree[y];
    ++tree[x].sum;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (v <= mid)
        insert(ls(x), ls(y), l, mid, v);
    else
        insert(rs(x), rs(y), mid + 1, r, v);
}

int query(int x, int y, int l, int r, int rk) {
    if (l == r)
        return l;
    int tmp = tree[ls(x)].sum - tree[ls(y)].sum;
    int mid = (l + r) >> 1;
    if (rk <= tmp)
        return query(ls(x), ls(y), l, mid, rk);
    else
        return query(rs(x), rs(y), mid + 1, r, rk - tmp);
}

inline int getid(int x) {
    return lower_bound(mapping.begin(), mapping.end(), x) - mapping.begin() + 1;
}

int main(int argc, char *argv[]) {
#if !defined(ONLINE_JUDGE) && FILE_IO
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
    clock_t stime = clock();
#endif
    // [ Codes ] ////////////////////////

    n = read<int>();
    m = read<int>();
    for (int i = 1; i <= n; ++i)
        mapping.push_back(arr[i] = read<int>());
    sort(mapping.begin(), mapping.end());
    mapping.erase(unique(mapping.begin(), mapping.end()), mapping.end());
    for (int i = 1; i <= n; ++i)
        insert(root[i], root[i - 1], 1, n, getid(arr[i]));
    while (m--) {
        int l = read<int>(), r = read<int>(), k = read<int>();
        printf("%d\n", mapping[query(root[r], root[l - 1], 1, n, k) - 1]);
    }

    // [ Codes ] ////////////////////////
#if !defined(ONLINE_JUDGE) && FILE_IO
    clock_t etime = clock();
    printf("\n----------------------------\n");
    printf("Time : %dms\n", (int)(etime - stime));
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
