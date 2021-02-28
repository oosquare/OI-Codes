#include <bits/stdc++.h>
using namespace std;

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T = int>
T read() {
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

constexpr int maxn = 100000 + 10;
constexpr int maxm = 2 * maxn;

struct e {
    int to, next;
};

int head[maxn], f[maxn], in[maxn], n, m, uuid;
e edge[maxm];

void link(int x, int y) {
    edge[++uuid] = {y, head[x]};
    head[x] = uuid;
    ++in[y];
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read();
    m = read();
    for (int i = 1; i <= m; ++i) {
        int x = read(), y = read();
        link(x, y);
    }
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (!in[i])
            q.push(i);
        f[i] = 1;
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
            f[y] = max(f[y], f[x] + 1);
            if (--in[y] == 0)
                q.push(y);
        }
    }
    copy(f + 1, f + 1 + n, ostream_iterator<int>(cout, "\n"));
    return 0;
}