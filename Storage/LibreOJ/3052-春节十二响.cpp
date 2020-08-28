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

constexpr int maxn = 2e5 + 10;

struct e {
    int to, next;
};

e tree[maxn];
int uuid, head[maxn];
priority_queue<int> q[maxn];
int n, tmp[maxn], mem[maxn];
long long ans;

void link(int x, int y) {
    tree[++uuid] = {y, head[x]};
    head[x] = uuid;
}

void DFS(int x) {
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next) {
        DFS(y);
        if (q[x].size() < q[y].size())
            swap(q[x], q[y]);
        int s = q[y].size();
        for (int j = 1; j <= s; ++j) {
            tmp[j] = max(q[x].top(), q[y].top());
            q[y].pop();
            q[x].pop();
        }
        for (int j = 1; j <= s; ++j)
            q[x].push(tmp[j]);
    }
    q[x].push(mem[x]);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    using namespace IO;
    n = read();
    for (int i = 1; i <= n; ++i)
        mem[i] = read();
    for (int i = 2; i <= n; ++i) {
        int x = read();
        link(x, i);
    }
    DFS(1);
    while (!q[1].empty()) {
        ans += q[1].top();
        q[1].pop();
    }
    writeln(ans);
    return 0;
}