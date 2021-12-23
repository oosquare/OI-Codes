#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

constexpr int maxn = 250000 + 10;

class SuffixAutomaton {
public:
    struct Node {
        int next[26], link, length;
        bool cloned;

        Node() {
            for (int i = 0; i < 26; ++i)
                next[i] = 0;

            link = length = 0;
            cloned = false;
        }

        int &operator[](int x) {
            return next[x];
        }
    };

    SuffixAutomaton() {
        clear();
    }

    void clear() {
        nodes.clear();
        nodes.push_back(Node());
        nodes[0].link = -1;
        last = 0;
    }

    int size() {
        return nodes.size() - 1;
    }

    Node &operator[](int x) {
        return nodes[x];
    }

    void insert(char c) {
        int x = create(), p = last, w = c - 'a';
        nodes[x].length = nodes[p].length + 1;

        for (; p != -1 && !nodes[p][w]; p = nodes[p].link)
            nodes[p][w] = x;

        if (p == -1) {
            nodes[x].link = 0;
        } else {
            int q = nodes[p][w];

            if (nodes[q].length == nodes[p].length + 1) {
                nodes[x].link = q;
            } else {
                int nq = create(q);
                nodes[nq].length = nodes[p].length + 1;
                nodes[nq].cloned = true;
                nodes[x].link = nodes[q].link = nq;

                for (; p != -1 && nodes[p][w] == q; p = nodes[p].link)
                    nodes[p][w] = nq;
            }
        }
    
        last = x;
    }

    void insert(char str[], int len) {
        for (int i = 1; i <= len; ++i)
            insert(str[i]);
    }

private:
    vector<Node> nodes;
    int last;

    int create(int id = -1) {
        nodes.push_back(id == -1 ? Node() : nodes[id]);
        return nodes.size() - 1;
    }
};

class SegmentTree {
public:
    void init(int n) {
        build(1, 1, n);
    }

    void assign(int l, int r, int v) {
        assign(1, l, r, v);
    }

    int query(int l, int r) {
        return query(1, l, r);
    }
private:
    struct Node {
        int left, right;
        int max, assign;
    };

    Node tree[maxn * 4];

    void pushup(int x) {
        tree[x].max = max(tree[x * 2].max, tree[x * 2 + 1].max);
    }

    void build(int x, int l, int r) {
        tree[x].left = l;
        tree[x].right = r;

        if (l == r)
            return;

        int mid = (l + r) / 2;
        build(x * 2, l, mid);
        build(x * 2 + 1, mid + 1, r);
    }

    void assign(int x, int l, int r, int v) {
        if (l <= tree[x].left && tree[x].right <= r) {
            tree[x].max = max(tree[x].max, v);
            tree[x].assign = max(tree[x].assign, v);
            return;
        }

        int mid = (tree[x].left + tree[x].right) / 2;

        if (l <= mid)
            assign(x * 2, l, r, v);

        if (mid < r)
            assign(x * 2 + 1, l, r, v);

        pushup(x);
    }

    int query(int x, int l, int r) {
        if (l <= tree[x].left && tree[x].right <= r)
            return tree[x].max;

        int mid = (tree[x].left + tree[x].right) / 2, res = tree[x].assign;

        if (l <= mid)
            res = max(res, query(x * 2, l, r));

        if (mid < r)
            res = max(res, query(x * 2 + 1, l, r));

        return res;
    }
};

char str[maxn];
int n;
SuffixAutomaton sam;
SegmentTree seg;
int cnt[maxn * 2];
vector<int> tree[maxn * 2];

void link(int x, int y) {
    tree[x].push_back(y);
}

void dfs(int x) {
    if (!sam[x].cloned)
        cnt[x] = 1;

    for (int y : tree[x]) {
        dfs(y);
        cnt[x] += cnt[y];
    }

    if (sam[x].link != -1)
        seg.assign(sam[sam[x].link].length + 1, sam[x].length, cnt[x]);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> (str + 1);
    n = strlen(str + 1);
    sam.insert(str, n);
    seg.init(n);

    for (int i = 1; i <= sam.size(); ++i)
        link(sam[i].link, i);

    dfs(0);

    for (int i = 1; i <= n; ++i)
        cout << seg.query(i, i) << endl;

    return 0;
}