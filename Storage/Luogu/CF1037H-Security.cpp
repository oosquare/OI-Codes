#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

constexpr int maxn = 1e5 + 10;

class SuffixAutomaton {
public:
    struct Node {
        int next[26], link, len, pos;
        bool clone;

        Node() : link(0), len(0), pos(0), clone(false) {
            for (int i = 0; i < 26; ++i)
                next[i] = 0;
        }

        int &operator[](int x) {
            return next[x];
        }
    };

    SuffixAutomaton() : uuid(1), last(1) {}

    int size() {
        return uuid;
    }

    Node &operator[](int x) {
        return nodes[x];
    }

    void insert(char c, int pos) {
        int x = create(), p = last, w = c - 'a';
        last = x;
        nodes[x].len = nodes[p].len + 1;
        nodes[x].pos = pos;

        for (; p && !nodes[p][w]; p = nodes[p].link)
            nodes[p][w] = x;

        if (!p) {
            nodes[x].link = 1;
        } else {
            int q = nodes[p][w];

            if (nodes[q].len == nodes[p].len + 1) {
                nodes[x].link = q;
            } else {
                int nq = create(q);
                nodes[nq].clone = true;
                nodes[nq].len = nodes[p].len + 1;
                nodes[q].link = nodes[x].link = nq;

                for (; p && nodes[p][w] == q; p = nodes[p].link)
                    nodes[p][w] = nq;
            }
        }
    }

    void insert(char str[], int len) {
        for (int i = 1; i <= len; ++i)
            insert(str[i], i);
    }

private:
    Node nodes[maxn * 2];
    int uuid, last;

    int create(int id = -1) {
        nodes[++uuid] = (id == -1 ? Node() : nodes[id]);
        return uuid;
    }
};

struct Node {
    int ls, rs;
    int sum;
};

int n, m, q, l, r;
char s[maxn], t[maxn];
SuffixAutomaton sam;
Node seg[maxn * 50];
int uuid, root[maxn * 2];
vector<int> tree[maxn * 2];
char ans[maxn];

void pushup(int x) {
    seg[x].sum = seg[seg[x].ls].sum + seg[seg[x].rs].sum;
}

void add(int &x, int l, int r, int p, int v) {
    if (!x)
        x = ++uuid;

    if (l == r) {
        seg[x].sum += v;
        return;
    }

    int mid = (l + r) >> 1;

    if (p <= mid)
        add(seg[x].ls, l, mid, p, v);
    else
        add(seg[x].rs, mid + 1, r, p, v);

    pushup(x);
}

int query(int x, int l, int r, int ql, int qr) {
    if (!x)
        return 0;

    if (ql <= l && r <= qr)
        return seg[x].sum;

    int mid = (l + r) >> 1, res = 0;

    if (ql <= mid)
        res += query(seg[x].ls, l, mid, ql, qr);

    if (mid < qr)
        res += query(seg[x].rs, mid + 1, r, ql, qr);

    return res;
}

int merge(int x, int y, int l, int r) {
    if (!x || !y)
        return x + y;

    if (l == r) {
        int id = ++uuid;
        seg[id].sum = seg[x].sum + seg[y].sum;
        return x;
    }

    int mid = (l + r) >> 1, id = ++uuid;
    seg[id].ls = merge(seg[x].ls, seg[y].ls, l, mid);
    seg[id].rs = merge(seg[x].rs, seg[y].rs, mid + 1, r);
    pushup(id);
    return id;
}

void link(int x, int y) {
    tree[x].push_back(y);
}

void dfs(int x) {
    if (!sam[x].clone)
        add(root[x], 0, n, sam[x].pos, 1);

    for (int y : tree[x]) {
        dfs(y);
        root[x] = merge(root[x], root[y], 0, n);
    }
}

bool setContain(int x, int len, int l, int r) {
    if (l + len - 1 > r)
        return false;

    return (query(root[x], 0, n, l + len - 1, r) > 0);
}

bool nodeContain(int x, int len, int l, int r) {
    return l + len - 1 <= sam[x].pos && sam[x].pos <= r;
}

bool find(int x, int len, bool lim) {
    if (!setContain(x, len, l, r))
        return false;

    if (!lim && setContain(x, len, l, r)) {
        ans[len + 1] = '\0';
        return true;
    }

    for (int i = 0; i < 26; ++i) {
        if (!sam[x][i])
            continue;

        if (lim && len < m && (char)(i + 'a') < t[len + 1])
            continue;

        ans[len + 1] = i + 'a';
        bool found = find(sam[x][i], len + 1, lim && len < m && (char)(i + 'a') == t[len + 1]);

        if (found)
            return true;

        ans[len + 1] = '\0';
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> (s + 1) >> q;
    n = strlen(s + 1);
    sam.insert(s, n);

    for (int i = 2; i <= sam.size(); ++i)
        link(sam[i].link, i);

    dfs(1);

    for (int i = 1; i <= q; ++i) {
        cin >> l >> r >> (t + 1);
        m = strlen(t + 1);

        if (find(1, 0, true))
            cout << (ans + 1) << endl;
        else
            cout << -1 << endl;
    }

    return 0;
}