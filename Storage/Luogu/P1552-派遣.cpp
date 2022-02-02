#include <iostream>
#include <vector>
using namespace std;

constexpr int maxn = 1e5 + 10;

struct Node {
    int ls, rs, key, dis;
};

int n, m, c[maxn], l[maxn];
vector<int> tree[maxn];
Node heap[maxn];
int root[maxn];
long long sum[maxn], cnt[maxn], ans;

inline void link(int x, int y) {
    tree[x].push_back(y);
}

inline void pushup(int x) {
    if (heap[heap[x].ls].dis < heap[heap[x].rs].dis)
        swap(heap[x].ls, heap[x].rs);

    heap[x].dis = heap[heap[x].rs].dis + 1;
}

int merge(int x, int y) {
    if (!x || !y)
        return x ^ y;

    if (heap[x].key < heap[y].key)
        swap(x, y);

    heap[x].rs = merge(heap[x].rs, y);
    pushup(x);
    return x;
}

inline int top(int x) {
    return heap[root[x]].key;
}

inline void pop(int x) {
    root[x] = merge(heap[root[x]].ls, heap[root[x]].rs);
}

void solve(int x) {
    root[x] = x;
    heap[x].dis = 1;
    heap[x].key = c[x];
    sum[x] = c[x];
    cnt[x] = 1;

    for (int y : tree[x]) {
        solve(y);
        root[x] = merge(root[x], root[y]);
        sum[x] += sum[y];
        cnt[x] += cnt[y];
    }

    while (sum[x] > m) {
        sum[x] -= top(x);
        --cnt[x];
        pop(x);
    }

    ans = max(ans, l[x] * cnt[x]);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        int b;
        cin >> b >> c[i] >> l[i];

        if (b)
            link(b, i);
    }

    solve(1);
    cout << ans << endl;
    return 0;
}