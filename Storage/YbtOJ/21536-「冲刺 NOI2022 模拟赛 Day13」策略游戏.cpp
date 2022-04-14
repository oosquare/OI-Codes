#include <iostream>
#include <bits/extc++.h>

constexpr int MAX_N = 300000 + 5;

struct Edge {
    int x, y, w;
};

struct Info {
    int id, w, which;

    bool operator<(const Info &rhs) const {
        return w > rhs.w;
    }
};

int n, m, p[MAX_N];
Edge edges[MAX_N];
int fa[MAX_N], sum[MAX_N], root[MAX_N];
int ans, seq[MAX_N];
std::queue<std::pair<int, int>> tmp;
__gnu_pbds::priority_queue<Info> buc[MAX_N];
__gnu_pbds::priority_queue<Info>::point_iterator iter[MAX_N][2];
__gnu_pbds::priority_queue<int, std::greater<int>> q;

int find(int x) {
    return (x == fa[x] ? x : fa[x] = find(fa[x]));
}

int mergeSet(int x, int y) {
    if (buc[x].size() < buc[y].size())
        std::swap(x, y);

    while (!buc[y].empty()) {
        auto [id, w, which] = buc[y].top();
        iter[id][which] = buc[x].push({ id, w, which });
        buc[y].pop();
    }

    return x;
}


void merge(int x, int y) {
    x = find(x);
    y = find(y);

    if (x == y)
        return;

    fa[y] = x;
    sum[x] += sum[y];
    root[x] = mergeSet(root[x], root[y]);

    while (!buc[root[x]].empty() && buc[root[x]].top().w <= sum[x]) {
        int id = buc[root[x]].top().id;
        int x = find(edges[id].x), y = find(edges[id].y);

        if (iter[id][0]->w + iter[id][1]->w <= sum[x] + sum[y])
            q.push(id);
        else
            tmp.push({ id, iter[id][0]->w + iter[id][1]->w - sum[x] - sum[y] });

        buc[root[x]].erase(iter[id][0]);
        buc[root[y]].erase(iter[id][1]);
    }

    while (!tmp.empty()) {
        auto [id, w] = tmp.front();
        tmp.pop();

        int x = find(edges[id].x), y = find(edges[id].y);
        iter[id][0] = buc[root[x]].push({ id, sum[x] + w / 2, 0 });
        iter[id][1] = buc[root[y]].push({ id, sum[y] + (w + 1) / 2, 1 });
    }
}

signed main() {
#ifdef ONLINE_JUDGE
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        std::cin >> p[i];

    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
        root[i] = i;
        sum[i] = p[i];
    }

    for (int i = 1; i <= m; ++i) {
        auto &[x, y, w] = edges[i];
        std::cin >> x >> y >> w;

        if (sum[x] + sum[y] >= w) {
            q.push(i);
        } else {
            int d = w - sum[x] - sum[y];
            iter[i][0] = buc[x].push({ i, sum[x] + d / 2, 0 });
            iter[i][1] = buc[y].push({ i, sum[y] + (d + 1) / 2, 1 });
        }
    }

    while (!q.empty()) {
        int id = q.top();
        q.pop();
        auto [x, y, w] = edges[id];

        if (find(x) == find(y))
            continue;

        merge(x, y);
        seq[++ans] = id;
    }

    std::cout << ans << std::endl;

    for (int i = 1; i <= ans; ++i)
        std::cout << seq[i] << " ";

    return 0;
}
