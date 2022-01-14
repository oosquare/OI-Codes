#include <iostream>
#include <queue>
#include <tuple>
using namespace std;

constexpr int maxn = 5e5 + 10;

struct Node {
    int next[2];
    int cnt;

    int &operator[](int x) {
        return next[x];
    }
};

int n, k;
long long a[maxn], sum[maxn];
long long ans;
Node tree[maxn * 100];
int uuid, root[maxn];
priority_queue<tuple<long long, int, int>> q;

inline void pushup(int x) {
    tree[x].cnt = tree[tree[x][0]].cnt + tree[tree[x][1]].cnt;
}

void insert(int &x, int y, int pos, long long num) {
    x = ++uuid;
    tree[x] = tree[y];
    ++tree[x].cnt;

    if (pos == -1)
        return;

    int w = ((num >> pos) & 1);
    insert(tree[x][w], tree[y][w], pos - 1, num);
}

long long query(int x, int pos, int num, int rk) {
    if (pos == -1)
        return 0;

    int w = ((num >> pos) & 1);

    if (tree[x][w ^ 1] && rk <= tree[tree[x][w ^ 1]].cnt)
        return (query(tree[x][w ^ 1], pos - 1, num, rk) | (1ll << pos));
    else
        return query(tree[x][w], pos - 1, num, rk - tree[tree[x][w ^ 1]].cnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    insert(root[0], 0, 31, 0);

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        sum[i] = (sum[i - 1] ^ a[i]);
        insert(root[i], root[i - 1], 31, sum[i]);
    }

    for (int i = 1; i <= n; ++i)
        q.push({query(root[i - 1], 31, sum[i], 1), i, 1});

    for (int i = 1; i <= k; ++i) {
        auto [s, p, t] = q.top();
        q.pop();
        ans += s;

        if (tree[root[p]].cnt >= t + 1)
            q.push({query(root[p - 1], 31, sum[p], t + 1), p, t + 1});
    }

    cout << ans << endl;
    return 0;
}
