#include <iostream>
using namespace std;

constexpr int maxn = 1e5 + 10;

struct Node {
    int ls, rs, fa, key, dis;
};

int n, m;
Node heap[maxn * 3];
int uuid, now[maxn], rev[maxn * 3];

void pushup(int x) {
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
    heap[heap[x].rs].fa = heap[heap[x].ls].fa = heap[x].fa = x;
    pushup(x);
    return x;
}

int find(int x) {
    return (heap[x].fa == x ? x : heap[x].fa = find(heap[x].fa));
}


int pop(int x) {
    int rt = merge(heap[x].ls, heap[x].rs);
    heap[x].fa = heap[heap[x].ls].fa = heap[heap[x].rs].fa = rt;
    return rt;
}

int create(int key) {
    ++uuid;
    heap[uuid].ls = heap[uuid].rs = 0;
    heap[uuid].fa = uuid;
    heap[uuid].key = key;
    heap[uuid].dis = 1;
    return uuid;
}

void solve() {
    uuid = 0;

    for (int i = 1; i <= n; ++i) {
        int s;
        cin >> s;
        now[i] = create(s);
        rev[now[i]] = i;
    }

    cin >> m;

    for (int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;

        if (find(now[x]) == find(now[y])) {
            cout << -1 << endl;
        } else {
            x = rev[find(now[x])];
            y = rev[find(now[y])];
            int vx = heap[now[x]].key, vy = heap[now[y]].key;
            int rx = pop(now[x]), ry = pop(now[y]);
            now[x] = create(vx / 2);
            rev[now[x]] = x;
            now[y] = create(vy / 2);
            rev[now[y]] = y;
            merge(merge(now[x], rx), merge(now[y], ry));
            cout << heap[find(now[x])].key << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);

    while (cin >> n)
        solve();

    return 0;
}