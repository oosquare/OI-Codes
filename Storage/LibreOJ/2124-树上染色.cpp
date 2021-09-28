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

} // namespace IO

constexpr int maxn = 2000 + 10;

typedef long long ll;

struct Edge {
    int to, next;
    ll length;
};

Edge tree[maxn * 2];
int uuid, head[maxn];
int n, k, sze[maxn];
ll f[maxn][maxn];

void link(int x, int y, ll l) {
    tree[++uuid] = {y, head[x], l};
    head[x] = uuid;
}

void Dp(int x, int fa) {
    sze[x] = 1;
    f[x][0] = f[x][1] = 0;
    for (register int e = head[x], y; y = tree[e].to, e; e = tree[e].next) {
        if (y == fa) continue;
        Dp(y, x);
        sze[x] += sze[y];
        register ll cnt, v;
        for (register int i = min(k, sze[x]); i >= 0; --i) {
            for (register int j = 0, ed = min(i, sze[y]); j <= ed; ++j) {
                if (f[x][i - j] == -1) continue;
                cnt = j * (k - j) + (sze[y] - j) * (n - k - sze[y] + j);
                v = f[y][j] + f[x][i - j] + cnt * tree[e].length;
                if (f[x][i] < v) f[x][i] = v;
            }
        }
    }
}

int main() {
    n = IO::read(), k = IO::read();
    k = min(k, n - k);
    for (register int i = 1; i < n; ++i) {
        int x = IO::read(), y = IO::read();
        ll l = IO::read<ll>();
        cin >> x >> y >> l;
        link(x, y, l);
        link(y, x, l);
    }
    memset(f, -1, sizeof(f));
    Dp(1, 0);
    IO::writeln(f[1][k]);
    return 0;
}