#include <bits/stdc++.h>
using namespace std;

struct Node {
    int next[26];
    bool end, vaild;

    int &operator[](int x) {
        return next[x];
    }
};

using ll = long long;

constexpr int maxn = 1e6 + 10;

int n;
int root = 1, uuid = root, timer, sze[maxn], dfn[maxn];
Node trie[maxn];
vector<int> tree[maxn];

void link(int x, int y) {
    tree[x].push_back(y);
}

void insert(string s) {
    int x = root, c;
    for (int i = s.size() - 1; i >= 0; --i) {
        c = s[i] - 'a';
        if (trie[x][c] == 0)
            trie[x][c] = ++uuid;
        x = trie[x][c];
    }
    trie[x].end = true;
}

void rebuild(int x, int fa) {
    for (int i = 0, y; y = trie[x][i], i < 26; ++i) {
        if (y == 0)
            continue;
        if (trie[y].end == true) {
            link(fa, y);
            rebuild(y, y);
        } else {
            rebuild(y, fa);
        }
    }
}

void dfs1(int x) {
    sze[x] = 1;
    for (int y : tree[x]) {
        dfs1(y);
        sze[x] += sze[y];
    }
    sort(tree[x].begin(), tree[x].end(), [=](int x, int y) {
        return sze[x] < sze[y];
    });
}

ll dfs2(int x) {
    dfn[x] = ++timer;
    ll res = 0;
    for (int y : tree[x])
        res += dfs2(y) + dfn[y] - dfn[x];
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        insert(s);
    }
    rebuild(root, root);
    dfs1(root);
    cout << dfs2(root) << endl;
    return 0;
}