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

typedef long long ll;

constexpr int maxn = 1e6 + 10;

struct e {
    int to, next;
    ll weight;
};

e edge[maxn * 2];
int head[maxn], uuid;
int n, m;
ll b, l, r, ans = -1;
ll dis[maxn], cost[maxn];
bool vis[maxn];
deque<int> q;

void link(int x, int y, int w) {
    edge[++uuid] = {y, head[x], w};
    head[x] = uuid;
    edge[++uuid] = {x, head[y], w};
    head[y] = uuid;
}

void SPFA(int maxv) {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[1] = 0;
    vis[1] = true;
    q.push_back(1);
    while (!q.empty()) {
        int x = q.front();
        q.pop_front();
        vis[x] = false;
        for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
            if (cost[y] > maxv)
                continue;
            if (dis[y] > dis[x] + edge[i].weight) {
                dis[y] = dis[x] + edge[i].weight;
                if (vis[y])
                    continue;
                vis[y] = true;
                // SLF + swap
                if (!q.empty() && dis[y] < dis[q.front()]) {
                    int t = q.front();
                    q.pop_front();
                    q.push_front(y);
                    q.push_back(t);
                } else {
                    q.push_back(y);
                }
            }
        }
    }
}

bool check(int x) {
    SPFA(x);
    if (dis[n] == 0x3f3f3f3f3f3f3f3f || dis[n] >= b)
        return false;
    else
        return true;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    using namespace IO;
    n = read();
    m = read();
    b = read();
    for (int i = 1; i <= n; ++i) {
        cost[i] = read<ll>();
        r = max(r, cost[i]);
    }
    for (int i = 1; i <= m; ++i) {
        int x = read(), y = read();
        ll z = read<ll>();
        link(x, y, z);
    }
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    if (ans == -1)
        printf("AFK\n");
    else
        printf("%lld\n", ans);
    return 0;
}