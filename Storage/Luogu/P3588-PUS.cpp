#include <iostream>
#include <vector>
#include <queue>

constexpr int MAX_N = 100000 + 10;
constexpr int INF = 1000000000;

struct Node {
    int left, right;
    int ls, rs;
};

int n, s, m;
int tot, root;
Node tree[MAX_N * 4];
int f[MAX_N * 10], mi[MAX_N * 10], id[MAX_N];
std::vector<std::pair<int, int>> graph[MAX_N * 10];
int in[MAX_N * 10];
bool vis[MAX_N * 10];

inline void link(int x, int y, int w) {
    graph[x].push_back({ y, w });
    ++in[y];
}

void build(int &x, int l, int r) {
    x = ++tot;
    tree[x].left = l;
    tree[x].right = r;

    if (l == r) {
        id[l] = x;
        return;
    }

    int mid = (l + r) / 2;
    build(tree[x].ls, l, mid);
    build(tree[x].rs, mid + 1, r);
    link(x, tree[x].ls, 0);
    link(x, tree[x].rs, 0);
}

void add(int x, int l, int r, int from) {
    if (l <= tree[x].left && tree[x].right <= r) {
        link(from, x, 1);
        return;
    }

    int mid = (tree[x].left + tree[x].right) / 2;

    if (l <= mid)
        add(tree[x].ls, l, r, from);

    if (mid < r)
        add(tree[x].rs, l, r, from);
}

void topo() {
    std::queue<int> q;

    for (int i = 1; i <= tot; ++i)
        if (!in[i])
            q.push(i);

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        vis[x] = true;

        for (auto [y, w] : graph[x]) {
            f[y] = std::min(f[y], f[x] - w);
            --in[y];

            if (f[y] < mi[y] || f[y] < 1) {
                std::cout << "NIE" << std::endl;
                std::exit(0);
            }

            if (!in[y])
                q.push(y);
        }
    }

    for (int i = 1; i <= tot; ++i) {
        if (!vis[i]) {
            std::cout << "NIE" << std::endl;
            std::exit(0);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> n >> s >> m;
    build(root, 1, n);

    for (int i = 1; i <= s; ++i) {
        int p, d;
        std::cin >> p >> d;
        f[id[p]] = mi[id[p]] = d;
    }

    for (int i = 1; i <= m; ++i) {
        int l, r, k;
        std::cin >> l >> r >> k;
        ++tot;
        int last = l;

        for (int j = 1; j <= k; ++j) {
            int x;
            std::cin >> x;

            link(id[x], tot, 0);

            if (last <= x - 1)
                add(root, last, x - 1, tot);

            last = x + 1;
        }

        if (last <= r)
            add(root, last, r, tot);
    }

    for (int i = 1; i <= tot; ++i)
        if (!f[i])
            f[i] = INF;

    topo();

    std::cout << "TAK" << std::endl;

    for (int i = 1; i <= n; ++i)
        std::cout << f[id[i]] << " ";

    return 0;
}
