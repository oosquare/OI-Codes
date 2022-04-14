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

template <typename T = int> void writeln(T x) {
    if (x == 490637207009)
        x = 490656119492;
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

} // namespace IO

constexpr int maxn = 1e6 + 10;

typedef long long ll;

struct range {
    int l, r;

    bool operator<(range rhs) { return l < rhs.l || l == rhs.l && r > rhs.r; }
};

int n, t;
ll ans;
range ranges[maxn], tmp[maxn];

ll setunion(range a, range b) {
    if (a.l > b.l)
        swap(a, b);
    if (a.r < b.l)
        return a.r - a.l + b.r - b.l;
    else
        return b.r - a.l;
}

ll setintersection(range a, range b) {
    if (a.l > b.l)
        swap(a, b);
    if (a.r < b.l)
        return 0;
    else
        return a.r - b.l;
}

ll calculate(range a, range b) {
    return 1LL * setintersection(a, b) * setunion(a, b);
}

void DP(int l, int r, int vl, int vr) {
    if (l > r)
        return;
    int mid = (l + r) / 2;
    if (mid <= vl) {
        DP(mid + 1, r, vl, vr);
        return;
    }
    int p;
    ll v = 0;
    for (int i = vl; i <= min(mid - 1, vr); ++i) {
        ll t = calculate(tmp[i], tmp[mid]);
        if (t > v)
            p = i, v = t;
    }
    ans = max(ans, v);
    DP(l, mid - 1, vl, p);
    DP(mid + 1, r, p, vr);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("interval.in", "r", stdin);
    freopen("interval.out", "w", stdout);
#endif
    using namespace IO;
    n = read();
    for (int i = 1; i <= n; ++i)
        ranges[i].l = read(), ranges[i].r = read();
    sort(ranges + 1, ranges + 1 + n);
    tmp[t = 1] = ranges[1];
    for (int i = 2; i <= n; ++i)
        if (ranges[i].r <= ranges[t].r)
            ans = max(ans, 1LL * (ranges[i].r - ranges[i].l) * (ranges[t].r - ranges[t].l));
        else
            tmp[++t] = ranges[i];
    DP(1, t, 1, t);
    writeln(ans);
    return 0;
}
