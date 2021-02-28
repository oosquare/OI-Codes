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

constexpr int maxn = 300 + 10;

struct e {
    int to, next;
};

e edge[maxn * maxn * 10];
int head[maxn * maxn], uuid;
int match[maxn * maxn], vis[maxn * maxn];
int n, m, ans;
bool invaild[maxn][maxn];
int dir[8][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

void link(int x, int y) {
    edge[++uuid] = {y, head[x]};
    head[x] = uuid;
    edge[++uuid] = {x, head[y]};
    head[y] = uuid;
}

bool vaild(int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= n && !invaild[x][y];
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
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    using namespace IO;
    n = read();
    m = read();
    for (int i = 1; i <= m; ++i) {
        int x = read(), y = read();
        invaild[x][y] = true;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (!vaild(i, j))
                continue;
            for (int k = 0; k < 8; ++k) {
                int ni = i + dir[k][0], nj = j + dir[k][1];
                if (!vaild(ni, nj))
                    continue;
                link(n * (i - 1) + j,  n * (ni - 1) + nj);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            memset(vis, 0, sizeof(vis));
            if (vaild(i, j) && (i + j) % 2 && find(n * (i - 1) + j))
                ++ans;
        }
        
    }
    writeln(n * n - ans - m);
    return 0;
}