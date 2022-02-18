#include <iostream>
#include <vector>
#include <queue>
using namespace std;

constexpr int MAX_N = 2e5 + 10;

int n, k, c[MAX_N];
vector<int> nodes[MAX_N];
vector<int> tree[MAX_N];
int tot, root, sze[MAX_N], sze2[MAX_N];
bool vis[MAX_N];
int tag[MAX_N], selected[MAX_N], timer;
int father[MAX_N];
int ans = 0x3f3f3f3f;

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void getRoot(int x, int fa) {
    sze[x] = 1;
    sze2[x] = 0;

    for (int y : tree[x]) {
        if (y == fa || vis[y])
            continue;

        getRoot(y, x);
        sze[x] += sze[y];
        sze2[x] = max(sze2[x], sze[y]);
    }

    sze2[x] = max(sze2[x], tot - sze[x]);

    if (!root || sze2[root] > sze2[x])
        root = x;
}

void mark(int x, int fa) {
    sze[x] = 1;
    tag[x] = timer;
    father[x] = fa;

    for (int y : tree[x]) {
        if (y == fa || vis[y])
            continue;

        mark(y, x);
        sze[x] += sze[y];
    }
}

int add(int x, queue<int> & q) {
    if (x == 0)
        return x;
    
    father[x] = add(father[x], q);
    
    if (selected[c[x]] != timer) {
        q.push(c[x]);
        selected[c[x]] = timer;
    }

    return father[x];
}

void solve(int x) {
    vis[x] = true;
    ++timer;
    mark(x, 0);
    selected[c[x]] = timer;
    queue<int> q;
    q.push(c[x]);

    bool quit = false;
    int res = -1;

    while (!q.empty()) {
        int co = q.front();
        ++res;
        q.pop();

        for (int i : nodes[co]) {
            if (tag[i] != timer) {
                quit = true;
                break;
            }

            add(i, q);
        }

        if (quit)
            break;
    }

    if (!quit)
        ans = min(ans, res);
    
    for (int y : tree[x]) {
        if (vis[y])
            continue;
        
        tot = sze[y];
        root = 0;
        getRoot(y, 0);
        solve(root);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
    }

    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
        nodes[c[i]].push_back(i);
    }

    tot = n;
    getRoot(1, 0);
    solve(root);
    cout << ans << endl;
    return 0;
}

