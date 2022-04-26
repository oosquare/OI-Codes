#include <cctype>
#include <iostream>
#include <numeric>

constexpr int MAX_N = 100000 + 10;

int t, n;
int type[MAX_N], len[MAX_N];

int getchar_alpha() {
    int c = std::cin.get();

    for (; !std::isalpha(c); c = std::cin.get())
        ;

    return c;
}

void solve() {
    int tot_b = 0, tot_w = 0;

    std::cin >> n;

    for (int i = 1; i <= n; ++i) {
        std::cin >> len[i];
        type[i] = getchar_alpha();

        if (type[i] == 'B')
            tot_b += len[i];
        else
            tot_w += len[i];
    }

    if (!tot_b || !tot_w) {
        std::cout << tot_b + tot_w << std::endl;
        return;
    }

    int d = std::gcd(tot_b, tot_w);
    tot_b /= d;
    tot_w /= d;
    int ans = 0;
    int now_b = 0, now_w = 0;

    for (int i = 1; i <= n; ++i) {
        if (type[i] == 'B') {
            now_b += len[i];

            if (!now_b || !now_w || now_w % tot_w != 0)
                continue;

            if (!((1ll * (now_b - len[i]) * tot_w < 1ll * now_w * tot_b) &&
                  (1ll * now_b * tot_w >= 1ll * now_w * tot_b)))
                continue;

            ++ans;
            now_b -= now_w / tot_w * tot_b;
            now_w = 0;
        } else {
            now_w += len[i];

            if (!now_b || !now_w || now_b % tot_b != 0)
                continue;

            if (!((1ll * now_b * tot_w > 1ll * (now_w - len[i]) * tot_b) &&
                  (1ll * now_b * tot_w <= 1ll * now_w * tot_b)))
                continue;

            ++ans;
            now_w -= now_b / tot_b * tot_w;
            now_b = 0;
        }
    }

    std::cout << ans << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> t;

    while (t--)
        solve();

    return 0;
}