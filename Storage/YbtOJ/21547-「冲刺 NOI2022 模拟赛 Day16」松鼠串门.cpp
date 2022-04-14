#include <iostream>
#include <vector>
#include <tuple>

constexpr int MAX_N = 1000000 + 10;

struct LinearBasis {
    unsigned long long b[64];
    int d[64];

    void add(unsigned long long val, int dep) {
        for (int i = 63; i >= 0; --i) {
            if (!((val >> i) & 1))
                continue;

            if (b[i]) {
                if (d[i] < dep) {
                    std::swap(d[i], dep);
                    std::swap(b[i], val);
                }

                val ^= b[i];
            } else {
                b[i] = val;
                d[i] = dep;
                break;
            }
        }
    }

    unsigned long long query(int lim) {
        unsigned long long res = 0;

        for (int i = 63; i >= 0; --i) {
            if (d[i] < lim || (res ^ b[i]) <= res)
                continue;

            res ^= b[i];
        }

        return res;
    }
};

int n, m, tot;
unsigned long long a[MAX_N];
std::vector<int> tree[MAX_N];
int dep[MAX_N];
std::tuple<int, int, unsigned long long> op[MAX_N];
LinearBasis basis[MAX_N];

void link(int x, int y) {
    tree[x].push_back(y);
}

void dfs(int x, int fa) {
    dep[x] = dep[fa] + 1;
    basis[x] = basis[fa];
    basis[x].add(a[x], dep[x]);

    for (int y : tree[x])
        dfs(y, x);
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("c.in", "r", stdin);
    std::freopen("c.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    
    for (int i = 1; i <= n; ++i) {
        int f;
        std::cin >> f >> a[i];
        
        if (f)
            link(f, i);
    }

    tot = n;

    for (int i = 1; i <= m; ++i) {
        auto &[type, x, y] = op[i];
        std::cin >> type >> x >> y;

        if (type == 1) {
            ++tot;
            link(x, tot);
            a[tot] = y;
        }
    }

    dfs(1, 0);

    for (int i = 1; i <= m; ++i) {
        auto [type, x, y] = op[i];

        if (type == 0) 
            std::cout << basis[x].query(dep[x] - y) << std::endl;
    }

    return 0;
}
