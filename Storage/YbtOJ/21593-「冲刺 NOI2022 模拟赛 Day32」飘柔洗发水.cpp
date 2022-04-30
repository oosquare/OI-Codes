#include <iostream>

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

constexpr int MAX_N = 2000000 + 10;

int n, d;
long long p, w[MAX_N], sum[MAX_N];
int q[MAX_N], fr, bk;
long long s;
int ans;

long long query(int l, int r) {
    long long res = sum[std::min(r, l + d - 1)] - sum[l - 1];

    if (fr <= bk)
        res = std::max(res, sum[q[fr]] - sum[q[fr] - d]);

    return res;
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("a.in", "r", stdin);
    std::freopen("a.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    n = read();
    p = read<long long>();
    d = read();

    for (int i = 1; i <= n; ++i) {
        w[i] = read();
        sum[i] = sum[i - 1] + w[i];
    }

    fr = 1;
    bk = 0;
    s = w[1];

    for (int l = 1, r = 1; r <= n;) {
        while (true) {
            while (fr <= bk && q[fr] - d + 1 < l)
                ++fr;

            if (s - query(l, r) <= p)
                break;

            s -= w[l];
            ++l;
        }

        ans = std::max(ans, r - l + 1);
        ++r;
        s += w[r];

        if (r - l + 1 >= d) {
            while (fr <= bk && sum[q[bk]] - sum[q[bk] - d] <= sum[r] - sum[r - d])
                --bk;

            q[++bk] = r;
        }
    }

    std::cout << ans << std::endl;
    return 0;
}
