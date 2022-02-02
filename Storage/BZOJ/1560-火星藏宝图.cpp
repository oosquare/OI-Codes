#include <cstdio>
#include <vector>
#include <algorithm>

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();

    for (; c < '0' || '9' < c; c = getchar())
        if (c == '-')
            s = -1;

    for (; '0' <= c && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + c - '0';

    return x * s;
}

using namespace std;

constexpr int maxn = 200000 + 10;
constexpr int maxm = 1000 + 10;
constexpr int oo = 0x3f3f3f3f;

struct Island {
    int x, y, v;

    bool operator<(const Island &rhs) const {
        return (x != rhs.x ? x < rhs.x : y < rhs.y);
    }
};

int n, m;
Island island[maxn];
int col[maxm][maxm], len[maxm];
int q[maxn];
int f[maxn];

inline int power(int x) {
    return x * x;
}

inline int getY(int i, int row) {
    return f[i] - power(island[i].x) - power(island[i].y) + 2 * row * island[i].x;
}

inline double slope(int i, int j, int row) {
    if (island[i].y == island[j].y)
        return ((getY(i, row) < getY(j, row)) ? oo : -oo);

    return 1.0 * (getY(j, row) - getY(i, row)) / (island[j].y - island[i].y);
}

void update(int l, int r) {
    int row = island[l].x;
    int fr = 1, bk = 0;

    for (int i = l, j = 1; i <= r; ++i) {
        while (j <= m && j <= island[i].y) {
            if (len[j]) {
                int k = col[j][len[j]];

                while (fr < bk && slope(q[bk - 1], q[bk], row) <= slope(q[bk], k, row))
                    --bk;

                q[++bk] = k;
            }

            ++j;
        }

        while (fr < bk && -2 * island[i].y <= slope(q[fr], q[fr + 1], row))
            ++fr;

        if (fr <= bk) {
            int j = q[fr];
            f[i] = f[j] - power(island[i].x - island[j].x) - power(island[i].y - island[j].y) + island[i].v;
        }

        while (fr < bk && slope(q[bk - 1], q[bk], row) <= slope(q[bk], i, row))
            --bk;

        q[++bk] = i;
        col[island[i].y][++len[island[i].y]] = i;
    }
}

int main() {
    n = read(), m = read();

    for (int i = 1; i <= n; ++i) {
        island[i].x = read(), island[i].y = read(), island[i].v = read();
        f[i] = -oo;
    }

    sort(island + 1, island + 1 + n);
    f[1] = island[1].v;

    for (int l = 1, r = 1; l <= n; l = r + 1, r = l) {
        while (r < n && island[r + 1].x == island[l].x)
            ++r;

        update(l, r);
    }

    printf("%d\n", f[n]);
    return 0;
}