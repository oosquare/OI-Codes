#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
#include <set>
using namespace std;

constexpr int maxn = 1e6 + 10;
constexpr int oo = 0x3f3f3f3f;

struct Node {
    int next[26];
    int fa;
    bool end;
};

struct Operation {
    int type;
    char c;
    int x, y;
};

int n, uuid = 1, now = 1, tot;
Node tree[maxn];
int step[maxn][20], dep[maxn];
set<int> pos[maxn];
Operation op[maxn];
int id[maxn];

void preprocess(int x, int fa) {
    for (int i = 1; i <= 19; ++i)
        step[x][i] = step[step[x][i - 1]][i - 1];

    for (int i = 0; i < 26; ++i) {
        int y = tree[x].next[i];

        if (y == 0 || y == fa)
            continue;

        step[y][0] = x;
        dep[y] = dep[x] + 1;
        preprocess(y, x);
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);

    for (int i = 19; i >= 0; --i)
        if (dep[step[x][i]] >= dep[y])
            x = step[x][i];

    if (x == y)
        return x;

    for (int i = 19; i >= 0; --i) {
        if (step[x][i] != step[y][i]) {
            x = step[x][i];
            y = step[y][i];
        }
    }

    return step[x][0];
}

int first(const set<int> &s) {
    if (s.empty())
        return oo;

    return *s.begin() - 1;
}

void dfs(int x, int fa) {
    cout << x << " " << tree[x].fa << endl;
    for (int i = 0; i < 26; ++i) {
        int y = tree[x].next[i];

        if (y == 0 || y == fa)
            continue;

        dfs(y, x);
    }
}

int main() {
    freopen("typewriter.in", "r", stdin);
    freopen("typewriter.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> op[i].type;

        switch (op[i].type) {
        case 1:
            cin >> op[i].c;
            
            if (!tree[now].next[(int)op[i].c - 'a']) {
                tree[now].next[(int)op[i].c - 'a'] = ++uuid;
                tree[uuid].fa = now;
            }

            now = tree[now].next[(int)op[i].c - 'a'];
            break;
        case 2:
            now = tree[now].fa;
            break;
        case 3:
            id[++tot] = now;
            break;
        case 4:
            cin >> op[i].x >> op[i].y;
            break;
        case 5:
            cin >> op[i].x >> op[i].y;
            break;
        }
    }

    preprocess(1, 0);

    for (int i = 1; i <= n; ++i) {
        int x = op[i].x, y = op[i].y;
        
        if (op[i].type == 4) {
            if (pos[x].find(y) == pos[x].end())
                pos[x].insert(y);
            else
                pos[x].erase(y);
        } else if (op[i].type == 5) {
            int l = lca(id[x], id[y]);
            cout << min(dep[l], min(first(pos[x]), first(pos[y]))) << endl;
        }
    }
    
    return 0;
}
