#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

constexpr int maxn = 1e5 + 10;

class GeneralSuffixAutomaton {
public:
    struct Node {
        int next[10], link, len;

        Node() : link(0), len(0) {
            for (int i = 0; i < 10; ++i)
                next[i] = 0;
        }

        int &operator[](int x) {
            return next[x];
        }
    };

    GeneralSuffixAutomaton() : uuid(1) {}

    int size() {
        return uuid;
    }

    Node &operator[](int x) {
        return nodes[x];
    }

    int insert(int w, int last) {
        if (!nodes[last][w])
            nodes[last][w] = ++uuid;

        return nodes[last][w];
    }

    void build() {
        queue<pair<int, int>> q;

        for (int i = 0; i < 10; ++i)
            if (nodes[1][i])
                q.push({1, i});

        while (!q.empty()) {
            auto [x, w] = q.front();
            q.pop();
            int l = extend(w, x);

            for (int i = 0; i < 10; ++i)
                if (nodes[l][i])
                    q.push({l, i});
        }
    }

private:
    Node nodes[maxn * 50];
    int uuid;

    int extend(int w, int last) {
        int x = nodes[last][w], p = nodes[last].link;
        nodes[x].len = nodes[last].len + 1;

        for (; p && !nodes[p][w]; p = nodes[p].link)
            nodes[p][w] = x;

        if (!p) {
            nodes[x].link = 1;
        } else {
            int q = nodes[p][w];

            if (nodes[q].len == nodes[p].len + 1) {
                nodes[x].link = q;
            } else {
                int nq = ++uuid;

                for (int i = 0; i < 10; ++i)
                    nodes[nq][i] = (nodes[nodes[q][i]].len ? nodes[q][i] : 0);

                nodes[nq].link = nodes[q].link;
                nodes[nq].len = nodes[p].len + 1;
                nodes[q].link = nodes[x].link = nq;

                for (; p && nodes[p][w] == q; p = nodes[p].link)
                    nodes[p][w] = nq;
            }
        }

        return x;
    }
};

int n, c;
int col[maxn], deg[maxn];
vector<int> tree[maxn];
GeneralSuffixAutomaton gsam;
long long ans;

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
    ++deg[x];
    ++deg[y];
}

void dfs(int x, int fa, int last) {
    last = gsam.insert(col[x], last);

    for (int y : tree[x]) {
        if (y == fa)
            continue;

        dfs(y, x, last);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> c;

    for (int i = 1; i <= n; ++i)
        cin >> col[i];

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
    }

    for (int i = 1; i <= n; ++i)
        if (deg[i] == 1)
            dfs(i, 0, 1);

    gsam.build();

    for (int i = 2; i <= gsam.size(); ++i)
        ans += gsam[i].len - gsam[gsam[i].link].len;

    cout << ans << endl;
    return 0;
}