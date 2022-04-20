#include <iostream>
#include <vector>

constexpr int MAX_N = 100000 + 10;

int n, q;
int a[MAX_N];

class SparseTable {
public:
    void init(int a[], int len) {
        logv[0] = -1;

        for (int i = 1; i <= len; ++i) {
            logv[i] = logv[i / 2] + 1;
            data[i][0] = a[i];
        }

        for (int j = 1; j <= 17; ++j)
            for (int i = 1; i + (1 << j) - 1 <= len; ++i)
                data[i][j] = std::min(data[i][j - 1], data[i + (1 << (j - 1))][j - 1]);
    }

    int query(int l, int r) {
        int s = logv[r - l + 1];
        return std::min(data[l][s], data[r - (1 << s) + 1][s]);
    }

private:
    int data[MAX_N][18], logv[MAX_N];
};

namespace Subtask12 {
    constexpr int MAX_N2 = 5000 + 10;

    SparseTable st;
    long long ans[MAX_N2][MAX_N2];

    void main() {
        st.init(a, n);

        for (int i = 1; i <= n; ++i)
            for (int j = i; j <= n; ++j)
                ans[i][j] = st.query(i, j);

        for (int i = 1; i <= n; ++i)
            for (int j = i + 1; j <= n; ++j)
                ans[i][j] += ans[i][j - 1];

        for (int j = 1; j <= n; ++j)
            for (int i = j + 1; i >= 1; --i)
                ans[i][j] += ans[i + 1][j];

        for (int i = 1; i <= q; ++i) {
            int l, r;
            std::cin >> l >> r;
            std::cout << ans[l][r] << std::endl;
        }
    }

} // namespace Subtask12

namespace Subtask3 {
    int st[MAX_N], top;
    long long sum;

    long long calc(int l, int r) {
        long long res = 0;
        sum = 0;
        top = 0;
        st[0] = l - 1;

        for (int i = l; i <= r; ++i) {
            while (top && a[st[top]] >= a[i]) {
                sum -= 1ll * (st[top] - st[top - 1]) * a[st[top]];
                --top;
            }

            sum += 1ll * (i - st[top]) * a[i];
            ++top;
            st[top] = i;
            res += sum;
        }

        return res;
    }

    void main() {
        for (int i = 1; i <= q; ++i) {
            int l, r;
            std::cin >> l >> r;
            std::cout << calc(l, r) << std::endl;
        }
    }
} // namespace Subtask3

namespace Subtask4 {
#define int long long
    constexpr int INF = 0x3f3f3f3f;
    using PairType = std::pair<long long, long long>;

    struct Modify {
        int h;
        long long v;
    };

    struct Query {
        int h, id, opt;
    };

    int lim, st[MAX_N], bl[MAX_N], br[MAX_N];
    long long ans[MAX_N];
    std::vector<Query> qs[MAX_N];
    std::vector<Modify> tag[MAX_N];
    long long s1[MAX_N], s2[MAX_N], s3[MAX_N], s4[MAX_N];

    void addp(int x1, int y1, int x2, int y2, int v) {
        tag[x1].push_back({ y1, v });
        tag[x2 + 1].push_back({ y1, -v });
        tag[x1].push_back({ y2 + 1, -v });
        tag[x2 + 1].push_back({ y2 + 1, v });
    }

    void query(int x1, int y1, int x2, int y2, int id) {
        qs[x2].push_back({ y2, id, 1 });
        qs[x1 - 1].push_back({ y2, id, -1 });
        qs[x2].push_back({ y1 - 1, id, -1 });
        qs[x1 - 1].push_back({ y1 - 1, id, 1 });
    }

    void add(int x, long long v1, long long v2, long long v3, long long v4) {
        while (x <= lim) {
            s1[x] += v1;
            s2[x] += v2;
            s3[x] += v3;
            s4[x] += v4;
            x += x & -x;
        }
    }

    std::pair<PairType, PairType> query(int x) {
        std::pair<PairType, PairType> ans;

        while (x) {
            ans.first.first += s1[x];
            ans.first.second += s2[x];
            ans.second.first += s3[x];
            ans.second.second += s4[x];
            x -= x & -x;
        }

        return ans;
    }

    void solve() {
        for (int i = 1; i <= lim; i++) {
            for (auto y : tag[i]) {
                long long v = y.v;
                add(y.h, v, (y.h - 1) * v, (i - 1) * v, (y.h - 1) * (i - 1) * v);
            }

            for (auto x : qs[i]) {
                long long sumv = 0, sumyv = 0, sumxv = 0, sumxyv = 0;
                std::pair<PairType, PairType> tmp = query(x.h);
                sumv = tmp.first.first;
                sumyv = tmp.first.second;
                sumxv = tmp.second.first;
                sumxyv = tmp.second.second;
                int j = x.h;
                ans[x.id] += 1ll * x.opt * (1ll * i * j * sumv - 1ll * i * sumyv - 1ll * j * sumxv + sumxyv);
            }
        }
    }

    void preprocess() {
        a[0] = -INF;
        a[n + 1] = -INF;
        int top = 0;

        for (int i = 1; i <= n + 1; i++) {
            while (top && a[i] < a[st[top]])
                br[st[top--]] = i;

            bl[i] = st[top];
            st[++top] = i;
        }

        for (int i = 1; i <= n; i++)
            if (i <= br[i] - 1 && bl[i] + 1 <= i)
                addp(i, bl[i] + 1, br[i] - 1, i, a[i]);
    }

    void main() {
        lim = n + 1;
        preprocess();

        for (int i = 1; i <= q; i++) {
            int l, r;
            std::cin >> l >> r;
            query(l, l, r, r, i);
        }

        solve();

        for (int i = 1; i <= q; i++)
            std::cout << ans[i] << std::endl;
    }
#undef int
} // namespace Subtask4

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("count.in", "r", stdin);
    std::freopen("count.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);

    std::cin >> n >> q;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    if (n <= 5000)
        Subtask12::main();
    else if (q <= 10)
        Subtask3::main();
    else
        Subtask4::main();

    return 0;
}