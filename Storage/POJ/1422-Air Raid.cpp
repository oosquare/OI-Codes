#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

namespace IO {
    
inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T> T read() {
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

template <typename T> void writeln(T x) {
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

const int maxn = 120 + 10;

struct e {
    int to, next;
};

e edge[maxn * maxn * 10];
int head[maxn * 2], uuid;
int t, n, m, ans, match[maxn * 2], vis[maxn * 2];

void link(int x, int y) {
    edge[++uuid] = {y, head[x]};
    head[x] = uuid;
}

bool find(int x) {
    for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
        if (vis[y])
            continue;
        vis[y] = true;
        if (!match[y] || find(match[y])) {
            match[y] = x;
            return true;
        }
    }
    return false;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    using namespace IO;
    t = read<int>();
    for (int T = 1; T <= t; ++T) {
        memset(head, 0, sizeof(head));
        memset(match, 0, sizeof(match));
        uuid = ans= 0;
        n = read<int>();
        m = read<int>();
        for (int i = 1; i <= m; ++i) {
            int x = read<int>(), y = read<int>();
            link(x, y + n);
            link(y + n, x);
        }
        for (int i = 1; i <= n; ++i) {
            memset(vis, 0, sizeof(vis));
            if (find(i))
                ++ans;
        }
        writeln<int>(n - ans);
    }
    return 0;
}