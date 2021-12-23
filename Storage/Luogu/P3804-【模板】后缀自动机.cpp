#include <iostream>
#include <string>
#include <vector>
using namespace std;

constexpr int maxn = 2e6 + 10;

struct SuffixAutomaton {
    struct Node {
        int next[26], link, len, cloned;

        Node() {
            for (int i = 0; i < 26; ++i)
                next[i] = 0;

            link = len = 0;
            cloned = false;
        }

        int &operator[](int x) {
            return next[x];
        }
    };

    vector<Node> nodes;
    int last;

    SuffixAutomaton() {
        nodes.clear();
        last = 0;
        nodes.push_back(Node());
        nodes[0].link = -1;
    }

    int create(Node nd = Node()) {
        nodes.push_back(nd);
        return nodes.size() - 1;
    }

    void insert(char c) {
        int x = create(), p = last, w = c - 'a';
        nodes[x].len = nodes[last].len + 1;

        for (; p != -1 && !nodes[p][w]; p = nodes[p].link)
            nodes[p][w] = x;

        if (p == -1) {
            nodes[x].link = 0;
        } else {
            int q = nodes[p][w];

            if (nodes[q].len == nodes[p].len + 1) {
                nodes[x].link = q;
            } else {
                int nq = create(nodes[q]);
                nodes[nq].len = nodes[p].len + 1;
                nodes[nq].cloned = true;

                for (; p != -1 && nodes[p][w] == q; p = nodes[p].link)
                    nodes[p][w] = nq;

                nodes[q].link = nq;
                nodes[x].link = nq;
            }
        }

        last = x;
    }

    Node &operator[](int x) {
        return nodes[x];
    }

    int size() {
        return nodes.size() - 1;
    }
};

SuffixAutomaton sam;
vector<int> tree[maxn];
int cnt[maxn];
long long ans;

void link(int x, int y) {
    tree[x].push_back(y);
}

void dfs(int x) {
    if (!sam[x].cloned)
        cnt[x] = 1;

    for (int y : tree[x]) {
        dfs(y);
        cnt[x] += cnt[y];
    }

    if (cnt[x] > 1)
        ans = max(ans, 1ll * cnt[x] * sam[x].len);
} 

int main() {
    ios::sync_with_stdio(false);
    string s;
    cin >> s;

    for (char c : s)
        sam.insert(c);

    for (int i = 1; i <= sam.size(); ++i) 
        link(sam[i].link, i);

    dfs(0);
    cout << ans << endl;
    return 0;
}