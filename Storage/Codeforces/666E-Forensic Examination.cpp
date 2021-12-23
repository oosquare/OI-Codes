#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

constexpr int maxn = 5e5 + 10;

int n, m, q;
char s[maxn], t[maxn];

namespace SegmentTree {

struct Node {
    int ls, rs;
    int max, pos;
};

Node tree[maxn * 20];
int uuid, root[maxn * 2];

void pushup(int x) {
    if (tree[tree[x].ls].max >= tree[tree[x].rs].max) {
        tree[x].max = tree[tree[x].ls].max;
        tree[x].pos = tree[tree[x].ls].pos;
    } else {
        tree[x].max = tree[tree[x].rs].max;
        tree[x].pos = tree[tree[x].rs].pos;
    }
}

void add(int &x, int l, int r, int p, int v) {
    if (!x)
        x = ++uuid;

    if (l == r) {
        tree[x].max += v;
        tree[x].pos = l;
        return;
    }

    int mid = (l + r) >> 1;

    if (p <= mid)
        add(tree[x].ls, l, mid, p, v);
    else
        add(tree[x].rs, mid + 1, r, p, v);

    pushup(x);
}

pair<int, int> query(int x, int l, int r, int ql, int qr) {
    if (!x)
        return {0, 0};

    if (ql <= l && r <= qr)
        return {tree[x].max, tree[x].pos};

    int mid = (l + r) >> 1;
    pair<int, int> res = {0, 0};

    if (ql <= mid) {
        auto res2 = query(tree[x].ls, l, mid, ql, qr);
        
        if (res2.first > res.first)
            res = res2;
    }

    if (mid < qr) {
        auto res2 = query(tree[x].rs, mid + 1, r, ql, qr);
        
        if (res2.first > res.first)
            res = res2;
    }

    return res;
}

int merge(int x, int y, int l, int r) {
    if (!x || !y)
        return x ^ y;

    if (l == r) {
        int id = ++uuid;
        tree[id].max = tree[x].max + tree[y].max;
        tree[id].pos = (tree[id].max ? l : 0);
        return id;
    }

    int mid = (l + r) / 2, id = ++uuid;
    tree[id].ls = merge(tree[x].ls, tree[y].ls, l, mid);
    tree[id].rs = merge(tree[x].rs, tree[y].rs, mid + 1, r);
    pushup(id);
    return id;
}

} // SegmentTree

namespace GeneralSuffixAutomaton {

struct Node {
    int next[26], link, len;

    Node() : link(0), len(0) {
        for (int i = 0; i < 26; ++i)
            next[i] = 0;
    }

    int &operator[](int x) {
        return next[x];
    }
};

Node nodes[maxn * 2];
int uuid = 1;

int insert(char c, int last) {
    int w = c - 'a';
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

            for (int i = 0; i < 26; ++i)
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

void insert(char str[], int len, int id) {
    using SegmentTree::root;
    using SegmentTree::add;
    int x = 1;

    for (int i = 1; i <= len; ++i) {
        int w = str[i] - 'a';

        if (!nodes[x][w])
            nodes[x][w] = ++uuid;

        x = nodes[x][w];
        SegmentTree::add(SegmentTree::root[x], 1, m, id, 1);
    }
}

void build() {
    queue<pair<int, char>> q;

    for (int i = 0; i < 26; ++i)
        if (nodes[1][i])
            q.push({1, (char)(i + 'a')});

    while (!q.empty()) {
        auto [x, c] = q.front();
        q.pop();
        int l = insert(c, x);

        for (int i = 0; i < 26; ++i)
            if (nodes[l][i])
                q.push({l, (char)(i + 'a')});
    }
}

} // namespace GeneralSuffixAutomaton

vector<int> tree[maxn * 2];
int step[maxn * 2][21];
int pre[maxn][2];

void link(int x, int y) {
    tree[x].push_back(y);
}

void dfs(int x) {
    using SegmentTree::root;
    using SegmentTree::merge;

    for (int i = 1; i <= 20; ++i)
        step[x][i] = step[step[x][i - 1]][i - 1];

    for (int y : tree[x]) {
        step[y][0] = x;
        dfs(y);
        root[x] = merge(root[x], root[y], 1, m);
    }
}

void match() {
    using GeneralSuffixAutomaton::nodes;
    int x = 1, l = 0;

    for (int i = 1; i <= n; ++i) {
        int w = s[i] - 'a';

        while (x && !nodes[x][w]) {
            x = nodes[x].link;
            l = nodes[x].len;
        }

        if (!x) {
            x = 1;
        } else {
            x = nodes[x][w];
            ++l;
        }

        pre[i][0] = l;
        pre[i][1] = x;
    }
}

pair<int, int> query(int x, int len, int l, int r) {
    using SegmentTree::root;
    using SegmentTree::query;
    using GeneralSuffixAutomaton::nodes;

    for (int i = 20; i >= 0; --i)
        if (nodes[step[x][i]].len >= len)
            x = step[x][i];

    auto [cnt, pos] = query(root[x], 1, m, l, r);

    if (cnt == 0)
        return {0, l};
    else
        return {cnt, pos};
}

int main() {
    ios::sync_with_stdio(false);
    cin >> (s + 1);
    n = strlen(s + 1);

    cin >> m;

    for (int i = 1; i <= m; ++i) {
        cin >> (t + 1);
        GeneralSuffixAutomaton::insert(t, strlen(t + 1), i);
    }

    GeneralSuffixAutomaton::build();
    match();

    for (int i = 2; i <= GeneralSuffixAutomaton::uuid; ++i)
        link(GeneralSuffixAutomaton::nodes[i].link, i);

    dfs(1);

    cin >> q;

    for (int i = 1; i <= q; ++i) {
        int l, r, pl, pr;
        cin >> l >> r >> pl >> pr;

        if (pre[pr][0] < pr - pl + 1) {
            cout << l << " " << 0 << endl;
            continue;
        }

        auto [cnt, pos] = query(pre[pr][1], pr - pl + 1, l, r);
        cout << pos << " " << cnt << endl;
    }

    return 0;
}