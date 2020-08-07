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

constexpr int maxn = 500000 + 10;

typedef long long ll;

ll n, d, k, x[maxn], s[maxn], f[maxn], q[maxn * 4], front, back, now, l, r, ans = -1;

bool check(int g) {
    memset(f, 0, sizeof(f));
    back = now = 0;
    front = 1;
    for (int i = 1; i <= n; ++i) {
        ll l = max(d - g, 1LL), r = d + g;
        while (x[now] + l <= x[i]) {
            while (front <= back && f[q[back]] < f[now])
                --back;
            q[++back] = now++;
        }
        while (front <= back && x[q[front]] + r < x[i])
            ++front;
        if (front <= back)
            f[i] = f[q[front]] + s[i];
        else
            f[i] = -0x3f3f3f3f3f3f3f3f;
        if (f[i] >= k)
            return true;
    }
    return false;
}

int main() {
//#ifndef ONLINE_JUDGE
//    freopen("Environment/project.in", "r", stdin);
//    freopen("Environment/project.out", "w", stdout);
//#endif
    using namespace IO;
    n = read<ll>();
    d = read<ll>();
    k = read<ll>();
    for (int i = 1; i <= n; ++i) {
        x[i] = read<ll>();
        s[i] = read<ll>();
    }
    l = 0;
    r = x[n];
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    writeln(ans);
    return 0;
}
