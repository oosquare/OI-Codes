#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int maxs = 2e5 + 10;
constexpr int oo = 0x3f3f3f3f;

struct Node {
    bool isleaf, iscover;
    int assign;
};

Node tree[maxs * 4];
int s, q;

/*
a = 0 : æ 
a = 1 : æ²¡æé¾
a = 2 : æé¾
*/
void update(int x, int a) {
    tree[x].assign = a;
    if (a == 2)
        tree[x].iscover = true;
    else
        tree[x].iscover = false;
}

void pushdown(int x) {
    if (tree[x].assign == 0)
        return;
    int a = tree[x].assign;
    update(x * 2, a);
    update(x * 2 + 1, a);
    tree[x].assign = 0;
}

void pushup(int x) {
    tree[x].iscover = (tree[x * 2].iscover || tree[x * 2 + 1].iscover);
}

void modify(int x, int l, int r, int ml, int mr, int a) {
    if (ml <= l && r <= mr) {
        update(x, a);
        return;
    }
    int mid = (l + r) / 2;
    pushdown(x);
    if (ml <= mid)
        modify(x * 2, l, mid, ml, mr, a);
    if (mid < mr)
        modify(x * 2 + 1, mid + 1, r, ml, mr, a);
    pushup(x);
} 

bool query(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return tree[x].iscover;
    int mid = (l + r) / 2;
    bool res = 0;   
    pushdown(x);
    if (ql <= mid)
        res |= query(x * 2, l, mid, ql, qr);
    if (mid < qr)
        res |= query(x * 2 + 1, mid + 1, r, ql, qr);
    return res;
}

ll queryLeft(int x) {
    int l = 1, r = x - 1, ans = 0;
    if (x - 1 == 0)
        return oo;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (!query(1, 1, s, mid, x - 1)) {
            r = mid - 1;
            ans = x - mid;
        } else {
            l = mid + 1;
        }
    }
    if (ans == x - 1)
        return oo;
    else
        return ans;
}

ll queryRight(int x) {
    if (x + 1 == s + 1)
        return oo;
    int l = x + 1, r = s, ans = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (!query(1, 1, s, x + 1, mid)) {
            l = mid + 1;
            ans = mid - x;
        } else {
            r = mid - 1;
        }
    }
    if (ans == s - x)
        return oo;
    else
        return ans;
}

void build(int x, int l, int r) {
    if (l == r) {
        tree[x].iscover = false;
        tree[x].isleaf = true;
        return;
    }
    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
    pushup(x);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("explore.in", "r", stdin);
    freopen("explore.out", "w", stdout);
#endif
    cin >> s >> q;
    build(1, 1, s);
    for (int i = 1; i <= q; ++i) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            cin >> l >> r;
            modify(1, 1, s, l, r, 2);
        } else if (op == 2) {
            int l, r;
            cin >> l >> r;
            modify(1, 1, s, l, r, 1);
        } else {
            int x;
            cin >> x;
            if (query(1, 1, s, x, x) == true) {
                cout << 0 << endl;
                continue;
            }
            long long res = queryLeft(x) + queryRight(x) + 1;
            if (res >= oo)
                cout << "INF" << endl;
            else
                cout << res << endl;
        }
    }
    return 0;
}
