#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

constexpr int MAX_N = 300000 + 10;

class SuffixAutomaton {
public:
    struct Node {
        int next[26], link, len, pos;
        bool clone;

        Node() : link(0), len(0), pos(0), clone(false) {
            for (int i = 0; i < 26; ++i)
                next[i] = 0;
        }

        int &operator[](int x) { return next[x]; }
    };

    SuffixAutomaton() : total(1), last(1) {}

    int add(char c, int pos) {
        int x = create(), p = last, w = c - 'a';
        nodes[x].pos = pos;
        nodes[x].len = nodes[p].len + 1;
        last = x;

        for (; p && !nodes[p][w]; p = nodes[p].link)
            nodes[p][w] = x;

        if (!p) {
            nodes[x].link = 1;
        } else {
            int q = nodes[p][w];

            if (nodes[q].len == nodes[p].len + 1) {
                nodes[x].link = q;
            } else {
                int nq = create(q);
                nodes[nq].len = nodes[p].len + 1;
                nodes[x].link = nodes[q].link = nq;

                for (; p && nodes[p][w] == q; p = nodes[p].link)
                    nodes[p][w] = nq;
            }
        }

        return x;
    }

    int size() { return total; }

    Node &operator[](int x) { return nodes[x]; }

private:
    Node nodes[MAX_N * 2];
    int total, last;

    int create(int id = -1) {
        nodes[++total] = (id == -1 ? Node() : nodes[id]);

        if (id != -1)
            nodes[total].clone = false;

        return total;
    }
};

struct Range {
    int l, r;
};

int n;
std::string s[MAX_N];
std::string t;
std::vector<int> tree[MAX_N * 2];
int id[MAX_N], len[MAX_N * 2];
SuffixAutomaton sam;
Range ranges[MAX_N];
int tot;
int cnt[MAX_N];

void link(int x, int y) { tree[x].push_back(y); }

void match(const std::string &pattern) {
    int x = 1;

    for (int i = 0; i < (int) pattern.size(); ++i) {
        if (!sam[x][pattern[i] - 'a'])
            return;

        x = sam[x][pattern[i] - 'a'];
    }

    len[x] = std::max(len[x], (int) pattern.size());
}

void dfs(int x) {
    for (int y : tree[x]) {
        len[y] = std::max(len[y], len[x]);
        dfs(y);
    }
}

bool check() {
    for (int i = 1; i <= tot; ++i) {
        ++cnt[ranges[i].l];
        --cnt[ranges[i].r + 1];
    }

    for (int i = 1; i <= (int) t.size(); ++i) {
        cnt[i] += cnt[i - 1];

        if (cnt[i] == 0)
            return false;
    }

    return true;
}

int calc() {
    int ans = 0, now = 0, nxt = 0;

    if (!check())
        return -1;

    std::sort(ranges + 1, ranges + 1 + tot, [](const auto &lhs, const auto &rhs) {
        return (lhs.l != rhs.l ? lhs.l < rhs.l : lhs.r > rhs.r);
    });

    for (int i = 1; i <= tot; ++i) {
        if (ranges[i].r <= nxt)
            continue;

        if (ranges[i].l > now) {
            ++ans;
            now = nxt + 1;
        }

        nxt = std::max(nxt, ranges[i].r);
    }

    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> n;
    std::cin >> t;

    for (int i = 1; i <= n; ++i)
        std::cin >> s[i];

    for (int i = 0; i < (int) t.size(); ++i)
        id[i + 1] = sam.add(t[i], i + 1);

    for (int i = 2; i <= sam.size(); ++i)
        link(sam[i].link, i);

    for (int i = 1; i <= n; ++i)
        match(s[i]);

    dfs(1);

    for (int i = 1; i <= (int) t.size(); ++i)
        if (len[id[i]])
            ranges[++tot] = { i - len[id[i]] + 1, i };

    std::cout << calc() << std::endl;
    return 0;
}
