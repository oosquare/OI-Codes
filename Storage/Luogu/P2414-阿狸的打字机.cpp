#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int maxm = 1e5 + 10;

struct Node {
    int next[26];
    int fail;
    int end;

    int &operator[](int x) {
        return next[x];
    }
};

struct Query {
    int id, x, y;

    bool operator<(const Query &rhs) const {
        return y < rhs.y;
    }
};

int m;
Node trie[maxn * 10];
int root, uuid = root, cnt, ed[maxn], rev[maxn];
int dfn[maxn], sze[maxn], timer;
int arr[maxn], ans[maxn], fa[maxn];
vector<int> tree[maxn], tree2[maxn];
vector<Query> qs[maxn];

inline int lowbit(int x) {
    return x & (-x);
}

void add(int p, int v) {
    for (; p <= timer; p += lowbit(p))
        arr[p] += v;
}

int query(int p) {
    int res = 0;
    for (; p; p -= lowbit(p))
        res += arr[p];
    return res;
}

int query(int x, int y) {
    return query(y) - query(x - 1);
}

void link(int x, int y) {
    tree[x].push_back(y);
}

void insert(string s) {
    int x = root;
    for (char c : s) {
        if (c == 'P') {
            rev[++cnt] = x;
            ed[x] = cnt;
        } else if (c == 'B') {
            x = fa[x];
        } else {
            if (trie[x][c - 'a'] == 0) {
                trie[x][c - 'a'] = ++uuid;
                fa[uuid] = x;
            }
            x = trie[x][c - 'a'];
            st.push(x);
        }
    }
}

void build() {
    for (int i = 0; i <= uuid; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (trie[i][j]) {
                tree2[i].push_back(trie[i][j]);
            }
        }
    }  
    queue<int> q;
    for (int i = 0; i < 26; ++i) {
        if (trie[root][i] != 0) {
            q.push(trie[root][i]);
            link(root, trie[root][i]);
        }
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 0; i < 26; ++i) {
            if (trie[x][i] == 0) {
                trie[x][i] = trie[trie[x].fail][i];
            } else {
                trie[trie[x][i]].fail = trie[trie[x].fail][i];
                q.push(trie[x][i]);
                link(trie[trie[x][i]].fail, trie[x][i]);
            }
        }
    }
}

void dfs1(int x) {
    dfn[x] = ++timer;
    sze[x] = 1;
    for (int y : tree[x]) {
        dfs1(y);
        sze[x] += sze[y];
    }
}

void dfs2(int x) {
    add(dfn[x], 1);
    if (ed[x] != 0) {
        for (auto [id, qx, qy] : qs[ed[x]]) {
            ans[id] = query(dfn[rev[qx]], dfn[rev[qx]] + sze[rev[qx]] - 1);
        }
    }
    for (int y : tree2[x])
        dfs2(y);
    add(dfn[x], -1);
}

int main() {
    ios::sync_with_stdio(false);
    
    string od;
    cin >> od;
    insert(od);
    build();

    cin >> m;
    for (int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;
        qs[y].push_back({i, x, y});
    }
    dfs1(root);
    dfs2(root);
    for (int i = 1; i <= m; ++i)
        cout << ans[i] << endl;
    return 0;
}