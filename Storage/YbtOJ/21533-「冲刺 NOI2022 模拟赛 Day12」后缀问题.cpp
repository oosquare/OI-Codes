#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
using namespace std;

constexpr int MAX_N = 2e5 + 10;

class SuffixAutomaton {
public:
    struct Node {
        int next[26];
        int link, len;
        bool cloned;

        Node() {
            for (int i = 0; i < 26; ++i)
                next[i] = 0;
            
            link = len = 0;
            cloned = false;
        }

        int & operator[](int x) {
            return next[x];
        }
    };

    SuffixAutomaton() {
        clear();
    }

    void insert(char c) {
        int w = (int) (c - 'a'), x = create(), p = last;
        last = x;
        nodes[x].len = nodes[p].len + 1;
        
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
                nodes[q].link = nodes[x].link = nq;

                for (; p && nodes[p][w] == q; p = nodes[p].link)
                    nodes[p][w] = nq;
            }
        }
    }

    Node & operator[](int x) {
        return nodes[x];
    }

    void clear() {
        nodes[1] = Node();
        nodes[1].cloned = true;
        tot = last = 1;
    }

    int size() {
        return tot;
    }
private:
    Node nodes[MAX_N * 2];
    int tot, last;

    int create(int id = -1) {
        nodes[++tot] = (id == -1 ? Node() : nodes[id]);
        
        if (id != -1)
            nodes[tot].cloned = true;
        
        return tot;
    }
};

int t, n;
char str[MAX_N];
SuffixAutomaton sam;
vector<int> tree[MAX_N * 2];

void link(int x, int y) {
    tree[x].push_back(y);
}

double calc(int x) {
    if (!sam[x].cloned)
        return sam[x].len;
    
    double sum = 0;

    for (int y : tree[x])
        sum += 1 / (calc(y) - sam[x].len);
    
    return 1 / sum + sam[x].len;
}

void solve() {
    cin >> (str + 1);
    n = (int) strlen(str + 1);
    sam.clear();

    for (int i = n; i >= 1; --i)
        sam.insert(str[i]);
    
    for (int i = 1; i <= sam.size(); ++i)
        tree[i].clear();
    
    for (int i = 2; i <= sam.size(); ++i)
        link(sam[i].link, i);
            
    cout << calc(1) << endl;
}

int main() {
    freopen("suffix.in", "r", stdin);
    freopen("suffix.out", "w", stdout);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    cin >> t;

    while (t--)
        solve();

    return 0;
}
