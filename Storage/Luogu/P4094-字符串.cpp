#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

constexpr int maxn = 2e5 + 10;

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

    int insert(char c, int pos) {
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
                nodes[x].link = nodes[q].link = nq;

                for (; p && nodes[p][w] == q; p = nodes[p].link)
                    nodes[p][w] = nq;
            }
        }

        return last;
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

int n, m;
char str[maxn];
SuffixAutomaton sam;
Node seg[maxn * 50];
int uuid, root[maxn * 2], pos[maxn];
vector<int> tree[maxn * 2];
int step[maxn * 2][19];

void pushup(int x) {
    seg[x].sum = seg[seg[x].ls].sum + seg[seg[x].rs].sum;
}

void add(int &x, int l, int r, int p) {
    if (!x)
        x = ++uuid;

    if (l == r) {
        ++seg[x].sum;
        return;
    }

    int mid = (l + r) / 2;

    if (p <= mid)
        add(seg[x].ls, l, mid, p);
    else
        add(seg[x].rs, mid + 1, r, p);

    pushup(x);
}

int query(int x, int l, int r, int ql, int qr) {
    if (!x)
        return 0;

    if (ql <= l && r <= qr)
        return seg[x].sum;

    int mid = (l + r) / 2, res = 0;

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
        return id;
    }

    int mid = (l + r) / 2, id = ++uuid;
    seg[id].ls = merge(seg[x].ls, seg[y].ls, l, mid);
    seg[id].rs = merge(seg[x].rs, seg[y].rs, mid + 1, r);
    pushup(id);
    return id;
}

void link(int x, int y) {
    tree[x].push_back(y);
}

void dfs(int x) {
    for (int i = 1; i <= 18; ++i)
        step[x][i] = step[step[x][i - 1]][i - 1];

    if (!sam[x].clone)
        add(root[x], 1, n, sam[x].pos);
    
    for (int y : tree[x]) {
        step[y][0] = x;
        dfs(y);
        root[x] = merge(root[x], root[y], 1, n);
    }
}

bool check(int pos, int len, int l, int r) {
    for (int i = 18; i >= 0; --i)
        if (sam[step[pos][i]].len >= len && step[pos][i])
            pos = step[pos][i];

    return (query(root[pos], 1, n, l + len - 1, r) > 0);
}

void solve() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    a = n - a + 1;
    b = n - b + 1;
    c = n - c + 1;
    d = n - d + 1;

    int l = 0, r = min(a - b + 1, c - d + 1), ans = 0;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (check(pos[c], mid, b, a)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    cin >> (str + 1);

    for (int i = 1, j = n; i < j; ++i, --j)
        swap(str[i], str[j]);

    for (int i = 1; i <= n; ++i)
        pos[i] = sam.insert(str[i], i);

    for (int i = 2; i <= sam.size(); ++i)
        link(sam[i].link, i);

    dfs(1);

    for (int i = 1; i <= m; ++i)
        solve();

    return 0;
}