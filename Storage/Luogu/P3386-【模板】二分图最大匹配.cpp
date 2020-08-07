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
constexpr int maxe = 5e4 + 10;

struct ee {
    int to, next;
};

int n, m, e, ma[2*maxn], head[2*maxn], uuid, ans;
bool vis[maxn * 2];
ee edge[maxe*2];

bool match(int x) {
    for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
        if (vis[y])
            continue;
        vis[y] = true;
        if (!ma[y] || match(ma[y])) {
            ma[y] = x;
            return true;
        }
    }
    return false;
}

void link(int x, int y) {
    edge[++uuid] = {y, head[x]};
    head[x] = uuid;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    using namespace IO;
    n = read();
    m = read();
    e = read();
    for (int i = 1; i <= e; ++i) {
        int x = read(), y = read();
        link(x, y + n);
        link(y + n, x);
    }
    for (int i = 1; i <= n; ++i) {
        memset(vis, 0, sizeof(vis));
        if (match(i))
            ++ans;
    }
    writeln(ans);
    return 0;
}