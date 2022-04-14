#include <cstdio>
#include <algorithm>

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = (char) std::getchar();

    for (; c < '0' || c > '9'; c = (char) std::getchar())
        if (c == '-')
            s = -1;

    for (; '0' <= c && c <= '9'; c = (char) std::getchar())
        x = x * 10 + c - '0';

    return x * s;
}

constexpr int MAX_N = 500000 + 10;

int n, q;
int a[MAX_N];
int mx[MAX_N], mi[MAX_N];

bool isSteady(int l, int r) {
    return mx[r] <= l;
}

bool check(int k, int l, int r) {
    l = l + k;
    r = r - k;

    if (isSteady(l, r))
        return true;
     
    if (isSteady(l, r - 1) || isSteady(l + 1, r))
        return true;

    if (isSteady(l, r - 2) || isSteady(l + 2, r))
        return true;

    return false;
}

int find(int l, int r) {
    int kl = 0, kr = std::max((r - l) / 2, 0);
    int pos = -1;
    
    while (kl <= kr) {
        int mid = (kl + kr) / 2;

        if (check(mid, l, r)) {
            pos = mid;
            kr = mid - 1;
        } else {
            kl = mid + 1;
        }
    }

    return pos;
}

char solve(int l, int r) {
    int k = find(l, r);
    l += k;
    r -= k;

    if (isSteady(l, r)) {
        return 'S';
    } else if (isSteady(l + 1, r) || isSteady(l, r - 1)) {
        return 'F';
    } else if (mi[l] == r - 2) {
        if (mx[r] > mx[r - 1])
            return (l % 2 == mx[r - 1] % 2 ? 'F' : 'S');
        else
            return (l % 2 != mx[r] % 2 ? 'F' : 'S');
    } else {
        if (mi[l] < mi[l + 1])
            return (r % 2 == mi[l + 1] % 2 ? 'F' : 'S');
        else
            return (r % 2 != mi[l] % 2 ? 'F' : 'S');
    }
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("inverse.in", "r", stdin);
    freopen("inverse.out", "w", stdout);
#else
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read(), q = read();
    
    for (int i = 1; i <= n; ++i)
        a[i] = read();

    for (int i = 1, it = 1; i <= n; ++i) {
        if (a[i] > a[i - 1])
            it = i;

        mx[i] = it;
    }

    for (int i = 1, it = 1; i <= n; ++i) {
        if (a[i] < a[i - 1])
            it = i;

        mx[i] = std::min(mx[i], it);
    }

    for (int i = n, it = n; i >= 1; --i) {
        if (a[i] > a[i + 1])
            it = i;
            
        mi[i] = it;
    }

    for (int i = n, it = n; i >= 1; --i) {
        if (a[i] < a[i + 1])
            it = i;

        mi[i] = std::max(mi[i], it);
    }

    for (int i = 1; i <= q; ++i) {
        int l = read(), r = read();
        std::putchar(solve(l, r));
    }

    return 0;
}
