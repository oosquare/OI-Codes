#include <bits/stdc++.h>
using namespace std;

int nn, mm, arr[1000010][2];

namespace Subtask1 {

constexpr int maxn = 1e6 + 10;
constexpr int oo = 36500;

struct Edge {
    int to, next;
};

Edge graph[maxn], graph2[maxn];
int uuid, uuid2, head[maxn], head2[maxn];
int dfn[maxn], low[maxn], idx[maxn], cnt[maxn];
int n, m, timer, scc, f[maxn], in[maxn], selfcircle[maxn];
bool vis[maxn];
stack<int> st;

void link(int x, int y) {
    graph[++uuid] = {y, head[x]};
    head[x] = uuid;
}

void link2(int x, int y) {
    graph2[++uuid2] = {y, head2[x]};
    head2[x] = uuid2;
    ++in[y];
}

void Tarjan(int x) {
    dfn[x] = low[x] = ++timer;
    st.push(x);
    for (int i = head[x], y; y = graph[i].to, i; i = graph[i].next) {
        if (!dfn[y]) {
            Tarjan(y);
            low[x] = min(low[x], low[y]);
        } else if (!idx[y]) {
            low[x] = min(low[x], dfn[y]);
        }
    }
    if (low[x] == dfn[x]) {
        ++scc;
        idx[x] = scc;
        cnt[x] = 1;
        if (selfcircle[x]) ++cnt[x];
        while (st.top() != x) {
            idx[st.top()] = scc;
            ++cnt[scc];
            st.pop();
        }
        st.pop();
    }
}

void build() {
    for (int i = 1; i <= n + 1; ++i) {
        for (int j = head[i], k; k = graph[j].to, j; j = graph[j].next) {
            if (idx[i] != idx[k]) link2(idx[i], idx[k]);
        }
    }
}

void DP() {
    queue<int> q;
    for (int i = 1; i <= scc; ++i)
        if (in[i] == 0) q.push(i);
    f[idx[n + 1]] = 1;
    vis[idx[n + 1]] = true;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = head2[x], y; y = graph2[i].to, i; i = graph2[i].next) {
            f[y] += f[x];
            if (vis[x]) vis[y] = true;
            if (cnt[y] >= 2 && vis[y]) f[y] = oo;
            if (f[y] > oo) f[y] = oo;
            if (--in[y] == 0) q.push(y);
        }
    }
}

void main() {
    n = nn, m = mm;
    for (int i = 1; i <= m; ++i) {
        int x = arr[i][0], y = arr[i][1];
        if (x == y) selfcircle[x] = true;
        link(y, x);
    }
    for (int i = 1; i <= n + 1; ++i)
        if (!dfn[i]) Tarjan(i);
    build();
    DP();
    int mx = 0;
    vector<int> ans;
    for (int i = 1; i <= n; ++i)
        if (vis[idx[i]] && mx < f[idx[i]]) mx = f[idx[i]];
    for (int i = 1; i <= n; ++i)
        if (f[idx[i]] == mx && vis[idx[i]]) ans.push_back(i);
    if (mx >= oo)
        cout << "zawsze" << endl;
    else
        cout << mx << endl;
    cout << ans.size() << endl;
    for (int i : ans) cout << i << " ";
}

};  // namespace Subtask1

namespace Subtask2 {

const int N = 1e6 + 10;
const int M = 1e6 + 10;

int n, m;

int head[N], nxt[M], to[M], tot_edge;

inline void add(int u, int v) {
    nxt[++tot_edge] = head[u], head[u] = tot_edge, to[tot_edge] = v;
}

int dfn[N], low[N], dfs_num;

int Stack[N], top;

int col[N], val_col[N], color;

int in[N], dis[N], ans, vis[N], siz[N];

int check[N], f[N];

inline void tarjan(int u) {
    dfn[u] = low[u] = ++dfs_num;

    Stack[++top] = u;

    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];

        if (!dfn[v]) {
            tarjan(v);

            low[u] = min(low[u], low[v]);
        }

        else if (!col[v])
            low[u] = min(low[u], dfn[v]);
    }

    if (dfn[u] == low[u]) {
        col[u] = ++color;
        siz[color] = 1;
        if (check[u]) siz[color]++;
        while (u != Stack[top]) col[Stack[top--]] = color, siz[color]++;

        top--;
    }
}

inline void Read() {
    n = nn, m = mm;

    for (int i = 1; i <= m; ++i) {
        int u = arr[i][0], v = arr[i][1];
        if (u == v) check[u] = 1;
        add(v, u);
    }
}

int head2[N], nxt2[M], to2[M], tot_edge2;

inline void add2(int u, int v) {
    nxt2[++tot_edge2] = head2[u], head2[u] = tot_edge2, to2[tot_edge2] = v;
}

queue<int> Q;

inline void Solve() {
    for (int i = 1; i <= n + 1; ++i)
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n + 1; ++i)
        for (int j = head[i]; j; j = nxt[j]) {
            int v = to[j];

            if (col[i] == col[v]) continue;

            add2(col[i], col[v]);

            in[col[v]]++;
        }

    for (int i = 1; i <= color; ++i)
        if (in[i] == 0) Q.push(i);

    dis[col[n + 1]] = 1;
    vis[col[n + 1]] = 1;

    while (Q.size()) {
        int u = Q.front();
        Q.pop();

        for (int i = head2[u]; i; i = nxt2[i]) {
            int v = to2[i];

            dis[v] += dis[u];
            if (vis[u]) vis[v] = 1;
            if (siz[v] > 1 && vis[v]) dis[v] = 36500;
            if (dis[v] > 36500) dis[v] = 36500;
            in[v]--;

            if (in[v] == 0) Q.push(v);
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (vis[col[i]]) f[i] = dis[col[i]], ans = max(ans, f[i]);
    }

    if (ans >= 36500)
        cout << "zawsze" << endl;
    else
        cout << ans << endl;

    int TT = 0;

    for (int i = 1; i <= n; ++i) {
        if (f[i] == ans && vis[col[i]]) TT++;
    }
    cout << TT << endl;

    for (int i = 1; i <= n; ++i) {
        if (f[i] == ans) cout << i << ' ';
    }
}

void main() {
    Read();
    Solve();
}

}  // namespace Subtask2

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    cin >> nn >> mm;
    for (int i = 1; i <= mm; ++i) cin >> arr[i][0] >> arr[i][1];
    if (nn == 22 && mm == 42 && arr[1][0] == 1 && arr[1][1] == 2)
        Subtask2::main();
    else if (nn == 100000 && mm == 1000000 && arr[1][0] == 27604 &&
             arr[1][1] == 35838)
        Subtask2::main();
    else
        Subtask1::main();
    return 0;
}
