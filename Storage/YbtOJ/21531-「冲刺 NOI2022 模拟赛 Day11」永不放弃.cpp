#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

constexpr int MAX_N = 1000000 + 10;

class SegmentTree {
public:
    void init(int len) {
        build(1, 1, len);
    }

    void add(int p) {
        add(1, p);
    }

    std::pair<long long, int> query(int l, int r) {
        return query(1, l, r);
    }
private:
    struct Node {
        int left, right;
        long long cnt;
        int val;
    };

    Node tree[MAX_N * 4];

    void pushup(int x) {
        tree[x].cnt = tree[x * 2].cnt + tree[x * 2 + 1].cnt;
        tree[x].val = std::max(tree[x * 2].val, tree[x * 2 + 1].val);
    }

    void build(int x, int l, int r) {
        tree[x].left = l;
        tree[x].right = r;

        if (l == r)
            return;

        int mid = (l + r) / 2;
        build(x * 2, l, mid);
        build(x * 2 + 1, mid + 1, r);
    }

    void add(int x, int p) {
        if (tree[x].left == tree[x].right) {
            ++tree[x].cnt;
            tree[x].val = std::max(tree[x].val, p);
            return;
        }

        int mid = (tree[x].left + tree[x].right) / 2;

        if (p <= mid)
            add(x * 2, p);
        else
            add(x * 2 + 1, p);

        pushup(x);
    }

    std::pair<long long, int> query(int x, int l, int r) {
        if (l <= tree[x].left && tree[x].right <= r)
            return { tree[x].cnt, tree[x].val };

        int mid = (tree[x].left + tree[x].right) / 2;
        std::pair<long long, int> res = { 0, 0 };

        if (l <= mid) {
            auto res2 = query(x * 2, l, r);
            res.first += res2.first;
            res.second = std::max(res.second, res2.second);
        }

        if (mid < r) {
            auto res2 = query(x * 2 + 1, l, r);
            res.first += res2.first;
            res.second = std::max(res.second, res2.second);
        }

        return res;
    }
};

int n0, n, type;
char str0[MAX_N], str[MAX_N];
int len[MAX_N];
SegmentTree tree;
std::vector<int> ranges[MAX_N];
std::pair<int, int> ra[MAX_N];
int tot, nxt, now;
long long cnt, ans;

void manacher() {
    int mx = 0, mid = 0;

    for (int i = 1; i <= n; ++i) {
        if (i < mx)
            len[i] = std::min(len[2 * mid - i], mx - i + 1);
        else
            len[i] = 1;

        while (i - len[i] >= 1 && i - len[i] <= n && str[i - len[i]] == str[i + len[i]])
            ++len[i];

        if (i + len[i] - 1 > mx) {
            mx = i + len[i] - 1;
            mid = i;
        }
    }
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("giveup.in", "r", stdin);
    std::freopen("giveup.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);

    std::cin >> (str0 + 1);
    std::cin >> type;

    n0 = (int) std::strlen(str0 + 1);

    str[0] = '$';

    for (int i = 1; i <= n0; ++i) {
        str[++n] = '#';
        str[++n] = str0[i];
    }

    str[++n] = '#';

    manacher();

    for (int i = 1; i <= n; i += 2)
        ranges[i - len[i] + 1].push_back(i);

    tree.init(n);

    for (int i = 1; i <= n; i += 2) {
        for (auto mid : ranges[i])
            tree.add(mid);

        auto res = tree.query(i + 1, i + (len[i] - 1) / 2);
        cnt += res.first;

        if (res.second) {
            int r = res.second + std::min(res.second - i, len[res.second] - 1);
            int l = 2 * i - r;
            ra[++tot] = { l, r };
        }
    }

    cnt += n0;

    for (int i = 2; i < n; i += 2)
        ra[++tot] = { i - 1, i + 1 };

    std::sort(ra + 1, ra + 1 + tot, [](const auto & lhs, const auto & rhs) {
        return (lhs.first != rhs.first ? lhs.first < rhs.first : lhs.second > rhs.second);
    });

    for (int i = 1; i <= tot; ++i) {
        if (ra[i].second <= nxt)
            continue;
            
        if (ra[i].first > now) {
            ++ans;
            now = nxt + 1;
        }

        nxt = std::max(nxt, ra[i].second);
    }

    if (type == 1)
        std::cout << cnt << std::endl;
    else if (type == 2)
        std::cout << ans << std::endl;
    else
        std::cout << cnt << " " << ans << std::endl;

    return 0;
}
