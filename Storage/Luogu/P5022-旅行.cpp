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

} // namespace IO

constexpr int maxn = 5000 + 10;

int n, m;
vector<int> tree[maxn];
vector<int> circle, ans;
bool inCircle[maxn], vis[maxn], turned;

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

bool find(int x, int fa) {
    vis[x] = true;
    
    for (int y : tree[x]) {
        if (y == fa)
            continue;
        if (vis[y] == true) {
            circle.push_back(y);
            circle.push_back(x);
            inCircle[x] = inCircle[y] = true;
            return true;
        }
        if (find(y, x)) {
            if (x != circle[0]) {
                circle.push_back(x);
                inCircle[x] = true;
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

void walkTree(int x, int fa);

void walkCircle(int x, int fa, int other) {
    if (vis[x] == false)
        ans.push_back(x);
    vis[x] = true;
    for (auto it = tree[x].begin(); it != tree[x].end(); ++it) {
        int y = *it;
        if (y == fa || vis[y] == true)
            continue;
        if (inCircle[y] == false) {
            walkTree(y, x);
        } else {
            bool last = next(it) == tree[x].end() || *next(it) == fa;
            if (inCircle[fa] == true) {
                if (last && turned == false && other < y) {
                    turned = true;
                    return;
                } else {
                    walkCircle(y, x, last ? other : *next(it));
                }
            } else {
                walkCircle(y, x, last ? n + 1 : *next(it));
            }
        }
    }
}

void walkTree(int x, int fa) {
    vis[x] = true;
    ans.push_back(x);
    for (int y : tree[x]) {
        if (y == fa || vis[y] == true)
            continue;
        // remove(x, exchange(last, y));
        if (inCircle[y] == true) {
            walkCircle(y, x, 0);
        } else {
            walkTree(y, x);
        }
    }
    // remove(x, last);
}

int main() {
    using namespace IO;
    n = read(), m = read();
    for (int i = 1; i <= m; ++i) {
        int x = read(), y = read();
        link(x, y);
    }
    for (int i = 1; i <= n; ++i)
        sort(tree[i].begin(), tree[i].end());
    if (m == n - 1) {
        walkTree(1, 0);
    } else {
        find(1, 0);
        memset(vis, 0, sizeof(vis));
        if (inCircle[1] == true) {
            walkCircle(1, 0, 0);
        } else {
            walkTree(1, 0);
        }
    }
    for (int v : ans)
        writesp(v);
    return 0;
}