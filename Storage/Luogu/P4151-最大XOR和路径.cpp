#include <iostream>
#include <vector>
using namespace std;

constexpr int maxn = 1e5 + 10;

struct LinearBasis {
    long long val[64];

    void insert(long long num) {
        for (int i = 63; i >= 0; --i) {
            if (!((num >> i) & 1))
                continue;

            if (val[i]) {
                num ^= val[i];
            } else {
                for (int j = i - 1; j >= 0; --j)
                    if ((num >> j) & 1)
                        num ^= val[j];

                for (int j = 63; j > i; --j)
                    if ((val[j] >> i) & 1)
                        val[j] ^= num;

                val[i] = num;
                return;
            }
        }
    }

    long long query(long long x) {
        for (int i = 63; i >= 0; --i)
            if ((x ^ val[i]) > x)
                x ^= val[i];

        return x;
    }
};

int n, m;
LinearBasis b;
vector<pair<int, long long>> graph[maxn];
long long dis[maxn];
bool vis[maxn];

void link(int x, int y, long long l) {
    graph[x].push_back({y, l});
    graph[y].push_back({x, l});
}

void dfs(int x, int last, long long sum) {
    vis[x] = true;
    dis[x] = sum;

    for (auto [y ,l] : graph[x]) {
        if (y == last)
            continue;

        if (!vis[y])
            dfs(y, x, sum ^ l);
        else
            b.insert(sum ^ l ^ dis[y]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int x, y;
        long long l;
        cin >> x >> y >> l;
        link(x, y, l);
    }

    dfs(1, 0, 0);
    cout << b.query(dis[n]) << endl;
    return 0;
}