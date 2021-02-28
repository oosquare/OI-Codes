#include <bits/stdc++.h>
using namespace std;

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

int read() {
    int x = 0, s = 1;
    char c = mygetchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = mygetchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = mygetchar();
    }
    return x * s;
}

template <typename T> class FHQTreap {
  public:
    FHQTreap() { Root = NULL; }

    ~FHQTreap() {
        if (Root)
            delete Root;
    }

    void insert(T key) {
        Node *x, *y;
        split1(Root, key, x, y);
        Root = merge(merge(x, create(key)), y);
    }

    void remove(T key) {
        Node *x, *y, *z;
        split2(Root, key, x, z);
        split1(x, key, x, y);
        if (y) {
            y = merge(y->Left, y->Right);
        }
        Root = merge(merge(x, y), z);
    }

    int rank(T key) {
        Node *x, *y;
        int ans;
        split1(Root, key, x, y);
        ans = (x ? x->Size : 0) + 1;
        Root = merge(x, y);
        return ans;
    }

    T at(int r) {
        if (Root == NULL || r > Root->Size)
            return T();
        Node *root = Root;
        while (root) {
            int ls = root->Left ? root->Left->Size : 0;
            if (ls + 1 == r) {
                break;
            } else if (ls + 1 > r) {
                root = root->Left;
            } else {
                r -= ls + 1;
                root = root->Right;
            }
        }
        return root->Key;
    }

    T previous(T key) {
        Node *x, *y, *root;
        T ans;
        split1(Root, key, x, y);
        root = x;
        if (root == NULL)
            return std::numeric_limits<T>::min();
        while (root->Right)
            root = root->Right;
        ans = root->Key;
        Root = merge(x, y);
        return ans;
    }

    T next(T key) {
        Node *x, *y, *root;
        T ans;
        split2(Root, key, x, y);
        root = y;
        if (root == NULL)
            return std::numeric_limits<T>::max();
        while (root->Left)
            root = root->Left;
        ans = root->Key;
        Root = merge(x, y);
        return ans;
    }

    int size() { return (Root ? Root->Size : 0); }

    bool find(T key) {
        Node *x, *y, *z;
        split2(Root, key, x, z);
        split1(x, key, x, y);
        bool ans;
        if (y)
            ans = true;
        else
            ans = false;
        Root = merge(merge(x, y), z);
        return ans;
    }

  private:
    struct Node {
        T Key;
        Node *Left, *Right;
        int Size, Priority;

        Node(T key, int pri)
            : Key(key), Left(NULL), Right(NULL), Size(1), Priority(pri) {}
        ~Node() {
            if (Left)
                delete Left;
            if (Right)
                delete Right;
        }
    } * Root;
    int Seed;

    int random() { return Seed = int((Seed + 3) * 482711ll % 2147483647); }

    Node *create(T key) {
        Node *root = new Node(key, random());
        return root;
    }

    void pushup(Node *root) {
        if (root)
            root->Size = (root->Left ? root->Left->Size : 0) +
                         (root->Right ? root->Right->Size : 0) + 1;
    }

    void split1(Node *root, T key, Node *&x, Node *&y) {
        if (root == NULL) {
            x = y = NULL;
            return;
        }
        if (root->Key < key) {
            x = root;
            split1(root->Right, key, root->Right, y);
        } else {
            y = root;
            split1(root->Left, key, x, root->Left);
        }
        pushup(root);
    }

    void split2(Node *root, T key, Node *&x, Node *&y) {
        if (root == NULL) {
            x = y = NULL;
            return;
        }
        if (!(key < root->Key)) {
            x = root;
            split2(root->Right, key, root->Right, y);
        } else {
            y = root;
            split2(root->Left, key, x, root->Left);
        }
        pushup(root);
    }

    Node *merge(Node *x, Node *y) {
        if (x == NULL)
            return y;
        if (y == NULL)
            return x;
        if (x->Priority > y->Priority) {
            x->Right = merge(x->Right, y);
            pushup(x);
            return x;
        } else {
            y->Left = merge(x, y->Left);
            pushup(y);
            return y;
        }
    }
};

const int maxn = 5e4 + 5;
const int oo = 0x7fffffff;
FHQTreap<int> tree[maxn << 2];
int arr[maxn], n, m;

void build(int x, int l, int r) {
    for (int i = l; i <= r; ++i)
        tree[x].insert(arr[i]);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(x << 1, l, mid);
    build(x << 1 | 1, mid + 1, r);
}

void modify(int x, int l, int r, int p, int v, int lv) {
    tree[x].remove(lv);
    tree[x].insert(v);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (p <= mid)
        modify(x << 1, l, mid, p, v, lv);
    else
        modify(x << 1 | 1, mid + 1, r, p, v, lv);
}

int qrank(int x, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr)
        return tree[x].rank(v) - 1;
    int res = 0, mid = (l + r) >> 1;
    if (ql <= mid)
        res += qrank(x << 1, l, mid, ql, qr, v);
    if (mid < qr)
        res += qrank(x << 1 | 1, mid + 1, r, ql, qr, v);
    return res;
}

inline int qrank(int l, int r, int v) { return qrank(1, 1, n, l, r, v) + 1; }

int qvalue(int l, int r, int k) {
    int nl = 0, nr = 1e8 + 5, ans = 0;
    while (nl <= nr) {
        int mid = (nl + nr) >> 1;
        if (qrank(l, r, mid) - 1 < k) {
            ans = mid;
            nl = mid + 1;
        } else {
            nr = mid - 1;
        }
    }
    return ans;
}

int qprevious(int x, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr)
        return tree[x].previous(v);
    int res = -oo, mid = (l + r) >> 1;
    if (ql <= mid)
        res = max(res, qprevious(x << 1, l, mid, ql, qr, v));
    if (mid < qr)
        res = max(res, qprevious(x << 1 | 1, mid + 1, r, ql, qr, v));
    return res;
}

int qnext(int x, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr)
        return tree[x].next(v);
    int res = oo, mid = (l + r) >> 1;
    if (ql <= mid)
        res = min(res, qnext(x << 1, l, mid, ql, qr, v));
    if (mid < qr)
        res = min(res, qnext(x << 1 | 1, mid + 1, r, ql, qr, v));
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read();
    m = read();
    for (int i = 1; i <= n; ++i)
        arr[i] = read();
    build(1, 1, n);
    while (m--) {
        int op = read();
        switch (op) {
        case 1: {
            int l = read(), r = read(), x = read();
            printf("%d\n", qrank(l, r, x));
            break;
        }
        case 2: {
            int l = read(), r = read(), k = read();
            printf("%d\n", qvalue(l, r, k));
            break;
        }
        case 3: {
            int p = read(), x = read();
            modify(1, 1, n, p, x, arr[p]);
            arr[p] = x;
            break;
        }
        case 4: {
            int l = read(), r = read(), x = read();
            printf("%d\n", qprevious(1, 1, n, l, r, x));
            break;
        }
        case 5: {
            int l = read(), r = read(), x = read();
            printf("%d\n", qnext(1, 1, n, l, r, x));
            break;
        }
        }
    }
    return 0;
}