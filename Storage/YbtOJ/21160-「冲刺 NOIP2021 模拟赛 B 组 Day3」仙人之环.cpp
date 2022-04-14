#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
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

constexpr int maxn = 1e6 + 10;

int n, m, k, ans;
vector<int> graph[maxn];
int dfn[maxn], low[maxn], timer, cnt;
int sze[maxn], uuid;
int st[maxn], top;

void link(int x, int y) {
    graph[x].push_back(y);
    graph[y].push_back(x);
}

void tarjan(int x, int fa) {
    dfn[x] = low[x] = ++timer;

    for (int y : graph[x]) {
        if (!dfn[y]) {
            tarjan(y, x);
            low[x] = min(low[x], low[y]);

            if (low[y] > dfn[x])
                ++cnt;
        } else if (y != fa) {
            low[x] = min(low[x], dfn[y]);
        }
    }
}

void dfs(int x) {
    dfn[x] = low[x] = ++timer;
    st[++top] = x;

    for (int y : graph[x]) {
        if (!dfn[y]) {
            dfs(y);
            low[x] = min(low[x], low[y]);

            if (low[y] == dfn[x]) {
                ++uuid;
                sze[uuid] = 1;

                for (int v = 0; v != y; --top) {
                    v = st[top];
                    ++sze[uuid];
                }
            }
        } else {
            low[x] = min(low[x], dfn[y]);
        }
    }
}

int main() {
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    using namespace IO;
    n = read(), m = read(), k = read();

    for (int i = 1; i <= m; ++i) {
        int x = read(), y = read();
        link(x, y);
    }

    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            dfs(i), ++ans;

    timer = 0;
    fill(dfn + 1, dfn + 1 + n, 0);
    fill(low + 1, low + 1 + n, 0);

    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i, 0);
    
    if (cnt >= k) {
        ans += k;
        writeln(ans);
    } else {
        ans += cnt;
        k -= cnt;
        sort(sze + 1, sze + 1 + uuid, greater<int>());

        for (int i = 1; i <= uuid && sze[i] > 1; ++i) {
            if (k >= sze[i]) {
                k -= sze[i];
                ans += sze[i] - 1;
            } else if (k > 0) {
                ans += k - 1;
                break;
            }
        }

        writeln(ans);
    }

    return 0;
}
