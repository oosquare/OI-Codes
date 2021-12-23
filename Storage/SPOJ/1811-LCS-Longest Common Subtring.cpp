#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

constexpr int maxn = 2.5e5 + 10;

class SuffixAutomaton {
public:
    struct Node {
        int next[26], link, len;

        Node() {
            for (int i = 0; i < 26; ++i)
                next[i] = 0;

            link = len = 0;
        }

        int &operator[](int x) {
            return next[x];
        }
    };

    SuffixAutomaton() {
        nodes.push_back(Node());
        last = 0;
        nodes[0].link = -1;
    }

    Node &operator[](int x) {
        return nodes[x];
    }

    int size() {
        return nodes.size() - 1;
    }

    void insert(char c) {
        int x = create(), p = last, w = c - 'a';
        nodes[x].len = nodes[p].len + 1;

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
                nodes[q].link = nodes[x].link = nq;

                for (; p != -1 && nodes[p][w] == q; p = nodes[p].link)
                    nodes[p][w] = nq;
            }
        }

        last = x;
    }

    void insert(char str[], int len) {
        for (int i = 1; i <= len; ++i)
            insert(str[i]);
    }
private:

    vector<Node> nodes;
    int last;

    int create(int id = -1) {
        nodes.push_back(id == -1 ? Node() : nodes[id]);
        return nodes.size() - 1;
    }
};

SuffixAutomaton sam;
char s[maxn], t[maxn];

int find(char s[], char t[], int ls, int lt) {
    sam.insert(s, ls);

    int ans = 0, x = 0, l = 0;

    for (int i = 1; i <= lt; ++i) {
        int w = t[i] - 'a';

        while (x && !sam[x][w]) {
            x = sam[x].link;
            l = sam[x].len;
        }

        if (sam[x][w]) {
            x = sam[x][w];
            ++l;
        }

        ans = max(ans, l);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> (s + 1) >> (t + 1);
    cout << find(s, t, strlen(s + 1), strlen(t + 1));
    return 0;
}