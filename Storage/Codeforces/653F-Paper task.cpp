#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

constexpr int maxn = 5e5 + 10;

class SuffixAutomaton {
public:
    struct Node {
        int next[2], link, len, pos;
        bool clone;

        Node() : link(0), len(0), pos(0), clone(false) {
            next[0] = next[1] = 0;
        }

        int &operator[](int x) {
            return next[x];
        }
    };

    SuffixAutomaton() : uuid(1), last(1) {}

    int size() {
        return uuid;
    }

    Node &operator[](int x) {
        return nodes[x];
    }

    void insert(char str, int pos) {
        int x = create(), p = last, w = (str == ')');
        last = x;
        nodes[x].len = nodes[p].len + 1;
        nodes[x].pos = pos;

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
                nodes[nq].clone = true;
                nodes[nq].len = nodes[p].len + 1;
                nodes[q].link = nodes[x].link = nq;

                for (; p && nodes[p][w] == q; p = nodes[p].link)
                    nodes[p][w] = nq;
            }
        }
    }

    void insert(char str[], int len) {
        for (int i = 1; i <= len; ++i)
            insert(str[i], i);
    }

private:
    Node nodes[maxn * 2];
    int uuid, last;

    int create(int id = -1) {
        nodes[++uuid] = (id == -1 ? Node() : nodes[id]);
        return uuid;
    }
};

int n;
char str[maxn];
SuffixAutomaton sam;
vector<int> tree[maxn * 2], val[maxn * 2];
int mi[maxn][20], logv[maxn];
int sum[maxn];
long long ans;

void link(int x, int y) {
    tree[x].push_back(y);
}

void preprocess() {
    logv[0] = -1;

    for (int i = 1; i <= n; ++i) {
        logv[i] = logv[i / 2] + 1;
        mi[i][0] = sum[i];
    }

    for (int j = 1; j <= 20; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            mi[i][j] = min(mi[i][j - 1], mi[i + (1 << (j - 1))][j - 1]);
}

int query(int l, int r) {
    int s = logv[r - l + 1];
    return min(mi[l][s], mi[r - (1 << s) + 1][s]);
}

void dfs(int x) {
    for (int y : tree[x]) {
        dfs(y);
        sam[x].pos = sam[y].pos;
    }

    int l0 = sam[x].pos - sam[x].len + 1, r0 = sam[x].pos - sam[sam[x].link].len;
    int l = l0, r = r0 + 1;

    while (l < r) {
        int mid = (l + r) / 2;

        if (query(mid, sam[x].pos) >= sum[sam[x].pos + 1]) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    auto &v = val[n + sum[sam[x].pos + 1]];
    ans += upper_bound(v.begin(), v.end(), r0) - lower_bound(v.begin(), v.end(), r);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> (str + 1);

    for (int i = n; i >= 1; --i)
        sum[i] = sum[i + 1] + (str[i] == '(' ? -1 : 1);

    for (int i = 1; i <= n + 1; ++i)
        val[n + sum[i]].push_back(i);

    sam.insert(str, n);
    preprocess();

    for (int i = 2; i <= sam.size(); ++i)
        link(sam[i].link, i);

    dfs(1);
    cout << ans << endl;
    return 0;
}