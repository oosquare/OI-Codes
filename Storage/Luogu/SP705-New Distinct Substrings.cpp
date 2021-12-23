#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

constexpr int maxn = 50000 + 10;

class SuffixAutomaton {
public:
    struct Node {
        int next[26], link, length;

        Node() {
            for (int i = 0; i < 26; ++i)
                next[i] = 0;

            link = length = 0;
        }

        int &operator[](int x) {
            return next[x];
        }
    };

    SuffixAutomaton() {
        clear();
    }

    void clear() {
        nodes[0] = Node();
        nodes[0].link = -1;
        uuid = last = 0;
    }

    Node &operator[](int x) {
        return nodes[x];
    }

    void insert(char c) {
        int x = create(), p = last, w = c - 'a';
        nodes[x].length = nodes[p].length + 1;

        for (; p != -1 && !nodes[p][w]; p = nodes[p].link)
            nodes[p][w] = x;

        if (p == -1) {
            nodes[x].link = 0;
        } else {
            int q = nodes[p][w];

            if (nodes[q].length == nodes[p].length + 1) {
                nodes[x].link = q;
            } else {
                int nq = create(q);
                nodes[nq].length = nodes[p].length + 1;
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

    int size() {
        return uuid;
    }
private:
    Node nodes[maxn * 2];
    int uuid, last;

    int create(int id = -1) {
        nodes[++uuid] = (id == -1 ? Node() : nodes[id]);
        return uuid;
    }
};

int t;
char str[maxn];
SuffixAutomaton sam;
vector<int> graph[maxn * 2];
int in[maxn * 2], f[maxn * 2];
int q[maxn * 2], fr, bk, s[maxn * 2], top;

void link(int x, int y) {
    graph[x].push_back(y);
    ++in[y];
}

void solve() {
    scanf("%s", str + 1);
    sam.clear();
    sam.insert(str, strlen(str + 1));

    for (int i = 0; i <= sam.size(); ++i) {
        f[i] = 0;
        in[i] = 0;
        graph[i].clear();
    }

    for (int i = 0; i <= sam.size(); ++i)
        for (int j = 0; j < 26; ++j)
            if (sam[i][j])
                link(i, sam[i][j]);

    q[fr = bk = 1] = 0;
    top = 0;

    while (fr <= bk) {
        int x = q[fr++];
        s[++top] = x;

        for (int y : graph[x]) {
            --in[y];

            if (!in[y])
                q[++bk] = y;
        }
    }

    while (top) {
        int x = s[top--];
        f[x] = 1;

        for (int y : graph[x])
            f[x] += f[y];
    }

    printf("%d\n", f[0] - 1);
}

int main() {
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}