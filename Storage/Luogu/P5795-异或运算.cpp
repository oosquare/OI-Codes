#include <iostream>
#include <vector>
using namespace std;

constexpr int maxn = 1000 + 10;
constexpr int maxm = 3e5 + 10;

struct Node {
    int next[2];
    int cnt;

    int &operator[](int x) {
        return next[x];
    }
};

int n, m, p, u, d, l, r, k, x[maxn], y[maxm];
Node tree[maxm * 100];
int uuid, root[maxm];

void insert(int &x, int y, int pos, int num) {
    x = ++uuid;
    tree[x] = tree[y];
    ++tree[x].cnt;

    if (pos == -1)
        return;

    int w = ((num >> pos) & 1);
    insert(tree[x][w], tree[y][w], pos - 1, num);
}

int query(vector<int> &add, vector<int> &del, const vector<int> &num, int pos, int rk) {
    if (pos == -1)
        return 0;

    int sum = 0;

    for (int i = 0, s = (int)add.size(); i < s; ++i) {
        int w = ((num[i] >> pos) & 1);
        sum += tree[tree[add[i]][w ^ 1]].cnt;
    }

    for (int i = 0, s = (int)del.size(); i < s; ++i) {
        int w = ((num[i] >> pos) & 1);
        sum -= tree[tree[del[i]][w ^ 1]].cnt;
    }

    if (rk <= sum) {
        for (int i = 0, s = (int)add.size(); i < s; ++i) {
            int w = ((num[i] >> pos) & 1);
            add[i] = tree[add[i]][w ^ 1];
        }

        for (int i = 0, s = (int)del.size(); i < s; ++i) {
            int w = ((num[i] >> pos) & 1);
            del[i] = tree[del[i]][w ^ 1];
        }

        return (query(add, del, num, pos - 1, rk) | (1 << pos));
    } else {
        for (int i = 0, s = (int)add.size(); i < s; ++i) {
            int w = ((num[i] >> pos) & 1);
            add[i] = tree[add[i]][w];
        }

        for (int i = 0, s = (int)del.size(); i < s; ++i) {
            int w = ((num[i] >> pos) & 1);
            del[i] = tree[del[i]][w];
        }

        return (query(add, del, num, pos - 1, rk - sum));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        cin >> x[i];

    insert(root[0], 0, 30, 0);

    for (int i = 1; i <= m; ++i) {
        cin >> y[i];
        insert(root[i], root[i - 1], 30, y[i]);
    }

    cin >> p;

    for (int i = 1; i <= p; ++i) {
        cin >> u >> d >> l >> r >> k;
        vector<int> add(d - u + 1, root[r]), del(d - u + 1, root[l - 1]), num(x + u, x + d + 1);
        cout << query(add, del, num, 30, k) << endl;
    }

    return 0;
}