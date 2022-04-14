#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e6 + 50;

struct Edge {
    int to, next;
};

struct Rule {
    int i, j;
    char hi, hj;
};

Edge graph[maxn];
int uuid, head[maxn], dfn[maxn], low[maxn];
int n, d, m, k, stc[maxn], top, scc, timer;
int idx[maxn], pos[maxn];
char s[maxn], res[maxn];
Rule rule[maxn];

void link(int x, int y) {
    graph[++uuid] = { y, head[x] };
    head[x] = uuid;
}

void init() {
    memset(head, 0, sizeof(head));
    memset(dfn, 0, sizeof(dfn));
    timer = scc = top = 0;
    memset(low, 0, sizeof(low));
    memset(stc, 0, sizeof(stc));
    memset(idx, 0, sizeof(idx));
}

void tarjan(int x) {
    dfn[x] = low[x] = ++timer;
    stc[++top] = x;
    for (int i = head[x], y; y = graph[i].to, i; i = graph[i].next) {
        if (!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        } else if (!idx[y])
            low[x] = min(low[x], dfn[y]);
    }
    if (low[x] == dfn[x]) {
        ++scc;
        while (top) {
            idx[stc[top]] = scc;
            if (stc[top--] == x)
                break;
        }
    }
}

bool check() {
    for (int i = 1; i <= 2 * n; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; ++i) {
        if (idx[i] == idx[i + n])
            return false;
        if (idx[i] < idx[n + i])
            res[i] = (s[i] == 'A') ? 'B' : 'A';
        else
            res[i] = (s[i] == 'C') ? 'B' : 'C';
    }
    res[n + 1] = '\0';
    cout << (res + 1) << endl;
    return true;
}

void solve() {
    for (int i = 0; i < (1 << d); ++i) {
        init();
        for (int j = 1; j <= d; ++j) s[pos[j]] = (i & (1 << (j - 1))) ? 'A' : 'B';
        for (int j = 1; j <= m; ++j) {
            if (rule[j].hi == s[rule[j].i])
                continue;
            if (rule[j].hj == s[rule[j].j]) {
                if (rule[j].hi == 'C' || (rule[j].hi == 'B' && s[rule[j].i] == 'C'))
                    link(rule[j].i + n, rule[j].i);
                else
                    link(rule[j].i, rule[j].i + n);
                continue;
            }

            int add1, add2;
            if (rule[j].hi == 'C' || (rule[j].hi == 'B' && s[rule[j].i] == 'C'))
                add1 = n;
            else
                add1 = 0;
            if (rule[j].hj == 'C' || (rule[j].hj == 'B' && s[rule[j].j] == 'C'))
                add2 = n;
            else
                add2 = 0;
            link(rule[j].i + add1, rule[j].j + add2);
            link(rule[j].j - add2 + n, rule[j].i - add1 + n);
        }
        if (check())
            exit(0);
    }
    cout << -1 << endl;
    return;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
#endif
    cin >> n >> d;
    cin >> (s + 1);
    cin >> m;
    for (int i = 1; i <= m; ++i) cin >> rule[i].i >> rule[i].hi >> rule[i].j >> rule[i].hj;
    for (int i = 1; i <= n; ++i)
        if ((s[i] -= 32) && s[i] == 'X')
            pos[++k] = i;
    solve();
    return 0;
}
