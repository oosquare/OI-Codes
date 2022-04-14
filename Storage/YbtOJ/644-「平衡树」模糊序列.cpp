#include <iostream>
#include <random>
using namespace std;

constexpr int MAXN = 3e5 + 10;

struct Node {
    int ls, rs, size, pri;
    int key, add;
};

int n, l[MAXN], r[MAXN];
Node tree[MAXN];
int root, uuid;
mt19937 gen((random_device())());

void pushup(int x) {
    tree[x].size = tree[tree[x].ls].size + tree[tree[x].rs].size + 1;
}

void update(int x, int v) {
    if (!x)
        return;

    tree[x].key += v;
    tree[x].add += v;
}

void pushdown(int x) {
    if (tree[x].add == 0)
        return;

    update(tree[x].ls, tree[x].add);
    update(tree[x].rs, tree[x].add);
    tree[x].add = 0;
}

void splitByValue(int root, int key, int & x, int & y) {
    if (!root) {
        x = y = 0;
        return;
    }

    pushdown(root);

    if (tree[root].key <= key) {
        x = root;
        splitByValue(tree[x].rs, key, tree[x].rs, y);
        pushup(x);
    } else {
        y = root;
        splitByValue(tree[y].ls, key, x, tree[y].ls);
        pushup(y);
    }
}

void splitBySize(int root, int sze, int & x, int & y) {
    if (!root) {
        x = y = 0;
        return;
    }

    pushdown(root);

    if (tree[tree[root].ls].size < sze) {
        x = root;
        splitBySize(tree[x].rs, sze - tree[tree[x].ls].size - 1, tree[x].rs, y);
        pushup(x);
    } else {
        y = root;
        splitBySize(tree[y].ls, sze, x, tree[y].ls);
        pushup(y);
    }
}

int merge(int x, int y) {
    if (!x || !y)
        return x ^ y;

    pushdown(x);
    pushdown(y);

    if (tree[x].pri > tree[y].pri) {
        tree[x].rs = merge(tree[x].rs, y);
        pushup(x);
        return x;
    } else {
        tree[y].ls = merge(x, tree[y].ls);
        pushup(y);
        return y;
    }
}

int create(int key) {
    ++uuid;
    tree[uuid] = { 0, 0, 1, (int) gen(), key, 0 };
    return uuid;
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("vague.in", "r", stdin);
    freopen("vague.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> l[i] >> r[i];

    for (int i = 1; i <= n; ++i) {
        int x, y, z, w;
        splitByValue(root, l[i] - 1, x, y);
        splitByValue(y, r[i] - 1, y, z);
        
        x = merge(x, create(l[i]));
        update(y, 1);
        splitBySize(z, 1, w, z);
        root = merge(merge(x, y), z);
    }

    cout << tree[root].size << endl;
    return 0;
}
