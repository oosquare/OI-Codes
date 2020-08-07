#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2000 + 10;

struct e {
    int to, next;
};

e edge[maxn * 100];
int uuid, head[maxn];
int timer, dfn[maxn], low[maxn];
int idx[maxn], cnt[maxn], scc;
stack<int> st;
int n, m;

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
        ++cnt[scc];
        while (st.top() != x) {
            idx[st.top()] = scc;
            ++cnt[scc];
            st.pop();
        }
        st.pop();
    }
}

bool check() {
    for (int i = 0; i < n; ++i)
        if (idx[i * 2] == idx[(i * 2) ^ 1])
            return false;
    return true;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(head, 0, sizeof(head));
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(idx, 0, sizeof(idx));
        memset(cnt, 0, sizeof(cnt));
        uuid = scc = timer = 0;
        for (int i = 1; i <= m; ++i) {
            int a1, a2, c1, c2;
            scanf("%d%d%d%d", &a1, &a2, &c1, &c2);
            a1 = (2 * a1) + c1;
            a2 = (2 * a2) + c2;
            link(a1, a2 ^ 1);
            link(a2, a1 ^ 1);
        }
        for (int i = 0; i < 2 * n; ++i)
            if (!dfn[i])
                Tarjan(i);
        printf("%s\n", check() ? "YES" : "NO");
    }
    return 0;
}