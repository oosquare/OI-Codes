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

constexpr int maxn = 2e5 + 10;

typedef long long ll;

struct q {
    int val, del;
    ll ans;
};

q seq[maxn];
ll arr[maxn], rev[maxn], ans;
int n, m;

int lowbit(int x) {
    return x & (-x);
}

void add(int p, ll v) {
    for (; p <= n + 1; p += lowbit(p))
        arr[p] += v;
}

ll query(int p) {
    ll res = 0;
    for (; p; p -= lowbit(p))
        res += arr[p];
    return res;
}

bool cmp1(const q &lhs, const q &rhs) {
    return lhs.val < rhs.val;
}

bool cmp2(const q &lhs, const q &rhs) {
    return lhs.del < rhs.del;
}

void solve(int l, int r) {
    if (l + 1 == r)
        return;
    int mid = (l + r) / 2;
    solve(l, mid);
    solve(mid, r);
    int i = l + 1, j = mid + 1;
    while (i <= mid) {
        while (seq[i].val > seq[j].val && j <= r) {
            add(seq[j].del, 1);
            ++j;
        }
        seq[i].ans += query(m + 1) - query(seq[i].del);
        ++i;
    }
    i = l + 1, j = mid + 1;
    while (i <= mid) {
        while (seq[i].val > seq[j].val && j <= r) {
            add(seq[j].del, -1);
            ++j;
        }
        ++i;
    }
    i = mid, j = r;
    while (j > mid) {
        while (seq[j].val < seq[i].val && i > l) {
            add(seq[i].del, 1);
            --i;
        }
        seq[j].ans += query(m + 1) - query(seq[j].del);
        --j;
    }
    i = mid, j = r;
    while (j > mid) {
        while (seq[j].val < seq[i].val && i > l) {
            add(seq[i].del, -1);
            --i;
        }
        --j;
    }
    sort(seq + l + 1, seq + r + 1, cmp1);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    using namespace IO;
    n = read(), m = read();
    for (int i = 1; i <= n; ++i) {
        int v = read();
        rev[v] = i;
        seq[i].val = v;
    }
    for (int i = 1; i <= m; ++i) {
        int v = read();
        seq[rev[v]].del = i;
    }
    for (int i = 1; i <= n; ++i)
        if (seq[i].del == 0)
            seq[i].del = m + 1;
    for (int i = 1; i <= n; ++i) {
        ans += query(n + 1) - query(seq[i].val);
        add(seq[i].val, 1);
    }
    for (int i = 1; i <= n; ++i)
        add(seq[i].val, -1);
    solve(0, n);
    sort(seq + 1, seq + n + 1, cmp2);
    for (int i = 1; i <= m; ++i) {
        writeln(ans);
        ans -= seq[i].ans;
    }
    return 0;
}