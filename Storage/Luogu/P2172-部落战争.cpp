#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

namespace IO {

template <typename T = int> T read() {
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

const int maxn = 120;

struct e {
    int to, next;
};

e edge[maxn * maxn * 10];
int head[maxn * maxn], uuid;
int n, m, r, c, ans, cnt, match[maxn * maxn], vis[maxn * maxn];
char ground[maxn][maxn];

int getx(int i) {
    int ans;
    switch (i) {
        case 0: ans = r; break;
        case 1: ans = c; break;
        case 2: ans = r; break;
        case 3: ans = c; break;
    }
    return ans;
}

int gety(int i) {
    int ans;
    switch (i) {
        case 0: ans = c; break;
        case 1: ans = r; break;
        case 2: ans = -c; break;
        case 3: ans = -r; break;
    }
    return ans;
}

void link(int x, int y) {
    edge[++uuid] = {y, head[x]};
    head[x] = uuid;
    edge[++uuid] = {x, head[y]};
    head[y] = uuid;
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

bool vaild(int x, int y) {
    return 1 <= x && x <= m && 1 <= y && y <= n && ground[x][y] == '.';
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    using namespace IO;
    m = read();
    n = read();
    r = read();
    c = read();
    for (int i = 1; i <= m; ++i)
        scanf("%s", ground[i] + 1);
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (ground[i][j] == 'x')
                continue;
            for (int k = 0; k < 4; ++k) {
                int ni = i + getx(k), nj = j + gety(k);
                if (!vaild(ni, nj))
                    continue;
                link((i - 1) * n + j, (ni - 1) * n + nj + m * n);
            }
        }
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (ground[i][j] == 'x') {
                ++cnt;
                continue;
            }
            memset(vis, 0, sizeof(vis));
            if (find((i - 1) * n + j))
                ++ans;
        }
    }
    writeln(m * n - cnt - ans);
    return 0;
}