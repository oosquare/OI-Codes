#include <iostream>
#include <vector>
using namespace std;

constexpr int maxn = 1e6 + 10;

struct Edge {
    int to, length, id;
};

int n;
vector<Edge> tree[maxn];
vector<pair<int, int>> circle;
bool vis[maxn], in[maxn];
long long seq[maxn], sum[maxn], tot;
int q[maxn], fr, bk;
long long dis[maxn][2], f[maxn], ans;

void link(int x, int y, int l, int id) {
    tree[x].push_back({y, l, id});
    tree[y].push_back({x, l, id});
}

bool find(int x, int last, vector<pair<int, int>> &nodes) {
    bool found = false;
    vis[x] = true;

    for (auto [y, l, id] : tree[x]) {
        if (id == last || in[y])
            continue;

        if (vis[y]) {
            nodes.push_back({y, l});
            in[y] = true;
            found = true;
        } else {
            bool res = find(y, id, nodes);

            if (res) {
                nodes.push_back({y, l});
                in[y] = true;

                if (x != nodes[0].first)
                    found = true;
            }
        }
    }

    return found;
}

long long dfs(int x, int fa) {
    long long res = 0;

    for (auto [y, l, id] : tree[x]) {
        if (y == fa || in[y])
            continue;

        res = max(res, dfs(y, x));

        if (dis[x][0] <= dis[y][0] + l) {
            dis[x][1] = dis[x][0];
            dis[x][0] = dis[y][0] + l;
        } else if (dis[x][1] < dis[y][0] + l) {
            dis[x][1] = dis[y][0] + l;
        }
    }

    return max(res, dis[x][0] + dis[x][1]);
}

long long calc(int x) {
    long long res = 0;
    tot = 0;
    circle.clear();
    find(x, 0, circle);

    for (auto [i, l] : circle) {
        res = max(res, dfs(i, 0));
        seq[++tot] = dis[i][0];
        sum[tot + 1] = l;
    }

    for (int i = 1, t = tot; i <= t; ++i) {
        seq[++tot] = seq[i];
        sum[tot + 1] = sum[i + 1];
    }

    for (int i = 1; i <= tot; ++i)
        sum[i] += sum[i - 1];

    fr = bk = 1;
    q[1] = 1;

    for (int i = 2; i <= tot; ++i) {
        while (fr <= bk && q[fr] < i - (int)circle.size() + 1)
            ++fr;

        int j = q[fr];
        f[i] = seq[i] + seq[j] + sum[i] - sum[j];
        res = max(res, f[i]);

        while (fr <= bk && seq[q[bk]] - sum[q[bk]] <= seq[i] - sum[i])
            --bk;

        q[++bk] = i;
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        int x, l;
        cin >> x >> l;
        link(i, x, l, i);
    }

    for (int i = 1; i <= n; ++i) {
        if (vis[i])
            continue;

        ans += calc(i);
    }

    cout << ans << endl;
    return 0;
}