#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

namespace IO {

template <typename T> T read() {
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

const int maxm = 500 + 10;

struct e {
    int to, next;
};

int head[maxm * 2], uuid;
e edge[maxm * maxm * 2];
int n, m, vis[maxm * 2], match[maxm * 2], ans;
int startt[maxm], endt[maxm], startp[maxm][2], endp[maxm][2];

template <typename T> T myabs(T x) { return x >= 0 ? x : -x; }

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

void build() {
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i == j)
                continue;
            int t0 = myabs(endp[i][0] - startp[j][0]) + myabs(endp[i][1] - startp[j][1]);
            if (endt[i] + t0 < startt[j]) {
                link(i, j);
            }
        }
    }
}

void init() {
    memset(match, 0, sizeof(match));
    memset(head, 0, sizeof(head));
    uuid = ans = 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    using namespace IO;
    n = read<int>();
    for (int T = 1; T <= n; ++T) {
        init();
        m = read<int>();
        for (int i = 1; i <= m; ++i) {
            int hh, mm;
            scanf("%d:%d", &hh, &mm);
            int a = startp[i][0] = read<int>();
            int b = startp[i][1] = read<int>();
            int c = endp[i][0] = read<int>();
            int d = endp[i][1] = read<int>();
            startt[i] = hh * 60 + mm;
            endt[i] = hh * 60 + mm + myabs(a - c) + myabs(b - d);
        }
        build();
        for (int i = 1; i <= m; ++i) {
            memset(vis, 0, sizeof(vis));
            if (find(i))
                ++ans;
        }
        writeln(m - ans);
    }
    return 0;
}