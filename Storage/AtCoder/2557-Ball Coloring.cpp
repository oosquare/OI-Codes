#include <iostream>
#include <algorithm>

constexpr int MAX_N = 200000 + 10;
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;

int n;
int a[MAX_N], b[MAX_N];
long long ans = INF;
std::pair<int, int> ranges[MAX_N], tmp[MAX_N];

inline bool between(int l, int r, int x) { return l <= x && x <= r; }

void updateUpAndDown(int &up, int &down, int maxValPos, int minValPos) {
    int tot = 0, tot2 = 0;

    for (int i = 1; i <= n; ++i) {
        if (i == maxValPos || i == minValPos)
            continue;

        if (b[i] < down && up < a[i])
            ranges[++tot] = { b[i], a[i] };
    }

    if (!tot)
        return;

    std::sort(ranges + 1, ranges + 1 + tot);

    for (int i = 1; i <= tot; ++i) {
        if (ranges[i].first == ranges[i + 1].first)
            continue;

        tmp[++tot2] = ranges[i];
    }

    tot = tot2;

    for (int i = 1; i <= tot; ++i)
        ranges[i] = tmp[i];

    if (up - ranges[1].first < ranges[tot].second - down)
        down = ranges[1].first;
    else
        up = ranges[tot].second;

    for (int i = 1; i < tot; ++i) {
        if (ranges[i].second - ranges[i + 1].first < up - down) {
            up = ranges[i].second;
            down = ranges[i + 1].first;
        }
    }
}

long long calcMaxMinTypeSame() {
    int maxValPos = 0, minValPos = 0;
    int down, up;

    for (int i = 1; i <= n; ++i) {
        if (!maxValPos || a[maxValPos] < a[i]) {
            maxValPos = i;
            up = b[i];
        }

        if (!minValPos || b[minValPos] > b[i]) {
            minValPos = i;
            down = a[i];
        }
    }

    if (maxValPos == minValPos)
        return INF;

    if (down > up)
        std::swap(down, up);

    for (int i = 1; i <= n; ++i) {
        if (i == maxValPos || i == minValPos)
            continue;

        if (between(down, up, a[i]) || between(down, up, b[i]))
            continue;

        if (a[i] < down)
            down = a[i];
        else if (up < b[i])
            up = b[i];
    }

    updateUpAndDown(up, down, maxValPos, minValPos);

    return 1ll * (a[maxValPos] - b[minValPos]) * (up - down);
}

long long calcMaxMinTypeNotSame() {
    int maxValPos = 0, minValPos = 0;
    int down, up;

    for (int i = 1; i <= n; ++i) {
        if (!maxValPos || a[maxValPos] < a[i]) {
            maxValPos = i;
            down = b[i];
        }

        if (!minValPos || b[minValPos] > b[i]) {
            minValPos = i;
            up = a[i];
        }
    }
    
    for (int i = 1; i <= n; ++i) {
        if (i == maxValPos || i == minValPos)
            continue;

        up = std::min(up, a[i]);
        down = std::max(down, b[i]);
    }

    return 1ll * (a[maxValPos] - up) * (down - b[minValPos]);
}

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> n;

    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i] >> b[i];

        if (a[i] < b[i])
            std::swap(a[i], b[i]);
    }

    ans = calcMaxMinTypeSame();
    ans = std::min(ans, calcMaxMinTypeNotSame());
    std::cout << ans << std::endl;
    return 0;
}
