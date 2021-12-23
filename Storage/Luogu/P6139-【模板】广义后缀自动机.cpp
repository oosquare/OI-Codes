#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

constexpr int maxn = 1e6 + 10;

class GeneralSuffixAutomaton {
public:
    struct Node {
        int next[26], link, len;

        Node() : link(0), len(0) {
            for (int i = 0; i < 26; ++i)
                next[i] = 0;
        }

        int &operator[](int x) {
            return next[x];
        }
    };

    GeneralSuffixAutomaton() : uuid(1), last(1) {}

    int size() {
        return uuid;
    }

    Node &operator[](int x) {
        return nodes[x];
    }

    void insert(char str[], int len) {
        int x = 1;

        for (int i = 1; i <= len; ++i) {
            int w = str[i] - 'a';

            if (!nodes[x][w])
                nodes[x][w] = ++uuid;

            x = nodes[x][w];
        }
    }

    void build() {
        queue<pair<int, char>> q;

        for (int i = 0; i < 26; ++i)
            if (nodes[1][i])
                q.push({1, (char)(i + 'a')});

        while (!q.empty()) {
            auto [x, c] = q.front();
            q.pop();
            int l = insert(c, x);
            
            for (int i = 0; i < 26; ++i)
                if (nodes[l][i])
                    q.push({l, (char)(i + 'a')});
        }
    }

private:
    Node nodes[maxn * 2];
    int uuid, last;

    int insert(char c, int last) {
        int w = c - 'a';
        int x = nodes[last][w], p = nodes[last].link;
        nodes[x].len = nodes[last].len + 1;

        for (; p && !nodes[p][w]; p = nodes[p].link)
            nodes[p][w] = x;
        
        if (!p) {
            nodes[x].link = 1;
        } else {
            int q = nodes[p][w];

            if (nodes[q].len == nodes[p].len + 1) {
                nodes[x].link = q;
            } else {
                int nq = ++uuid;

                for (int i = 0; i < 26; ++i)
                    nodes[nq][i] = (nodes[nodes[q][i]].len != 0 ? nodes[q][i] : 0);

                nodes[nq].link = nodes[q].link;
                nodes[nq].len = nodes[p].len + 1;
                nodes[x].link = nodes[q].link = nq;

                for (; p && nodes[p][w] == q; p = nodes[p].link)
                    nodes[p][w] = nq;
            }
        }

        return x;
    }
};

GeneralSuffixAutomaton gsam;
int n;
char str[maxn];
long long ans;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> (str + 1);
        gsam.insert(str, strlen(str + 1));
    }

    gsam.build();

    for (int i = 2; i <= gsam.size(); ++i)
        ans += gsam[i].len - gsam[gsam[i].link].len;

    cout << ans << endl;
    return 0;
}