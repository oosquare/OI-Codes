#include <bits/stdc++.h>
using namespace std;

#define int long long

constexpr int N = 1e6 + 10;
constexpr int oo = 0x3f3f3f3f3f3f3f3f;

int n;
int from[2 * N], to[N * 2], cnt, head[N];
int vis[N], dis[N];
int tmp1[N], tmp2[N], lth[N];
int stak[N], top;
int deep[N], depth[N], len1[N], len2[N], du[N], ans;
int pmaxn[N][2], smaxn[N][2], f;

void link(int x, int y, int z) {
    from[++cnt] = head[x];
    head[x] = cnt;
    dis[cnt] = z;
    to[cnt] = y;
    return;
}

void dfs1(int x, int fa) {
    depth[x] = deep[x];
    int son[2];
    son[0] = son[1] = -oo;

    for (int i = head[x]; i; i = from[i]) {
        int v = to[i];

        if (v == fa || vis[v])
            continue;

        deep[v] = deep[x] + dis[i];
        dfs1(v, x);
        depth[x] = max(depth[x], depth[v]);
        lth[x] = max(lth[x], lth[v] + dis[i]);

        if (son[0] < lth[v] + dis[i])
            son[1] = son[0], son[0] = lth[v] + dis[i];
        else if (son[1] < lth[v] + dis[i])
            son[1] = dis[i] + lth[v];
    }

    if (son[1] > -oo)
        ans = max(ans, son[0] + son[1]);

    return;
}

int solve(int x) {
    int s1 = pmaxn[x - 1][0] + smaxn[x][0];
    return max(s1, max(tmp1[x - 1], tmp2[x]));
}

void dfs(int x) {
    vis[x] = 1;
    stak[++top] = x;

    for (int i = head[x]; i; i = from[i]) {
        int v = to[i];

        if (du[v] <= 1 || vis[v] == 1)
            continue;

        dfs(v);
    }

    return;
}
signed main() {
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    cin >> n;

    for (int i = 1; i <= n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        link(x, y, z);
        link(y, x, z);
        du[x]++, du[y]++;
    }

    queue<int> q;

    for (int i = 1; i <= n; i++)
        if (du[i] == 1)
            q.push(i);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = head[u]; i; i = from[i]) {
            int v = to[i];
            du[v]--;

            if (du[v] == 1)
                q.push(v);
        }
    }

    for (int i = 1; i <= n; i++)
        if (du[i] > 1) {
            dfs(i);
            break;
        }

    for (int i = 1; i <= top; i++)
        dfs1(stak[i], 0);

    stak[0] = stak[top];

    for (int i = 1; i <= top; i++)
        for (int j = head[stak[i]]; j; j = from[j]) {
            int v = to[j];

            if (v == stak[i - 1]) {
                len1[i] = dis[j] + len1[i - 1];
                break;
            }
        }

    for (int i = top - 1; i + 1; i--)
        for (int j = head[stak[i]]; j; j = from[j]) {
            int v = to[j];

            if (v == stak[i + 1]) {
                len2[i] = dis[j] + len2[i + 1];
                break;
            }
        }

    int sss = -oo;

    for (int i = 1; i <= top; i++) {
        if (sss > -oo)
            tmp1[i] = max(tmp1[i - 1], len1[i] + depth[stak[i]] + sss);

        sss = max(sss, depth[stak[i]] - len1[i]);
        pmaxn[i][0] = max(pmaxn[i - 1][0], depth[stak[i]] + len1[i]);
    }

    smaxn[top][0] = pmaxn[top][1] = depth[stak[top]];
    tmp2[top] = depth[stak[top]];
    sss = -oo;

    for (int i = top; i + 1; i--) {
        if (sss != -oo)
            tmp2[i] = max(tmp2[i + 1], depth[stak[i]] + len2[i] + sss);

        sss = max(sss, depth[stak[i]] - len2[i]);
        smaxn[i][0] = max(smaxn[i + 1][0], depth[stak[i]] + len2[i]);
    }

    int res = tmp1[top];

    for (int i = 2; i <= top; i++)
        res = min(res, solve(i));

    cout << max(ans, res) << endl;
    return 0;
}
