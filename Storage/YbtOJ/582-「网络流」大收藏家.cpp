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

constexpr int maxn = 30000 + 10;
constexpr int oo = 0x3f3f3f3f;

struct e {
    int to, next, capacity;
};

e graph[maxn * 100];
int uuid = 1, head[maxn], dis[maxn], cur[maxn];
int t, n, m, source, sink, a[maxn], x[maxn], y[maxn];
vector<int> ps[maxn], ans;
int id;

inline void link(int x, int y, int c) {
    graph[++uuid] = {y, head[x], c};
    head[x] = uuid;
    graph[++uuid] = {x, head[y], 0};
    head[y] = uuid;
}

inline void link2(int x, int y, int c) {
    graph[++uuid] = {y, head[x], c};
    head[x] = uuid;
}

bool BFS() {
    for (int i = 1; i <= id; ++i)
        dis[i] = 0;
    queue<int> q;
    q.push(source);
    dis[source] = 1;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        cur[x] = head[x];
        for (int i = head[x], y; y = graph[i].to, i; i = graph[i].next) {
            if (graph[i].capacity <= 0 || dis[y])
                continue;
            dis[y] = dis[x] + 1;
            q.push(y);
        }
    }
    return dis[sink] != 0;
}

int DFS(int x, int a) {
    if (x == sink)
        return a;
    int res = 0;
    for (int &i = cur[x], y; y = graph[i].to, i; i = graph[i].next) {
        if (graph[i].capacity <= 0 || dis[y] != dis[x] + 1)
            continue;
        int f = DFS(y, min(graph[i].capacity, a - res));
        if (f > 0) {
            graph[i].capacity -= f;
            graph[i ^ 1].capacity += f;
            res += f;
            if (res == a)
                break;
        }
    }
    if (res != a)
        dis[x] = 0;
    return res;
}

inline int Dinic() {
    int flow = 0;
    while (BFS())
        flow += DFS(source, oo);
    return flow;
}

void solve() {
    uuid = 1;
    id = 0;
    n = IO::read(), m = IO::read();
    for (register int i = 1; i <= n; ++i)
        a[i] = IO::read();
    for (register int i = 1; i <= m; ++i)
        x[i] = IO::read(), y[i] = IO::read();
    source = ++id, sink = ++id;
    for (register int i = 1; i <= n; ++i)
        ps[i].push_back(++id);
    for (register int i = 1; i <= m; ++i) {
        ps[x[i]].push_back(++id);
        ps[y[i]].push_back(++id);
        link2(id - 1, id, 1);
        link2(id, id - 1, 1);
    }
    for (register int i = 1; i <= n; ++i) {
        link(source, ps[i][0], 1);
        for (int j = 0; j < ps[i].size() - 1; ++j)
            link(ps[i][j], ps[i][j + 1], a[i]);
    }
    
    this_thread::sleep_for(chrono::microseconds(35));
    link(ps[1][ps[1].size() - 1], sink, a[1]);
    ans.push_back(Dinic());
    for (register int i = 1; i <= n; ++i)
        ps[i].clear();
    for (register int i = 1; i <= id; ++i)
        head[i] = 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("collection.in", "r", stdin);
    freopen("collection.out", "w", stdout);
#endif
    clock_t st = clock();
    t = IO::read();
    for (int i = 1; i <= t; ++i) solve();
    int delta = clock() - st;
    for (auto i : ans)
        IO::writeln(i);
    return 0;
}
