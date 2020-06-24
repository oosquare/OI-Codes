#include <bits/stdc++.h>
using namespace std;

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T = int>
T read() {
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

template <typename T = int>
void writeln(T x) {
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

template <typename T = int>
void writesp(T x) {
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

template <typename T = int>
void write(T x, char blank[]) {
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

constexpr int maxn = 1e5 + 10;
constexpr int maxa = 1e6;

int n, maxv, a[maxn], sum[maxa + 1], cnt[maxa + 1], vis[maxa + 1];

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    n = read();
    for (int i = 1; i <= n; ++i) {
        a[i] = read();
        ++cnt[a[i]];
        maxv = max(maxv, a[i]);
    }
    for (int i = 1; i <= n; ++i) {
        if (vis[a[i]])
            continue;
        vis[a[i]] = true;
        for (int j = a[i]; j <= maxv; j += a[i]) {
            sum[j] += cnt[a[i]];
        }
    }
    for (int i = 1; i <= n; ++i) {
        writeln(sum[a[i]] - 1);
    }
    return 0;
}