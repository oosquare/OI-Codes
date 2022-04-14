#include <iostream>

using namespace std;

constexpr int MAX_N = 1e5 + 10;
constexpr int MOD = 1e9 + 7;

struct Node {
    int cnt, sum, add;
};

int n, a[MAX_N];
Node tree[MAX_N * 4];
int stk1[MAX_N], stk2[MAX_N], top1, top2;
int f[MAX_N];

void pushup(int x) {
    tree[x].cnt = min(tree[x * 2].cnt, tree[x * 2 + 1].cnt);
    tree[x].sum = 0;

    if (tree[x * 2].cnt == tree[x].cnt)
        (tree[x].sum += tree[x * 2].sum) %= MOD;

    if (tree[x * 2 + 1].cnt == tree[x].cnt)
        (tree[x].sum += tree[x * 2 + 1].sum) %= MOD;
}

void update(int x, int v) {
    tree[x].cnt += v;
    tree[x].add += v;
}

void pushdown(int x) {
    if (!tree[x].add)
        return;

    update(x * 2, tree[x].add);
    update(x * 2 + 1, tree[x].add);
    tree[x].add = 0;
}

void build(int x, int l, int r) {
    tree[x].add = tree[x].sum = tree[x].cnt = 0;

    if (l == r)
        return;

    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
}

void assign(int x, int l, int r, int p, int v) {
    if (l == r) {
        tree[x].cnt = -1;
        tree[x].sum = v;
        return;
    }

    int mid = (l + r) / 2;
    pushdown(x);

    if (p <= mid)
        assign(x * 2, l, mid, p, v);
    else
        assign(x * 2 + 1, mid + 1, r, p, v);

    pushup(x);
}

void add(int x, int l, int r, int ql, int qr, int v) {
    if (l > r || ql > qr)
        return;
        
    if (ql <= l && r <= qr) {
        update(x, v);
        return;
    }

    int mid = (l + r) / 2;
    pushdown(x);

    if (ql <= mid) 
        add(x * 2, l, mid, ql, qr, v);
    
    if (mid < qr) 
        add(x * 2 + 1, mid + 1, r, ql, qr, v);

    pushup(x);
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("divide.in", "r", stdin);
    freopen("divide.out", "w", stdout);
#else
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif

    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    build(1, 1, n);

    top1 = top2 = 0;
    f[0] = 1;

    for (int i = 1; i <= n; i++) {
        assign(1, 1, n, i, f[i - 1]);

        while (top1 && a[stk1[top1]] <= a[i]) {
            add(1, 1, n, stk1[top1 - 1] + 1, stk1[top1], a[i] - a[stk1[top1]]);
            --top1;
        }

        stk1[++top1] = i;

        while (top2 && a[stk2[top2]] >= a[i]) {
            add(1, 1, n, stk2[top2 - 1] + 1, stk2[top2], a[stk2[top2]] - a[i]);
            --top2;
        }

        stk2[++top2] = i;

        add(1, 1, n, 1, i - 1, -1);
        f[i] = tree[1].sum;
    }

    cout << f[n] << endl;

    return 0;
}
