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

constexpr int maxn = 1000000 + 10;
constexpr int maxm = 2 * maxn;

map<int, int> edges[maxn];
int n, m;
bool vis[maxn];
int cnt[maxn], dis[maxn];

void link(int x, int y) {
    ++edges[x][y];
    ++edges[y][x];
}

void BFS() {
    queue<int> q;
    q.push(1);
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    vis[1] = true;
    cnt[1] = 1;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (auto i : edges[x]) {
            int y = i.first, c = i.second;
            if (dis[y] > dis[x] + 1) {
                dis[y] = dis[x] + 1;
                cnt[y] = cnt[x] * c % 100003;
            } else if (dis[y] == dis[x] + 1) {
                cnt[y] = (cnt[y] + cnt[x] * c % 100003) % 100003;
            }
            if (vis[y])
                continue;
            vis[y] = true;
            q.push(y);
        }
    }
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
        link(x, y);
    }
    BFS();
    for (int i = 1; i <= n; ++i)
        writeln(cnt[i]);
    return 0;
}