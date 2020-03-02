#include <bits/stdc++.h>
using namespace std;

const int maxn = 10001, maxm = 101, mod = 123456789;

int a[maxn], b[maxn], c[maxm][maxn], n, m;
int f[maxn][maxm];

inline int lowbit(int x) { return -x & x; }

inline void modify(int id, int pos, int val) {
    for (; pos <= maxn; pos += lowbit(pos)) {
        c[id][pos] = ((long long)c[id][pos] + val) % mod;
    }
}

inline int query(int id, int pos) {
    int ans = 0;
    for (; pos; pos -= lowbit(pos)) {
        ans = ((long long)ans + c[id][pos]) % mod;
    }
    return ans;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(c, 0, sizeof(c));
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            b[i] = a[i];
        }
        sort(b + 1, b + 1 + n);
        int len = unique(b + 1, b + 1 + n) - b - 1;
        for (int i = 1; i <= n; ++i) {
            a[i] = lower_bound(b + 1, b + 1 + len, a[i]) - b;
        }
        for (int i = 1; i <= n; ++i) {
            modify(1, a[i], 1);
            for (int j = 1; j < m; ++j) {
                int res = query(j, a[i] - 1);
                if (!res)
                    break;
                modify(j + 1, a[i], res);
            }
        }
        printf("%d\n", (int)(query(m, maxn) % mod));
    }
    return 0;
}