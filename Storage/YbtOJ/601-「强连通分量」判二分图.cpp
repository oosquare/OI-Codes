#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3000 + 10;

struct edge {
    int to, next;
};

int g1[maxn][maxn];
edge g2[maxn * 100];
int uuid, head[maxn];
int dfn[maxn], low[maxn], id[maxn], timer, scc;
int n, m, ma[maxn], vis[maxn], ans;
stack<int> st;

void link(int x, int y) {
    g2[++uuid] = {y, head[x]};
    head[x] = uuid;
}

void tarjan(int x) {
    dfn[x] = low[x] = ++timer;
    st.push(x);
    for (int i = head[x], y; y = g2[i].to, i; i = g2[i].next) {
        if (!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        } else if (!id[y]) {
            low[x] = min(low[x], dfn[y]);
        }
    }
    if (low[x] == dfn[x]) {
        id[x] = ++scc;
        while (st.top() != x) {
            id[st.top()] = scc;
            st.pop();
        }
        st.pop();
    }
}

bool find(int x) {
    for (int i = n + 1; i <= n + m; ++i) {
        if (g1[x][i]) {
            if (vis[i])
                continue;
            vis[i] = true;
            if (!ma[i] || find(ma[i])) {
                ma[i] = x;
                return true;
            }
        }
    }
    return false;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("fantasy.in", "r", stdin);
    freopen("fantasy.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        char s[maxn];
        cin >> (s + 1);
        for (int j = 1; j <= m; ++j)
            if (s[j] == '1')
                g1[i][j + n] = true;
    }
    for (int i = 1; i <= n; ++i) {
        memset(vis, 0, sizeof(vis));
        if (find(i))
            ++ans;
    }
    if (ans < n) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j)
                cout << 1;
            cout << endl;
        }
    } else {
        for (int i = 1; i <= n; ++i) {
            for (int j = n + 1; j <= n + m; ++j)
                if (g1[i][j])
                    ma[j] == i ? link(i, j) : link(j, i);
        }
        for (int i = n + 1; i <= n + m; ++i)
            ma[i] ? link(i, n + m + 1) : link(n + m + 1, i);
        for (int i = 1; i <= n + m + 1; ++i)
            if (!dfn[i])
                tarjan(i);
        for (int i = 1; i <= n; ++i) {
            for (int j = n + 1; j <= n + m; ++j)
                if (g1[i][j] && (ma[j] == i || id[i] == id[j]))
                    cout << 0;
                else
                    cout << 1;
            cout << endl;
        }
    }
    return 0;
}
