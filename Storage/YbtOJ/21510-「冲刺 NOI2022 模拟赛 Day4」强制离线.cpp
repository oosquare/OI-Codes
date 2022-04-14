#pragma Clang optimize("Oz")
#include <iostream>
#include <queue>
#include <algorithm>

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();

    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            s = -1;

    for (; '0' <= c && c <= '9'; c = getchar())
        x = x * 10 + c - '0';

    return x * s;
}

template <typename T> void write(T x, char sep = '\n') {
    if (x == 0) {
        putchar('0');
        putchar(sep);
        return;
    }

    static int st[50];
    int top = 0;

    if (x < 0) {
        putchar('-');
        x = -x;
    }

    while (x) {
        st[++top] = x % 10;
        x /= 10;
    }

    while (top)
        putchar(st[top--] + '0');

    putchar(sep);
}

constexpr int MAX_N = 1e5 + 10;

int n, x, y, z;
int a[MAX_N], b[MAX_N], c[MAX_N];
std::pair<int, int> val[MAX_N];
long long pre[MAX_N], suf[MAX_N], sum, ans;

void calcPre() {
    std::priority_queue<int> q;
    long long s = 0;

    for (int i = 1; i <= y; ++i) {
        auto [first, second] = val[i];
        q.push(second - first);
        s += first;
    }

    pre[y] = s;

    for (int i = y + 1; i <= n - x; ++i) {
        auto [first, second] = val[i];
        s += first;

        if (second - first >= q.top()) {
            s += second - first;
        } else {
            s += q.top();
            q.pop();
            q.push(second - first);
        }

        pre[i] = s;
    }
}

void calcSuf() {
    std::priority_queue<int> q;
    long long s = 0;

    for (int i = n; i >= n - x + 1; --i) {
        auto [first, second] = val[i];
        q.push(second);
    }

    for (int i = n - x; i >= y + 1; --i) {
        auto [first, second] = val[i];
        
        if (second >= q.top()) {
            s += second;
        } else {
            s += q.top();
            q.pop();
            q.push(second);
        }

        suf[i] = s;
    }
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("zanl.in", "r", stdin);
    freopen("zanl.out", "w", stdout);
#else
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    x = read(), y = read(), z = read();
    n = x + y + z;

    for (int i = 1; i <= n; ++i)
        a[i] = read(), b[i] = read(), c[i] = read();

    for (int i = 1; i <= n; ++i) {
        sum += a[i];
        val[i] = { b[i] - a[i], c[i] - a[i] };
    }

    std::sort(val + 1, val + 1 + n, std::greater<std::pair<int, int>>());

    calcPre();
    calcSuf();

    for (int i = y; i <= n - x; ++i)
        ans = std::max(ans, sum + pre[i] + suf[i + 1]);

    write(ans);
    return 0;
}
