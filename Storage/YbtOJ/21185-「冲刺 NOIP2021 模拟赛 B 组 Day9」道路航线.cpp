#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <numeric>
#include <cstring>
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

constexpr int maxn = 3e6 + 10;

struct Edge {
    int to, next;
};

int n, m, a, b, timer;
int q[maxn], l, r;
Edge graph[maxn * 2];
int uuid, head[maxn];
int vis[maxn];
int ex[maxn], ey[maxn], et[maxn];

void link(int x, int y, int t) {
    graph[++uuid] = {y, head[x]};
    head[x] = uuid;

    if (t)
        return;

    graph[++uuid] = {x, head[y]};
    head[y] = uuid;
}

bool check(int mid, int start, int end) {
    memset(head, 0, sizeof(head));
    uuid = 0;

    for (int i = 1; i <= mid; ++i)
        link(ex[i], ey[i], et[i]);

    ++timer;
    vis[start] = timer;
    q[l = r = 1] = start;

    while (l <= r) {
        int x = q[l++];

        for (int i = head[x], y; y = graph[i].to, i; i = graph[i].next) {
            if (vis[y] == timer)
                continue;

            vis[y] = timer;
            q[++r] = y;

            if (y == end)
                return true;
        }
    }

    return false;
}

int solve(int start, int end) {
    int l = 1, r = m, ans = -1;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (check(mid, start, end)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    return ans;
}

int main() {
    freopen("road.in", "r", stdin);
    freopen("road.out", "w", stdout);
    using namespace IO;
    n = read(), m = read(), a = read(), b = read();

    for (int i = 1; i <= m; ++i)
        ex[i] = read(), ey[i] = read(), et[i] = read();

    writesp(solve(a, b));
    writeln(solve(b, a));
    return 0;
}
