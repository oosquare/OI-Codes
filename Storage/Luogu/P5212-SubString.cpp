#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

constexpr int maxn = 4e6 + 10;

class LinkCutTree {
public:
    void link(int x, int y) {
        makeRoot(x);

        if (findRoot(y) != x)
            tree[x].father = y;
    }

    void cut(int x, int y) {
        makeRoot(x);

        if (findRoot(y) == x && tree[y].father == x && !tree[y].left)
            tree[x].right = tree[y].father = 0;
    }

    int query(int x) {
        splay(x);
        return tree[x].key;
    }

    void add(int x, int v) {
        updateAdd(split(1, x), v);
    }

    void init(int x, int v) {
        tree[x] = {0, 0, 0, v, 0, false};
    }

private:
    struct Node {
        int left, right, father;
        int key, add;
        bool rev;

        int &operator[](int x) {
            return (x == 0 ? left : right);
        }
    };

    Node tree[maxn * 2];
    int st[maxn * 2], top;

    void updateReverse(int x) {
        tree[x].rev ^= 1;
        swap(tree[x].left, tree[x].right);
    }

    void updateAdd(int x, int v) {
        tree[x].add += v;
        tree[x].key += v;
    }

    void pushdown(int x) {
        if (tree[x].rev) {
            if (tree[x].left)
                updateReverse(tree[x].left);

            if (tree[x].right)
                updateReverse(tree[x].right);

            tree[x].rev = false;
        }

        if (tree[x].add) {
            if (tree[x].left)
                updateAdd(tree[x].left, tree[x].add);

            if (tree[x].right)
                updateAdd(tree[x].right, tree[x].add);

            tree[x].add = 0;
        }
    }

    int which(int x) {
        return (tree[tree[x].father].right == x ? 1 : 0);
    }

    bool isRoot(int x) {
        return (tree[tree[x].father].left != x && tree[tree[x].father].right != x);
    }

    void rotate(int x) {
        int y = tree[x].father, z = tree[y].father, k = which(x), w = tree[x][k ^ 1];

        if (!isRoot(y))
            tree[z][which(y)] = x;

        tree[x][k ^ 1] = y;
        tree[y][k] = w;

        if (w)
            tree[w].father = y;
        
        tree[y].father = x;
        tree[x].father = z;
    }

    void splay(int x) {
        st[++top] = x;

        for (int p = x; !isRoot(p); p = tree[p].father)
            st[++top] = tree[p].father;

        while (top)
            pushdown(st[top--]);

        for (int p; p = tree[x].father, !isRoot(x); rotate(x))
            if (!isRoot(p))
                rotate(which(p) == which(x) ? p : x);
    }

    void access(int x) {
        for (int s = 0; x; s = x, x = tree[x].father) {
            splay(x);
            tree[x].right = s;
        }
    }

    void makeRoot(int x) {
        access(x);
        splay(x);
        updateReverse(x);
    }

    int findRoot(int x) {
        access(x);
        splay(x);

        while (tree[x].left) {
            pushdown(x);
            x = tree[x].left;
        }

        splay(x);
        return x;
    }

    int split(int x, int y) {
        makeRoot(x);
        access(y);
        splay(y);
        return y;
    }
};

class SuffixAutomaton {
public:
    struct Node {
        int next[2], link, len;
        bool clone;

        Node() : link(0), len(0), clone(false) {
            for (int i = 0; i < 2; ++i)
                next[i] = 0;
        }

        int &operator[](int x) {
            return next[x];
        }
    };

    SuffixAutomaton() : uuid(1), last(1) {}

    int size() {
        return uuid - 1;
    }

    Node &operator[](int x) {
        return nodes[x];
    }

    void init(LinkCutTree *p) {
        lct = p;
        lct->init(1, 0);
    }

    void insert(char c) {
        int x = create(), p = last, w = c - 'A';
        last = x;
        nodes[x].len = nodes[p].len + 1;
        lct->init(x, 0);

        for (; p && !nodes[p][w]; p = nodes[p].link)
            nodes[p][w] = x;

        if (!p) {
            nodes[x].link = 1;
            lct->link(1, x);
        } else {
            int q = nodes[p][w];

            if (nodes[q].len == nodes[p].len + 1) {
                nodes[x].link = q;
                lct->link(q, x);
            } else {
                int nq = create(q);
                nodes[nq].clone = true;
                nodes[nq].len = nodes[p].len + 1;
                lct->cut(nodes[q].link, q);
                nodes[q].link = nodes[x].link = nq;
                lct->init(nq, lct->query(q));
                lct->link(nodes[nq].link, nq);
                lct->link(nq, q);
                lct->link(nq, x);

                for (; p && nodes[p][w] == q; p = nodes[p].link)
                    nodes[p][w] = nq;
            }
        }

        lct->add(x, 1);
    }

    void insert(char str[], int len) {
        for (int i = 1; i <= len; ++i)
            insert(str[i]);
    }

private:
    Node nodes[maxn * 2];
    int uuid, last;
    LinkCutTree *lct;

    int create(int id = -1) {
        nodes[++uuid] = (id == -1 ? Node() : nodes[id]);
        return uuid;
    }
};

int q, mask;
char type[10], str[maxn];
LinkCutTree lct;
SuffixAutomaton sam;

void decode(char str[], int len, int mask) {
    for (int j = 0; j < len; ++j) {
        mask = (mask * 131 + j) % len;
        char t = str[j];
        str[j] = str[mask];
        str[mask] = t;
    }
}

int query(char str[], int len) {
    int x = 1;

    for (int i = 1; i <= len; ++i) {
        int w = str[i] - 'A';

        if (!sam[x][w])
            return 0;

        x = sam[x][w];
    }

    return lct.query(x);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> q;
    cin >> (str + 1);

    sam.init(&lct);
    sam.insert(str, strlen(str + 1));

    for (int i = 1; i <= q; ++i) {
        cin >> (type + 1) >> (str + 1);
        int len = strlen(str + 1);
        decode(str + 1, len, mask);

        if (type[1] == 'Q') {
            int res = query(str, len);
            cout << res << endl;
            mask ^= res;
        } else {
            sam.insert(str, len);
        }
    }

    return 0;
}