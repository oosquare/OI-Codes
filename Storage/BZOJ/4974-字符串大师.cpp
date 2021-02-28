#include <bits/stdc++.h>
using namespace std;

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

int read() {
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

const int maxn = 100000 + 10;
int fail[maxn], pre[maxn], vis[26], n;
char ans[maxn];

void preprocess() {
    fail[0] = -1;
    for (int i = 1; i <= n; ++i)
        fail[i] = i - pre[i];
}

void solve() {
    for (int i = 1; i <= n; ++i) {
        if (fail[i]) {
            ans[i] = ans[fail[i]];
        } else {
            int j;
            for (j = fail[i - 1]; j != -1; j = fail[j])
                vis[ans[j + 1] - 'a'] = i;
            for (j = 0; j < 26; ++j)
                if (vis[j] != i)
                    break;
            ans[i] = j + 'a';
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read();
    for (int i = 1; i <= n; ++i)
        pre[i] = read();
    preprocess();
    solve();
    for (int i = 1; i <= n; ++i)
        putchar(ans[i]);
    putchar('\n');
    return 0;
}