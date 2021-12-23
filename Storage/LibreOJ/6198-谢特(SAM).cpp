#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

constexpr int maxn = 2e5 + 10;

struct Node {
    int next[26], link, len;
    bool clone;
    int val;

    int &operator[](int x) {
        return next[x];
    }
};

Node sam[maxn], trie[maxn * 50];
int suuid, last, tuuid, root[maxn];
char str[maxn];
int n, w[maxn];
vector<int> tree[maxn];
int sze[maxn], son[maxn], dfn[maxn], rev[maxn], timer;
int ans;

void link(int x, int y) {
    tree[x].push_back(y);
}

void insert(char c, int val) {
    int x = ++suuid, p = last, w = c - 'a';
    last = x;
    sam[x].len = sam[p].len + 1;
    sam[x].val = val;

    for (; p != -1 && !sam[p][w]; p = sam[p].link)
        sam[p][w] = x;

    if (p == -1) {
        sam[x].link = 0;
    } else {
        int q = sam[p][w];

        if (sam[q].len == sam[p].len + 1) {
            sam[x].link = q;
        } else {
            int nq = ++suuid;
            sam[nq] = sam[q];
            sam[nq].len = sam[p].len + 1;
            sam[nq].clone = true;
            sam[q].link = sam[x].link = nq;

            for (; p != -1 && sam[p][w] == q; p = sam[p].link)
                sam[p][w] = nq;
        }
    }
}

void insert(int &rt, int num) {
    if (!rt)
        rt = ++tuuid;

    int x = rt;

    for (int i = 31; i >= 0; --i) {
        int w = ((num >> i) & 1);

        if (!trie[x][w])
            trie[x][w] = ++tuuid;

        x = trie[x][w];
    }
}

int calc(int rt, int num) {
    int x = rt, res = 0;

    for (int i = 31; i >= 0; --i) {
        int w = ((num >> i) & 1);

        if (trie[x][w ^ 1]) {
            res |= (1 << i);
            x = trie[x][w ^ 1];
        } else if (trie[x][w]) {
            x = trie[x][w];
        } else {
            break;
        }
    }

    return res;
}

void preprocess(int x) {
    sze[x] = 1;
    dfn[x] = ++timer;
    rev[timer] = x;

    for (int y : tree[x]) {
        preprocess(y);
        sze[x] += sze[y];

        if (sze[y] > sze[son[x]])
            son[x] = y;
    }
}

int merge(int x, int y) {
    if (!x || !y)
        return x ^ y;

    for (int i = 0; i < 26; ++i)
        trie[x][i] = merge(trie[x][i], trie[y][i]);

    return x;
}

void dfs(int x) {
    for (int y : tree[x])
        dfs(y);

    root[x] = root[son[x]];

    if (!sam[x].clone) {
        ans = max(ans, (root[x] ? sam[x].len : 0) + calc(root[x], sam[x].val));
        insert(root[x], sam[x].val);
    }

    for (int y : tree[x]) {
        if (y == son[x])
            continue;

        for (int i = dfn[y]; i < dfn[y] + sze[y]; ++i)
            if (!sam[rev[i]].clone)
                ans = max(ans, (root[x] ? sam[x].len : 0) + calc(root[x], sam[rev[i]].val));

        root[x] = merge(root[x], root[y]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    sam[0].link = -1;

    cin >> n;
    cin >> (str + 1);

    for (int i = 1; i <= n; ++i)
        cin >> w[i];

    for (int i = 1, j = n; i < j; ++i, --j) {
        swap(str[i], str[j]);
        swap(w[i], w[j]);
    }

    for (int i = 1; i <= n; ++i)
        insert(str[i], w[i]);

    for (int i = 1; i <= suuid; ++i)
        link(sam[i].link, i);

    preprocess(0);
    dfs(0);
    cout << ans << endl;
    return 0;
}