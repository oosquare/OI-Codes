#include <iostream>
using namespace std;

constexpr int maxn = 1e5 + 10;

struct Node {
    int ls, rs, fa, key, dis;
};

int n, m;
Node heap[maxn];

int merge(int x, int y) {
    if (!x || !y)
        return x ^ y;

    if (heap[x].key > heap[y].key || (heap[x].key == heap[y].key && x > y))
        swap(x, y);

    heap[x].rs = merge(heap[x].rs, y);

    if (heap[heap[x].ls].dis < heap[heap[x].rs].dis)
        swap(heap[x].ls, heap[x].rs);

    heap[x].dis = heap[heap[x].rs].dis + 1;
    heap[x].fa = heap[heap[x].ls].fa = heap[heap[x].rs].fa = x;
    return x;
}

int find(int x) {
    return (heap[x].fa == x ? x : heap[x].fa = find(heap[x].fa));
}

int pop(int x) {
    int res = heap[x].key;
    heap[x].key = -1;
    heap[x].fa = heap[heap[x].ls].fa = heap[heap[x].rs].fa = merge(heap[x].ls, heap[x].rs);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cin >> heap[i].key;
        heap[i].fa = i;
    }

    for (int i = 1; i <= m; ++i) {
        int op;
        cin >> op;

        if (op == 1) {
            int x, y;
            cin >> x >> y;

            if (heap[x].key == -1 || heap[y].key == -1 || find(x) == find(y))
                continue;

            merge(find(x), find(y));
        } else {
            int x;
            cin >> x;

            if (heap[x].key == -1) {
                cout << -1 << endl;
                continue;
            }

            x = find(x);
            cout << pop(x) << endl;
        }
    }

    return 0;
}