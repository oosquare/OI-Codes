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

constexpr int maxn = 10000 + 10;

struct edge {
    int to, next;
};

int n, ans, deg[maxn];
edge graph[maxn * maxn];
bool linked[maxn][maxn];
int uuid, head[maxn], dfn[maxn], low[maxn], timer;
int idx[maxn], cnt[maxn], scc;
int st[maxn], top;
int sa[maxn], sb[maxn], ta, tb, ca[maxn], cb[maxn];

void link(int x, int y) {
    graph[++uuid] = {y, head[x]};
    head[x] = uuid;
}

void tarjan(int x) {
    dfn[x] = low[x] = ++timer;
    st[++top] = x;
    for (int i = head[x], y; y = graph[i].to, i; i = graph[i].next) {
        if (!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        } else if (!idx[y]) {
            low[x] = min(low[x], dfn[y]);
        }
    }
    if (low[x] == dfn[x]) {
        idx[x] = ++scc;
        cnt[scc] = 1;
        while (st[top] != x) {
            idx[st[top]] = scc;
            ++cnt[scc];
            --top;
        }
        --top;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("conspiracy.in", "r", stdin);
    freopen("conspiracy.out", "w", stdout);
#endif
    using namespace IO;
    ios::sync_with_stdio(false);
    n = read();
    for (int i = 1; i <= n; ++i) {
        int y;
        deg[i] = read();
        for (int j = 1; j <= deg[i]; ++j) {
            y = read();
            linked[i][y] = true;
        }
    }
    for (int i = 1; i < n; ++i)
        for (int j = i + 1; j <= n; ++j)
            if (linked[i][j])
                link(i + n, j), link(j + n, i);
            else
                link(i, j + n), link(j, i + n);
    for (int i = 1; i <= 2 * n; ++i)
        if (!dfn[i])
            tarjan(i);
    
    for (int i = 1; i <= n; ++i) {
        if (idx[i] == idx[i + n]) {
            cout << 0 << endl;
            return 0;
        }
        if (idx[i] < idx[i + n])
            sa[++ta] = i;
        else
            sb[++tb] = i;
    }
    if (ta > 0 && tb > 0)
        ans = 1;
    for (int i = 1; i <= ta; ++i)
        for (int j = 1; j <= ta; ++j)
            if (linked[sa[i]][sa[j]])
                ++ca[sa[i]];
    for (int i = 1; i <= tb; ++i)
        for (int j = 1; j <= tb; ++j)
            if (!linked[sb[i]][sb[j]] && i != j)
                ++cb[sb[i]];
    for (int i = 1; i <= ta; ++i)
        if (ca[sa[i]] == deg[sa[i]] && ta > 1)
            ++ans;
    for (int i = 1; i <= tb; ++i)
        if (cb[sb[i]] == n - deg[sb[i]] - 1 && tb > 1)
            ++ans;
    for (int i = 1; i <= ta; ++i)
        for (int j = 1; j <= tb; ++j)
            if (ca[sa[i]] == deg[sa[i]] || (ca[sa[i]] == deg[sa[i]] - 1 && linked[sa[i]][sb[j]]))
                if (cb[sb[j]] == n - deg[sb[j]] - 1 || (cb[sb[j]] == n - deg[sb[j]] - 2 && !linked[sa[i]][sb[j]]))
                    ++ans;
    writeln(ans);

    return 0;
}
