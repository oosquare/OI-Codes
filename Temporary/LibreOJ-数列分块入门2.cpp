#include <bits/stdc++.h>
using namespace std;

template <typename T> T read() {
    T x = 0, s = 1;
    char c = getchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * s;
}

typedef long long ll;
constexpr int maxn = 50000 + 10;
int arr[maxn], val[maxn], add[maxn], blockid[maxn], blocksize;
int n;

void modify(int l, int r, int v) {
    int ls = (blockid[l] - 1) * blocksize + 1;
    int le = blockid[l] * blocksize;
    int rs = (blockid[r] - 1) * blocksize + 1;
    int re = blockid[r] * blocksize;
    //
    for (int i = ls, p = blockid[l]; i <= le; ++i)
        arr[i] = val[i] = arr[i] + add[p];
    add[blockid[l]] = 0;
    for (int i = l, e = min(blockid[l] * blocksize, r); i <= e; ++i)
        arr[i] = (val[i] += v);
    sort(val + ls, val + le + 1);
    //
    if (blockid[l] != blockid[r]) {
        for (int i = rs, p = blockid[r]; i <= re; ++i)
            arr[i] = val[i] = arr[i] + add[p];
        add[blockid[r]] = 0;
        for (int i = (blockid[r] - 1) * blocksize + 1; i <= r; ++i)
            arr[i] = (val[i] += v);
        sort(val + rs, val + re + 1);
    }
    //
    for (int i = blockid[l] + 1, e = blockid[r] - 1; i <= e; ++i)
        add[i] += v;
}

int get(int id, ll v) {
    int l = (blockid[l] - 1) * blocksize + 1, r = blockid[id] * blocksize;
    int ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (val[mid] + add[blockid[mid]] < v) {
            ans = mid - l + 1;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}

int query(int l, int r, ll v) {
    v *= v;
    int ans = 0;
    for (int i = l, e = blockid[l] * blocksize; i <= e; ++i)
        ans += arr[i] < v;
    if (blockid[l] != blockid[r])
        for (int i = (blockid[r] - 1) * blocksize + 1; i <= r; ++i)
            ans += arr[i] < v;
    for (int i = blockid[l] + 1, e = blockid[r] - 1; i <= e; ++i) {
        if (val[i * blocksize] + add[i] <= v) {
            ans += blocksize;
            continue;
        }
        ans += get(i, v);
    }
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    n = read<int>();
    blocksize = sqrt(n);
    for (int i = 1; i <= n; ++i) {
        val[i] = arr[i] = read<int>();
        blockid[i] = (i - 1) / blocksize + 1;
    }
    for (int i = 1; i <= blockid[n]; ++i)
        sort(val + (i - 1) * blocksize + 1, val + i * blocksize + 1);
    for (int i = 1; i <= n; ++i) {
        int op = read<int>(), l = read<int>(), r = read<int>(), v = read<int>();
        if (op)
            printf("%d\n", query(l, r, v));
        else
            modify(l, r, v);
    }
    return 0;
}