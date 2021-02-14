 b#include <bits/stdc++.h>
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

constexpr int maxn = 500000;

struct node {
    int t, x, y, cnt, ans, type;
};

node arr[maxn], tmp[maxn];
int bitt[maxn * 10], w, k, nextid;
vector<int> gett;

int lowbit(int x) {
    return x & (-x);
}

void add(int p, int v) {
    for (; p <= k; p += lowbit(p))
        bitt[p] += v;
}

int query(int p) {
    int res = 0;
    for (; p; p -= lowbit(p))
        res += bitt[p];
    return res;
}

void init(int p) {
    for (; p <= k; p += lowbit(p))
        if (bitt[p] == 0)
            return;
        else
            bitt[p] = 0;
}

void CDQdivide(int l, int r) {
    if (l >= r)
        return;
    int mid = (l + r) / 2, idx1 = l, idx2 = mid + 1, len = l - 1;
    CDQdivide(l, mid);
    CDQdivide(mid + 1, r);
    while (idx1 <= mid && idx2 <= r) {
        if (arr[idx1].x <= arr[idx2].x) {
            tmp[++len] = arr[idx1++];
            if (tmp[len].type == 1)
                add(tmp[len].y, tmp[len].cnt);
        } else {
            tmp[++len] = arr[idx2++];
            if (tmp[len].type == 2)
                tmp[len].ans += query(tmp[len].y);
        }
    }
    while (idx1 <= mid) {
        tmp[++len] = arr[idx1++];
        if (tmp[len].type == 1)
            add(tmp[len].y, tmp[len].cnt);
    }
    while (idx2 <= r) {
        tmp[++len] = arr[idx2++];
        if (tmp[len].type == 2)
            tmp[len].ans += query(tmp[len].y);
    }
    for (int i = l; i <= r; ++i) {
        arr[i] = tmp[i];
        init(arr[i].y);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    using namespace IO;
    read(), w = read() + 1;
    while (true) {
        int op = read();
        if (op == 1) {
            int x = read() + 1, y = read() + 1, a = read();
            ++nextid, arr[nextid] = {nextid, x, y, a, 0, 1};
            k = max(k, y);
        } else if (op == 2) {
            int x1 = read() + 1, y1 = read() + 1, x2 = read() + 1, y2 = read() + 1;
            gett.push_back(nextid + 1);
            ++nextid, arr[nextid] = {nextid, x2, y2, 0, 0, 2};
            ++nextid, arr[nextid] = {nextid, x1 - 1, y2, 0, 0, 2};
            ++nextid, arr[nextid] = {nextid, x2, y1 - 1, 0, 0, 2};
            ++nextid, arr[nextid] = {nextid, x1 - 1, y1 - 1, 0, 0, 2};
            k = max(k, y2);
        } else {
            break;
        }
    }
    ++k;
    CDQdivide(1, nextid);
    sort(arr + 1, arr + 1 + nextid, [](const node &a, const node &b) { return a.t < b.t; });
    for (int i : gett)
        writeln(arr[i].ans - arr[i + 1].ans - arr[i + 2].ans + arr[i + 3].ans);
    return 0;
}