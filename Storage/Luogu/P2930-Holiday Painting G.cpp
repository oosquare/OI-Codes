#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

constexpr int maxr = 50000 + 10;
constexpr int maxc = 15 + 10;

class SegmentTree {
public:
    void build(int n, int a[]) {
        size = n;
        s = a;
        build(1, 1, size);
    }

    void assign(int l, int r, int v) {
        assign(1, l, r, v);
    }

    int query(int l, int r) {
        return query(1, l, r);
    }
private:
    struct Node {
        int left, right;
        int sum, assign;

        int length() const {
            return right - left + 1;
        }
    };

    Node tree[maxr * 4];
    int *s, size;

    void pushup(int x) {
        tree[x].sum = tree[x * 2].sum + tree[x * 2 + 1].sum;
    }

    void update(int x, int v) {
        tree[x].assign = v;

        if (v == 1)
            tree[x].sum = s[tree[x].right] - s[tree[x].left - 1];
        else
            tree[x].sum = tree[x].length() - (s[tree[x].right] - s[tree[x].left - 1]);
    }

    void pushdown(int x) {
        if (tree[x].assign == -1)
            return;

        update(x * 2, tree[x].assign);
        update(x * 2 + 1, tree[x].assign);
        tree[x].assign = -1;
    }

    void build(int x, int l, int r) {
        tree[x].left = l;
        tree[x].right = r;
        tree[x].assign = -1;

        if (l == r) {
            tree[x].sum = (s[l] - s[l - 1] == 0);
            return;
        }

        int mid = (l + r) / 2;
        build(x * 2, l, mid);
        build(x * 2 + 1, mid + 1, r);
        pushup(x);
    }

    void assign(int x, int l, int r, int v) {
        if (l <= tree[x].left && tree[x].right <= r) {
            update(x, v);
            return;
        }

        int mid = (tree[x].left + tree[x].right) / 2;
        pushdown(x);

        if (l <= mid)
            assign(x * 2, l, r, v);

        if (mid < r)
            assign(x * 2 + 1, l, r, v);

        pushup(x);
    }

    int query(int x, int l, int r) {
        if (l <= tree[x].left && tree[x].right <= r)
            return tree[x].sum;

        int mid = (tree[x].left + tree[x].right) / 2, res = 0;
        pushdown(x);

        if (l <= mid)
            res += query(x * 2, l, r);

        if (mid < r)
            res += query(x * 2 + 1, l, r);

        return res;
    }
};

int r, c, q;
char a[maxr][maxc];
int sum[maxc][maxr];
SegmentTree tree[maxc];

int main() {
    ios::sync_with_stdio(false);
    cin >> r >> c >> q;

    for (int i = 1; i <= r; ++i)
        cin >> (a[i] + 1);

    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j)
            sum[j][i] = a[i][j] - '0';


    for (int i = 1; i <= c; ++i)
        for (int j = 1; j <= r; ++j)
            sum[i][j] += sum[i][j - 1];

    for (int i = 1; i <= c; ++i)
        tree[i].build(r, sum[i]);

    for (int i = 1; i <= q; ++i) {
        int r1, r2, c1, c2, x, ans = 0;
        cin >> r1 >> r2 >> c1 >> c2 >> x;

        for (int j = c1; j <= c2; ++j) 
            tree[j].assign(r1, r2, x);

        for (int j = 1; j <= c; ++j)
            ans += tree[j].query(1, r);

        cout << ans << endl;
    }
    
    return 0;
}