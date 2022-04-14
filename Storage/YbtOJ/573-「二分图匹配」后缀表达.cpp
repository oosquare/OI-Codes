#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3000 + 10;

struct edge {
    int to, next;
};

edge graph[maxn];
int uuid, head[maxn], vis[maxn], match[maxn];
int id, tag[maxn], vaild[maxn][maxn], cnt[maxn][maxn], f[maxn];
int len, fat[maxn], ans[maxn], inv[maxn];
char expr[maxn];
stack<int> stk;

void link(int x, int y) {
    graph[++uuid] = {y, head[x]};
    head[x] = uuid;
}

bool find1(int u, int x) {
    for (int i = head[x], y; y = graph[i].to, i; i = graph[i].next) {
        if (tag[y] != id && vaild[y][u]) {
            tag[y] = id;
            if (match[y] == -1 || find1(match[y], x)) {
                match[y] = u;
                return true;
            }
        }
    }
    return false;
}

bool find2(int u, int x) {
    for (int i = head[x], y; y = graph[i].to, i; i = graph[i].next) {
        if (tag[y] != id && vaild[y][u]) {
            tag[y] = id;
            if (match[y] == -1 || find2(match[y], x)) {
                return true;
            }
        }
    }
    return false;
}

void DFS(int x) {
    ans[x] = 1;
    for (int i = head[x], y; y = graph[i].to, i; i = graph[i].next) {
        DFS(y);
        ans[x] += ans[y];
    }
    for (int i = 0; i < 26; ++i)
        ans[x] += cnt[x][i];
    id = 0;
    for (int i = 0; i < 26; ++i) {
        if (cnt[x][i]) {
            ++id;
            vaild[x][i] = true;
            ans[x] -= find1(i, x);
        }
    }
    for (int i = head[x], y; y = graph[i].to, i; i = graph[i].next) {
        tag[y] = ++id;
        if (match[y] == -1 || find2(match[y], x))
            for (int j = 0; j < 26; ++j)
                vaild[x][j] = vaild[x][j] || vaild[y][j];
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("expr.in", "r", stdin);
    freopen("expr.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> (expr + 1);
    len = strlen(expr + 1);
    memset(match, -1, sizeof(match));
    for (int i = 1; i <= len; ++i) {
        if (isalpha(expr[i])) {
            stk.push(i);
        } else {
            fat[stk.top()] = i;
            stk.pop();
            fat[stk.top()] = i;
            stk.pop();
            stk.push(i);
        }
    }
    for (int i = 1; i < len; ++i) {
        while (expr[fat[i]] == expr[fat[fat[i]]]) {
            inv[fat[i]] = true;
            fat[i] = fat[fat[i]];
        }
    }
    for (int i = 1; i <= len; ++i) {
        if (isalpha(expr[i])) {
            cnt[fat[i]][expr[i] - 'a'] = true;
        } else if (!inv[i]) {
            link(fat[i], i);
        }
    }
    DFS(len);
    cout << ans[len] << endl;
    return 0;
}
