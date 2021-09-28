#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;

const int maxn = 2000 + 10;

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

int notx(int x) {
    return x <= n ? x + n : x - n;
}

bool check() {
    for (int i = 1; i <= n; ++i)
        if (idx[i] == idx[i + n])
            return false;
    return true;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    while (scanf("%d%d", &n, &m) && n && m) {
        memset(head, 0, sizeof(head));
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(idx, 0, sizeof(idx));
        memset(cnt, 0, sizeof(cnt));
        uuid = scc = timer = 0;
        for (int i = 1; i <= m; ++i) {
            int x, y;
            char a, b;
            scanf("%d%c %d%c", &x, &a, &y, &b);
            ++x;
            ++y;
            if (a == 'h')
                x += n;
            if (b == 'h')
                y += n;
            link(x, notx(y));
            link(y, notx(x));
        }
        link(1, 1 + n);
        for (int i = 1; i <= 2 * n; ++i)
            if (!dfn[i])
                Tarjan(i);
        if (!check()) {
            printf("bad luck\n");
            continue;
        } else {
            for (int i = 2; i <= n; ++i)
                printf("%d%c ", i - 1, idx[i] > idx[i + n] ? 'w' : 'h');
            printf("\n");
        }
    }
    return 0;
}