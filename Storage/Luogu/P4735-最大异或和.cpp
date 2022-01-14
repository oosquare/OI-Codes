#include <iostream>
using namespace std;

constexpr int maxn = 6e5 + 10;

struct Node {
    int next[2];
    int cnt;

    int &operator[](int x) {
        return next[x];
    }
};

int n, m, a[maxn], sum[maxn], len;
int uuid;
Node tree[maxn * 100];
int root[maxn];

void insert(int now, int pre, int pos, int num) {
    if (pos == -1)
        return;

    int w = ((num >> pos) & 1);
    tree[now][w ^ 1] = tree[pre][w ^ 1];
    tree[now][w] = ++uuid;
    tree[tree[now][w]].cnt = tree[tree[pre][w]].cnt + 1;
    insert(tree[now][w], tree[pre][w], pos - 1, num);
}

int query(int l, int r, int pos, int num) {
    if (pos == -1)
        return 0;

    int w = ((num >> pos) & 1);

    if (tree[tree[r][w ^ 1]].cnt > tree[tree[l][w ^ 1]].cnt)
        return (query(tree[l][w ^ 1], tree[r][w ^ 1], pos - 1, num) | (1 << pos));
    else
        return query(tree[l][w], tree[r][w], pos - 1, num);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    len = n;
    root[0] = ++uuid;
    insert(root[0], 0, 25, 0);

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        sum[i] = sum[i - 1] ^ a[i];
        root[i] = ++uuid;
        insert(root[i], root[i - 1], 25, sum[i]);
    }

    for (int i = 1; i <= m; ++i) {
        char op;
        int l, r, x;
        cin >> op;

        if (op == 'A') {
            ++len;
            cin >> a[len];
            root[len] = ++uuid;
            sum[len] = sum[len - 1] ^ a[len];
            insert(root[len], root[len - 1], 25, sum[len]);
        } else {
            cin >> l >> r >> x;

            if (l != 1)
                cout << query(root[l - 2], root[r - 1], 25, sum[len] ^ x) << endl;
            else
                cout << query(0, root[r - 1], 25, sum[len] ^ x) << endl;
        }
    }

    return 0;
}