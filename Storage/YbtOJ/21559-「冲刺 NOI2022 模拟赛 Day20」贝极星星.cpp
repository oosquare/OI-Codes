#include <iostream>
#include <random>

template <typename T = int> T read() {
    T x = 0, s = 1;
    int c = std::getchar();

    for (; c < '0' || c > '9'; c = std::getchar())
        if (c == '-')
            s = -1;

    for (; '0' <= c && c <= '9'; c = std::getchar())
        x = x * 10 + c - '0';

    return x * s;
}

constexpr int MAX_N = 1000000 + 10;
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;

struct Node {
    int ls, rs, size, priority;
    long long key, last, first, delta;
};

int n;
int a[MAX_N];
Node tree[MAX_N];
int tot, root;

int create(long long key) {
    static std::mt19937 gen((std::random_device())());
    static std::uniform_int_distribution<> dist(0, 0x3f3f3f3f);

    ++tot;
    tree[tot].ls = tree[tot].rs = 0;
    tree[tot].size = 1;
    tree[tot].priority = dist(gen);
    tree[tot].key = key;
    tree[tot].last = key;
    tree[tot].first = tree[tot].delta = 0;
    return tot;
}

void pushup(int x) {
    if (!x)
        return;

    tree[x].size = tree[tree[x].ls].size + 1 + tree[tree[x].rs].size;
    tree[x].last = (tree[x].rs ? tree[tree[x].rs].last : tree[x].key);
}

void update(int x, long long first, long long delta) {
    if (!x)
        return;

    tree[x].key += first + tree[tree[x].ls].size * delta;
    tree[x].last += first + (tree[x].size - 1) * delta;
    tree[x].first += first;
    tree[x].delta += delta;
}

void pushdown(int x) {
    if (!x || (tree[x].first == 0 && tree[x].delta == 0))
        return;

    update(tree[x].ls, tree[x].first, tree[x].delta);
    update(tree[x].rs, tree[x].first + (tree[tree[x].ls].size + 1) * tree[x].delta, tree[x].delta);
    tree[x].first = tree[x].delta = 0;
}

void split(int root, int sze, int &x, int &y) {
    if (!root) {
        x = y = 0;
        return;
    }

    pushdown(root);

    if (tree[tree[root].ls].size < sze) {
        x = root;
        split(tree[x].rs, sze - tree[tree[root].ls].size - 1, tree[x].rs, y);
        pushup(x);
    } else {
        y = root;
        split(tree[y].ls, sze, x, tree[y].ls);
        pushup(y);
    }
}

int merge(int x, int y) {
    if (!x || !y)
        return x ^ y;

    if (tree[x].priority > tree[y].priority) {
        pushdown(x);
        tree[x].rs = merge(tree[x].rs, y);
        pushup(x);
        return x;
    } else {
        pushdown(y);
        tree[y].ls = merge(x, tree[y].ls);
        pushup(y);
        return y;
    }
}

inline int toSize(int i) { return i + 1; }

inline int toIndex(int i) { return i - 1; }

int find(int i) {
    int x = root;
    int ans = i, pos = tree[tree[x].ls].size + 1;
    long long last = -INF;

    while (x) {
        pushdown(x);
        long long prev = (tree[x].ls ? tree[tree[x].ls].last : last);

        if (prev + 1ll * a[i] * toIndex(pos) >= tree[x].key) {
            ans = toIndex(pos);
            x = tree[x].ls;
            pos = pos - tree[x].size + tree[tree[x].ls].size;
        } else {
            last = tree[x].key;
            x = tree[x].rs;
            pos = pos + tree[tree[x].ls].size + 1;
        }
    }

    return ans;
}

void modify(int i) {
    int k = find(i);
    int x, y;
    split(root, toSize(k) - 1, x, y);
    int id = create(tree[x].last);
    y = merge(id, y);
    update(y, 1ll * a[i] * k, a[i]);
    root = merge(x, y);
}

long long output(int x) {
    if (!x)
        return 0;

    pushdown(x);
    return std::max(tree[x].key, std::max(output(tree[x].ls), output(tree[x].rs)));
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("Bella.in", "r", stdin);
    std::freopen("Bella.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    n = read();

    for (int i = 1; i <= n; ++i)
        a[i] = read();

    root = create(0);

    for (int i = 1; i <= n; ++i)
        modify(i);

    std::cout << output(root) << std::endl;
    return 0;
}
