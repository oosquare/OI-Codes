#include <iostream>
#include <cstring>
#include <vector>
#include <set>

using namespace std;

constexpr int maxn = 10000 + 10;

class SuffixAutomaton {
public:
    struct Node {
        int next[26], link, len, pos;
        bool clone;

        Node() : link(0), len(0), pos(0), clone(false) {
            for (int i = 0; i < 26; ++i)
                next[i] = 0;
        }

        int &operator[](int x) {
            return next[x];
        }
    };

    SuffixAutomaton() {
        clear();
    }

    void clear() {
        nodes.clear();
        last = 0;
        nodes.push_back(Node());
        nodes[0].link = -1;
    }

    int size() {
        return nodes.size() - 1;
    }

    Node &operator[](int x) {
        return nodes[x];
    }


    void insert(char c, int e) {
        int x = create(), p = last, w = c - 'a';
        last = x;
        nodes[x].len = nodes[p].len + 1;
        nodes[x].pos = e;

        for (; p != -1 && !nodes[p][w]; p = nodes[p].link)
            nodes[p][w] = x;

        if (p == -1) {
            nodes[x].link = 0;
        } else {
            int q = nodes[p][w];

            if (nodes[q].len == nodes[p].len + 1) {
                nodes[x].link = q;
            } else {
                int nq = create(q);
                nodes[nq].len = nodes[p].len + 1;
                nodes[nq].clone = true;
                nodes[q].link = nodes[x].link = nq;

                for (; p != -1 && nodes[p][w] == q; p = nodes[p].link)
                    nodes[p][w] = nq;
            }
        }
    }

    void insert(char str[], int len) {
        for (int i = 1; i <= len; ++i)
            insert(str[i], i);
    }
public:
    vector<Node> nodes;
    int last;

    int create(int id = -1) {
        nodes.push_back(id == -1 ? Node() : nodes[id]);
        return nodes.size() - 1;
    }
};

int n, m;
char s[maxn], t[maxn];
SuffixAutomaton sams, samt;
int fs[maxn], ft[maxn];
vector<int> tree[maxn];
set<int> st[maxn];
int pre[maxn][2];

void link(int x, int y) {
    tree[x].push_back(y);
}

void dfss(int x) {
    fs[x] = (sams[x].clone == false);

    for (int y : tree[x]) {
        dfss(y);
        fs[x] += fs[y];
    }
}

void dfst(int x) {
    if (!samt[x].clone) {
        st[x].insert(samt[x].pos);
        ft[x] = 1;
    }

    for (int y : tree[x]) {
        dfst(y);
        ft[x] += ft[y];

        if (ft[x] <= 1)
            st[x].merge(st[y]);
    }

    if (ft[x] == 1 && x) {
        pre[*st[x].begin()][0] = samt[samt[x].link].len + 1;
        pre[*st[x].begin()][1] = samt[x].len;
    }
}

bool match(int lim) {
    int x = 0, l = 0;

    for (int i = 1; i <= m; ++i) {
        int w = t[i] - 'a';

        while (x && !sams[x][w]) {
            x = sams[x].link;
            l = sams[x].len;
        }

        if (sams[x][w]) {
            ++l;
            x = sams[x][w];
        }

        if (l != 0 && l <= lim) {
            if (fs[x] == 1 && pre[i][0] <= l && l <= pre[i][1])
                return true;

            if (l == lim) {
                --l;

                if (l <= sams[sams[x].link].len)
                    x = sams[x].link;
            }
        }
    }

    return false;
}

bool check(int lim) {
    return match(lim);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> (s + 1) >> (t + 1);
    n = strlen(s + 1);
    m = strlen(t + 1);
    sams.insert(s, n);
    samt.insert(t, m);

    for (int i = 1; i <= sams.size(); ++i)
        link(sams[i].link, i);

    dfss(0);

    for (int i = 0; i <= samt.size(); ++i)
        tree[i].clear();

    for (int i = 1; i <= samt.size(); ++i)
        link(samt[i].link, i);

    dfst(0);

    int l = 1, r = min(n, m), ans = -1;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    cout << ans << endl;
    return 0;
}