#pragma Clang optimize(3)
#include <iostream>
#include <vector>
#include <cstring>

constexpr int MAX_N = 1e5 + 10;

class SuffixAutomaton {
public:
    struct Node {
        int next[26];
        int link, len;

        Node() {
            for (int i = 0; i < 26; ++i)
                next[i] = 0;
            
            link = len = 0;
        }

        int & operator[](int x) {
            return next[x];
        } 
    };

    void init() {
        tot = last = 1;
        nodes[tot] = Node();
    }

    int add(char c) {
        int x = create(), p = last, w = c - 'a';
        last = x;

        nodes[x].len = nodes[p].len + 1;
        for (; p && nodes[p][w] == 0; p = nodes[p].link)
            nodes[p][w] = x;
        
        if (p == 0) {
            nodes[x].link = 1;
        } else {
            int q = nodes[p][w];

            if (nodes[q].len == nodes[p].len + 1) {
                nodes[x].link = q;
            } else {
                int nq = create(q);
                nodes[nq].len = nodes[p].len + 1;
                nodes[q].link = nodes[x].link = nq;

                for (; p && nodes[p][w] == q; p = nodes[p].link)
                    nodes[p][w] = nq;
            }
        }

        return x;
    }

    int size() {
        return tot;
    }

    Node & operator[](int x) {
        return nodes[x];
    }

private:
    Node nodes[MAX_N * 2];
    int tot, last;

    int create(int id = -1) {
        nodes[++tot] = (id == -1 ? Node() : nodes[id]);
        return tot;
    }
};

SuffixAutomaton sam;

class LinkCutTree {
public:
    void link(int fa, int x) {
        tree[x].fa = fa;
    }

    void access(int x, int top, std::pair<int, int> seq[], int & len) {
        len = 0;

        for (int y = 0; x != 0; y = x, x = tree[y].fa) {
            splay(x);
            tree[x].rs = y;
            seq[++len] = { sam[x].len, tree[x].top };
            update(x, top);
        }
    }
private:
    struct Node {
        int ls, rs, fa;
        int top, assign;

        int & operator[](int x) {
            return (x == 0 ? ls : rs);
        }
    };

    Node tree[MAX_N * 2];
    int stk[MAX_N * 2];

    bool isRoot(int x) {
        return (tree[tree[x].fa].ls != x && tree[tree[x].fa].rs != x);
    }

    int which(int x) {
        return (tree[tree[x].fa].rs == x ? 1 : 0);
    }

    void update(int x, int top) {
        if (!x)
            return;
            
        tree[x].top = top;
        tree[x].assign = top;
    }

    void pushdown(int x) {
        if (tree[x].assign == 0)
            return;

        update(tree[x].ls, tree[x].assign);
        update(tree[x].rs, tree[x].assign);
        tree[x].assign = 0;        
    }

    void rotate(int x) {
        int y = tree[x].fa, z = tree[y].fa, k = which(x), w = tree[x][k ^ 1];

        if (!isRoot(y))
            tree[z][which(y)] = x;
        
        tree[y].fa = x;
        tree[x].fa = z;
        tree[x][k ^ 1] = y;
        tree[y][k] = w;

        if (w)
            tree[w].fa = y;
    }
    
    void splay(int x) {
        int top = 0;
        stk[++top] = x;

        for (int y = x; !isRoot(y); y = tree[y].fa)
            stk[++top] = tree[y].fa;

        while (top)
            pushdown(stk[top--]);
        
        for (int y; y = tree[x].fa, !isRoot(x); rotate(x))
            if (!isRoot(y))
                rotate(which(x) == which(y) ? y : x);
    }
};

LinkCutTree lct;

class SegmentTree {
public:
    void init(int n) {
        build(1, 1, n);
    }

    void add(int l, int r, unsigned long long v) {
        add(1, l, r, v);
    }

    unsigned long long querySum(int l, int r) {
        return query(1, l, r, 1);
    }

