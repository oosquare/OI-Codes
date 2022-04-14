#include <bits/stdc++.h>
using namespace std;

template <typename T = int>
T read() {
    T x = 0, s = 1;
    char c = getchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * s;
}

struct str {
    char s[210];
    int len;
    
    bool operator<(const str& rhs) const {
        for (int i = 1; i <= min(len, rhs.len); ++i) {
            if (s[i] < rhs.s[i])
                return true;
            else if (s[i] > rhs.s[i])
                return false;
        }
        if (len <= rhs.len)
            return true;
        else
            return false;
    }

    str operator+(const str& rhs) const {
        str res;
        res.len = len + rhs.len;
        for (int i = 1; i <= len; ++i)
            res.s[i] = s[i];
        for (int i = len + 1; i <= len + rhs.len; ++i)
            res.s[i] = rhs.s[i - len];
        return res;
    }
} strings[1001];

int n;

int main() {
    freopen("easy.in", "r", stdin);
    freopen("easy.out", "w", stdout);
    n = read();
    for (int i = 1; i <= n; ++i) {
        scanf("%s", strings[i].s + 1);
        strings[i].len = strlen(strings[i].s + 1);
    }
    sort(strings + 1, strings + 1 + n, [](str a, str b){ return a + b < b + a; });
    for (int i = 1; i <= n; ++i)
        printf("%s", strings[i].s + 1);
    printf("\n");
    return 0;
}
