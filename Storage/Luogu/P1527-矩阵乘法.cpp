#include <bits/stdc++.h>
using namespace std;

namespace IO {
    
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

template <typename T = int> void writeln(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar('\n');
}

template <typename T = int> void writesp(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar(' ');
}

template <typename T = int> void write(T x, char blank[]) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar('\n');
    for (int i = 0; blank[i] != '\0'; ++i)
        putchar(blank[i]);
}

} // namespace IO

constexpr int maxn = 500 + 10;
constexpr int oo = 0x3f3f3f3f;

struct nums {
    int x, y, v;
};

struct querys {
    int x1, y1, x2, y2, k, id;
};

vector<nums> ns;
vector<querys> qs;
int tree[maxn][maxn];
int n, m, minv = oo, maxv = -oo, ans[maxn * 1000];

int lowbit(int x) {
    return x & (-x);
}

void add(int x, int y, int v) {
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= n; j += lowbit(j))
            tree[i][j] += v;
}

int query(int x, int y) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i))
        for (int j = y; j; j -= lowbit(j))
            res += tree[i][j];
    return res;
}

int query(int x1, int y1, int x2, int y2) {
    return query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2) + query(x1 - 1, y1 - 1);
}

void init(int x, int y) {
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= n && tree[i][j]; j += lowbit(j))
            tree[i][j] = 0;
}

void BinarySolve(const vector<nums> &ns, const vector<querys> qs, int l, int r) {
    if (qs.size() == 0)
        return;
    if (l == r) {
        for (auto i : qs)
            ans[i.id] = l;
        return;
    }
    int mid = (l + r) / 2;
    vector<nums> ns1, ns2;
    vector<querys> qs1, qs2;
    for (auto i : ns) {
        if (i.v <= mid) {
            add(i.x, i.y, 1);
            ns1.push_back(i);
        } else {
            ns2.push_back(i);
        }
    }
    for (auto i : qs) {
        int t = query(i.x1, i. y1, i.x2, i.y2);
        if (i.k <= t) {
            qs1.push_back(i);
        } else {
            i.k -= t;
            qs2.push_back(i);
        }
    }
    for (auto i : ns1)
        add(i.x, i.y, -1);
    BinarySolve(ns1, qs1, l, mid);
    BinarySolve(ns2, qs2, mid + 1, r);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    using namespace IO;
    n = read(), m = read();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int a = read();
            ns.push_back({i, j, a});
            minv = min(minv, a);
            maxv = max(maxv, a);
        }
    }
    for (int i = 1; i <= m; ++i)
        qs.push_back({read(), read(), read(), read(), read(), i});
    BinarySolve(ns, qs, minv, maxv);
    for (int i = 1; i <= m; ++i)
        writeln(ans[i]);
    return 0;
}