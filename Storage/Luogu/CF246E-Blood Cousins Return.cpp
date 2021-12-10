#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>

using namespace std;

constexpr int maxn = 1e5 + 10;

int n, m;
vector<int> tree[maxn];
int timer, dfn[maxn], rev[maxn], dep[maxn], mdep[maxn], sze[maxn], son[maxn];
unordered_set<int> cnt[2 * maxn];
unordered_map<string, int> mp;
int uuid, id[maxn];
vector<pair<int, int>> querys[maxn];
int ans[maxn];

void link(int x, int y) {
    tree[x].push_back(y);
}

void preprocess(int x) {
    sze[x] = 1;
    dfn[x] = ++timer;
    rev[timer] = x;
    mdep[x] = dep[x];

    for (int y : tree[x]) {
        dep[y] = dep[x] + 1;
        preprocess(y);
        sze[x] += sze[y];
        mdep[x] = max(mdep[x], mdep[y]);

        if (sze[son[x]] < sze[y])
            son[x] = y;
    }
}

void solve(int x, bool keep) {
    for (int y : tree[x]) {
        if (y == son[x])
            continue;
        
        solve(y, false);
    }

    if (son[x])
        solve(son[x], true);
    
    cnt[dep[x]].insert(id[x]);

    for (int y : tree[x]) {
        if (y == son[x])
            continue;
        
        for (int i = dfn[y]; i <= dfn[y] + sze[y]; ++i)
            cnt[dep[rev[i]]].insert(id[rev[i]]);
    }

    for (auto [k, id] : querys[x])
        ans[id] = cnt[dep[x] + k].size();
    
    if (!keep)
        for (int i = dep[x]; i <= mdep[x]; ++i)
            cnt[i].clear();
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        string s;
        int r;
        cin >> s >> r;

        if (mp.find(s) == mp.end())
            mp[s] = ++uuid;
        
        id[i] = mp[s];
        link(r, i);
    }

    cin >> m;

    for (int i = 1; i <= m; ++i) {
        int x, k;
        cin >> x >> k;
        querys[x].push_back({k, i});
    }

    preprocess(0);
    solve(0, true);

    for (int i = 1; i <= m; ++i)
        cout << ans[i] << endl;

    return 0;
}