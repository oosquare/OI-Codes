#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 300 + 10;

struct e {
    int to, next;
};

e edge[maxn * maxn];
int uuid, head[maxn];
int dfn[maxn], low[maxn], idx[maxn];
int n, m, k, timer, scc;
stack<int> st;

void link(int x, int y) {
    edge[++uuid] = {y, head[x]};
    head[x] = uuid;
}

void Tarjan(int x) {
    dfn[x] = low[x] = ++timer;
    st.push(x);
    for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
        if (!dfn[y]) {

            Tarjan(y);
            low[x] = min(low[x], low[y]);
        } else if (!idx[y]) {
            low[x] = min(low[x], dfn[y]);
        }
    }
    if (low[x] == dfn[x]) {
        idx[x] = ++scc;
        while (st.top() != x) {
            idx[st.top()] = scc;
            st.pop();
        }
        st.pop();
    }
}

bool check() {
    for (int i = 1; i <= n; ++i)
        if (idx[i] == idx[i + n])
            return false;
    return true;
}

int notx(int x) { return x <= n ? x + n : x - n; }

char mygetchar() {
    char c = getchar();
    while (c != 'h' && c != 'm')
        c = getchar();
    return c;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    scanf("%d", &k);
    for (int casenum = 1; casenum <= k; ++casenum) {
        memset(head, 0, sizeof(head));
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(idx, 0, sizeof(idx));
        uuid = scc = timer = 0;
        while (!st.empty())
            st.pop();
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; ++i) {
            int x, y;
            char a, b;
            a = mygetchar();
            scanf("%d", &x);
            b = mygetchar();
            scanf("%d", &y);
            if (a == 'h')
                x += n;
            if (b == 'h')
                y += n;
            link(notx(x), y);
            link(notx(y), x);
        }
        for (int i = 1; i <= 2 * n; ++i)
            if (!dfn[i])
                Tarjan(i);
        printf("%s\n", check() ? "GOOD" : "BAD");
    }
    return 0;
}