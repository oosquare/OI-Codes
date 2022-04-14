#include <bits/stdc++.h>
using namespace std;

namespace IO {

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = mygetchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = mygetchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = mygetchar();
    }
    return x * s;
}

template <typename T = int> void writeln(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar('\n');
}

template <typename T = int> void writesp(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar(' ');
}

template <typename T = int> void write(T x, char blank[]) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar('\n');
    for (int i = 0; blank[i] != '\0'; ++i)
        putchar(blank[i]);
}

} // namespace IO

constexpr int maxn = 50000 + 10;
constexpr double alpha = 0.718;
constexpr int oo = 0x3f3f3f3f;

struct node {
    int key, lv, rv;
    int a, b, fa, ls, rs, size, fsize, cnt;
};

node tree[maxn];
int uuid, root, len, tmp[maxn];
int n, id[maxn];
int val[maxn];

inline int &ls(int x) { return tree[x].ls; }

inline int &rs(int x) { return tree[x].rs; }

inline int &fa(int x) { return tree[x].fa; }

void pushup(int x) {
    tree[x].size = tree[ls(x)].size + tree[rs(x)].size + 1;
    tree[x].fsize = tree[ls(x)].fsize + tree[rs(x)].fsize + tree[x].cnt;
}

bool balanced(int x) {
    return alpha * tree[x].size > max(tree[ls(x)].size, tree[rs(x)].size);
}

void enumerate(int x) {
    if (!x)
        return;
    enumerate(ls(x));
    tmp[++len] = x;
    enumerate(rs(x));
}

void make(int &x, int l, int r, int lv, int rv) {
    if (l > r)
        return;
    int mid = (l + r) / 2;
    x = tmp[mid];
    tree[x].lv = lv, tree[x].rv = rv;
    tree[x].key = (lv + rv) / 2;
    make(ls(x), l, mid - 1, tree[x].lv, tree[x].key);
    make(rs(x), mid + 1, r, tree[x].key, tree[x].rv);
    if (ls(x))
        fa(ls(x)) = x;
    if (rs(x))
        fa(rs(x)) = x;
    pushup(x);
}

void rebuild(int &x, int lv, int rv) {
    len = 0;
    enumerate(x);
    for (int i = 1; i <= len; ++i) {
        int y = tmp[i];
        tree[y].size = 1, tree[y].fsize = tree[y].cnt;
        ls(y) = rs(y) = fa(y) = 0;
    }
    make(x, 1, len, lv, rv);
}

void check() {

}

int insert(int a, int b, int t) {
    int x = root, y = 0, dir, cnt = 0;
    while (x) {
        y = x;
        ++tree[y].fsize;
        if (tree[a].key == tree[tree[x].a].key && tree[b].key == tree[tree[x].b].key) {
            ++tree[x].cnt;
            id[t] = x;
            return cnt + tree[x].cnt + tree[ls(x)].fsize;
        }
        if (tree[tree[x].a].key < tree[a].key || (tree[tree[x].a].key == tree[a].key && tree[tree[x].b].key < tree[b].key)) {
            cnt += tree[ls(x)].fsize + tree[x].cnt;
            dir = 1;
            x = rs(x);
        } else {
            dir = 0;
            x = ls(x);
        }
    }
    id[t] = x = ++uuid;
    fa(x) = y;
    tree[x].a = a, tree[x].b = b;
    tree[x].size = tree[x].fsize = tree[x].cnt = 1;
    if (y) {
        if (dir == 0) {
            tree[x].lv = tree[y].lv;
            tree[x].rv = tree[y].key;
            tree[x].key = (tree[x].lv + tree[x].rv) / 2;
            ls(y) = x;
        } else {
            tree[x].lv = tree[y].key;
            tree[x].rv = tree[y].rv;
            tree[x].key = (tree[x].lv + tree[x].rv) / 2;
            rs(y) = x;
        }
    }
    int w = 0;
    while (fa(x)) {
        x = fa(x);
        ++tree[x].size;
        if (!balanced(x))
            w = x;
    }
    if (w) {
        int f = fa(w);
        if (f) {
            if (tree[w].key < tree[f].key) {
                rebuild(w, tree[f].lv, tree[f].key);
                fa(w) = f;
                ls(f) = w;
            } else {
                rebuild(w, tree[f].key, tree[f].rv);
                fa(w) = f;
                rs(f) = w;
            }
        } else {
            if (tree[w].key < tree[f].key)
                rebuild(w, 0, oo / 2);
            else
                rebuild(w, oo / 2, oo);
            root = w;
        }
    }
    return cnt + 1;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("comparison.in", "r", stdin);
    freopen("comparison.out", "w", stdout);
#endif
    n = IO::read();
    root = 1;
    uuid = 2;
    rs(1) = 2;
    fa(2) = 1;
    tree[2].size = tree[2].fsize = tree[2].cnt = 1;
    tree[1].size = tree[1].fsize = 2;
    tree[1].cnt = 1;
    tree[1].lv = 0;
    tree[1].rv = oo;
    tree[1].a = tree[1].b = 1;
    tree[1].key = oo / 2;
    tree[2].lv = oo / 2;
    tree[2].rv = oo;
    tree[2].key = (tree[2].lv + tree[2].rv) / 2;
    tree[2].a = tree[2].b = 2;
    id[0] = 1;
    id[n + 1] = 2;
    
    for (int i = 1; i <= n; ++i) {
        int a = IO::read(), b = IO::read();
        cout << insert(id[a], id[b], i) << endl;
            // printf("(%d)\n", val[i]);
        
        // if (i == 6 || i == 5) {
        //     cout << "--\n";
        //     for (int i = 1; i <= n; ++i) {
        //         cout << i << "  " << val[i] << " ";
        //         print(val[i]);
        //     } 
        //     cout << "--\n";       
        // }
    }
    // for (int i = 1; i <= n; ++i) {
    //     cout << i << "  " << val[i] << endl;
    // }
    return 0;
}
