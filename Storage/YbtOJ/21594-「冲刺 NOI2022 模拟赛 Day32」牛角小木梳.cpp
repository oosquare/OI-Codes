#include <iostream>
#include <vector>

constexpr int MAX_N = 100000 + 10;

int n;
long long p;
std::vector<int> tree[MAX_N];
int dis[MAX_N], which[MAX_N];
int ans;

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void preprocess(int x, int fa) {
    for (int y : tree[x]) {
        if (y == fa)
            continue;

        preprocess(y, x);

        if (dis[x] < dis[y] + 1) {
            dis[x] = dis[y] + 1;
            which[x] = y;
        }
    }
}

void walk(int x, int fa, bool in_chain) {
    ++ans;

    if (in_chain && p >= 1 && which[x]) {
        --p;
        walk(which[x], x, true);
    }

    for (int y : tree[x]) {
        if (y == fa || (in_chain && y == which[x]))
            continue;

        if (p >= 2) {
            p -= 2;
            walk(y, x, false);
        } else {
            break;
        }
    }
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("b.in", "r", stdin);
    std::freopen("b.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);

    std::cin >> n >> p;

    for (int i = 1; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        link(x, y);
    }

    preprocess(0, 0);
    walk(0, 0, true);
    std::cout << ans << std::endl;
    return 0;
}