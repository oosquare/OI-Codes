#include <iostream>

template <typename T = int> T read() {
    T x = 0, s = 1;
    int c = std::getchar();

    for (; c < '0' || c > '9'; c = std::getchar())
        ;

    for (; '0' <= c && c <= '9'; c = std::getchar())
        x = x * 10 + c - '0';

    return x * s;
}

constexpr int MAX_N = 100000 + 10;

int n;
int val[MAX_N], cnt[MAX_N];
int ans, sta;
int f[MAX_N];

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("Ava.in", "r", stdin);
    std::freopen("Ava.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    n = read();

    for (int i = 1; i < n; ++i) {
        int x = read(), y = read(), w = read();
        val[x] ^= w;
        val[y] ^= w;
    }

    for (int i = 0; i < n; ++i)
        ++cnt[val[i]];

    for (int i = 1; i < 16; ++i) {
        ans += cnt[i] / 2;
        
        if (cnt[i] % 2)
            sta |= (1 << i);
    }

    for (int i = 0; i < sta; ++i)
        f[i] = 0x3f3f3f3f;

    sta |= 1;

    for (int s = sta; s >= 0; --s) {
        for (int i = 1; i < 16; ++i) {
            if (!((s >> i) & 1))
                continue;
            
            for (int j = 1; j < 16; ++j) {
                if (!((s >> j) & 1) || i == j)
                    continue;

                int ns = (s ^ (1 << i) ^ (1 << j)), delta = 1;

                if ((ns >> (i ^ j)) & 1)
                    ++delta;

                ns ^= (1 << (i ^ j));
                f[ns] = std::min(f[ns], f[s] + delta);
            }
        }
    }

    std::cout << ans + f[1] << std::endl;
    return 0;
}