    unsigned long long querrySquare(int l, int r) {
        return query(1, l, r, 2);
    }
private:
    struct Node {
        int left, right;
        unsigned long long sum, sqr, add;
    };

    Node tree[MAX_N * 4];

    void pushup(int x) {
        tree[x].sum = tree[x * 2].sum + tree[x * 2 + 1].sum;
        tree[x].sqr = tree[x * 2].sqr + tree[x * 2 + 1].sqr;
    }

    void update(int x, unsigned long long v) {
        tree[x].add += v;
        tree[x].sum += 1ull * (tree[x].right - tree[x].left + 1) * v;
        tree[x].sqr += 1ull * (tree[x].right - tree[x].left + 1) * (tree[x].left + tree[x].right) / 2 * v;
    }

    void pushdown(int x) {
        if (tree[x].add == 0)
            return;
        
        update(x * 2, tree[x].add);
        update(x * 2 + 1, tree[x].add);
        tree[x].add = 0;
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

    void add(int x, int l, int r, unsigned long long v) {
        if (l <= tree[x].left && tree[x].right <= r) {
            update(x, v);
            return;
        }

        int mid = (tree[x].left + tree[x].right) / 2;
        pushdown(x);

        if (l <= mid)
            add(x * 2, l, r, v);
        
        if (mid < r)
            add(x * 2 + 1, l, r, v);
        
        pushup(x);
    }

    unsigned long long query(int x, int l, int r, int type) {
        if (l <= tree[x].left && tree[x].right <= r)
            return (type == 1 ? tree[x].sum : tree[x].sqr);
        
        unsigned long long res = 0;
        int mid = (tree[x].left + tree[x].right) / 2;
        pushdown(x);

        if (l <= mid)
            res += query(x * 2, l, r, type);
        
        if (mid < r)
            res += query(x * 2 + 1, l, r, type);

        return res;
    }
};

int n;
SegmentTree seg;
char str[MAX_N];
std::vector<int> tree[MAX_N * 2];
int id[MAX_N], pos[MAX_N * 2];
std::vector<std::pair<int, int>> ranges[MAX_N * 2];
int len;
std::pair<int, int> seq[MAX_N * 2];
unsigned long long ans;

void link(int x, int y) {
    tree[x].push_back(y);
}

void dfs(int x) {
    for (int y : tree[x]) {
        dfs(y);
        pos[x] = pos[y];
    }
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("substr.in", "r", stdin);
    std::freopen("substr.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    
    std::cin >> (str + 1);
    n = std::strlen(str + 1);
    sam.init();

    for (int i = 1; i <= n; ++i) {
        id[i] = sam.add(str[i]);
        pos[id[i]] = i;
    }

    for (int i = 2; i <= sam.size(); ++i) {
        link(sam[i].link, i);
        lct.link(sam[i].link, i);
    }
    
    dfs(1);

    for (int i = 2; i <= sam.size(); ++i)
        ranges[pos[i]].push_back({ pos[i] - sam[i].len + 1, pos[i] - sam[sam[i].link].len });
    
    for (int i = 2; i <= sam.size(); ++i)
        ans += sam[i].len - sam[sam[i].link].len;

    ans = (ans % 2 == 0 ? ans / 2 * (ans + 1) : (ans + 1) / 2 * ans);
    seg.init(n);

    for (int i = 1; i <= n; ++i) {
        seg.add(1, i, 1);
        lct.access(id[i], i, seq, len);
        int p = 0;

        for (int j = len; j >= 2; --j) {
            auto [l, r] = seq[j];

            if (!l)
                continue;
            
            if (r)
                seg.add(r - l + 1, r - p, -1);
            
            p = l;
        }

        for (auto [l, r] : ranges[i]) {
            ans -= seg.querrySquare(l, r);
            ans += seg.querySum(l, r) * (l - 1);

            if (r < i)
                ans -= seg.querySum(r + 1, i) * (r - l + 1);
        }
    }

    std::cout << ans << std::endl;
    return 0;
}
