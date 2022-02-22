#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

constexpr int MAX_N = 2e5 + 10;
constexpr int MAX_K = 100 + 10;

struct Range {
    int l, r;

    bool operator<(const Range& rhs) const { return l < rhs.l; }
};

int n, k;
Range range[MAX_K];
int f[2][MAX_N];
int q[MAX_N], fr, bk;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;

    for (int i = 1; i <= k; ++i) {
        auto& [l, r] = range[i];
        cin >> l >> r;
    }

    sort(range + 1, range + 1 + k);

    memset(f, 0x3f, sizeof(f));

    f[0][0] = 0;

    for (int i = 1; i <= k; ++i) {
        auto [l, r] = range[i];
        int now = (i & 1), pre = (now ^ 1);

        memcpy(f[now], f[pre], sizeof(f[now]));

        fr = 1;
        bk = 0;

        for (int j = r; j >= 0; --j) {
            while (fr <= bk && f[pre][r - j] <= f[pre][q[bk]]) --bk;

            q[++bk] = r - j;

            while (fr < bk && q[fr] < l - j) ++fr;

            f[now][j] = min(f[now][j], f[pre][q[fr]] + 1);
        }

        fr = 1;
        bk = 0;

        for (int j = 0; j <= min(n, r); ++j) {
            while (fr <= bk && f[pre][j] <= f[pre][q[bk]]) --bk;

            q[++bk] = j;

            while (fr < bk && q[fr] < j - r + l) ++fr;

            f[now][j] = min(f[now][j], f[pre][q[fr]] + 2);
        }
    }

    if (f[k & 1][n] != 0x3f3f3f3f) {
        cout << "Full" << endl;
        cout << f[k & 1][n] << endl;
    } else {
        cout << "Hungry" << endl;
    }

    return 0;
}
