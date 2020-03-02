#include <iostream>
#include <string>
#include <queue>
#include <cstring>
using namespace std;

const int Lim = 1000001;

inline int transform(char x) {
    if (x == 'N')
        return 0;
    if (x == 'S')
        return 1;
    if (x == 'E')
        return 2;
    if (x == 'W')
        return 3;
}

class ACAutomaton {
public:
    void insert(char s[]) {
        int len = strlen(s + 1), u = 1;
        for (int i = 1; i <= len; i++) {
            int c = transform(s[i]);
            if (!Trie[u].Next[c]) {
                Trie[u].Next[c] = ++Total;
            }
            u = Trie[u].Next[c];
        }
    }

    void process() {
        queue<int> q;
        for (int i = 0; i < 4; i++) {
            Trie[0].Next[i] = 1;
        }
        q.push(1);
        Trie[1].Fail = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                if (!Trie[u].Next[i]) {
                    Trie[u].Next[i] = Trie[Trie[u].Fail].Next[i];
                } else {
                    q.push(Trie[u].Next[i]);
                    int v = Trie[u].Fail;
                    Trie[Trie[u].Next[i]].Fail = Trie[v].Next[i];
                }
            }
        }
    }

    void match(char s[]) {
        int len = strlen(s + 1), u = 1;
        for (int i = 1; i <= len; i++) {
            int c = transform(s[i]);
            int k = Trie[u].Next[c];
            while (k > 1) {
                Trie[k].Matched = true;
                k = Trie[k].Fail;
            }
            u = Trie[u].Next[c];
        }
    }

    int count(char s[]) {
        int u = 1, len = strlen(s + 1), ans = 0;
        for (int i = 1; i <= len; i++) {
            int c = transform(s[i]);
            u = Trie[u].Next[c];
            if (Trie[u].Matched)
                ans = i;
        }
        return ans;
    }

    void clear() {
        memset(Trie, 0, sizeof(Trie));
        for (int i = 0; i < 4; i++) {
            Trie[0].Next[i] = 1;
            Trie[1].Next[i] = 0;
        }
        Total = 1;
    }

private:
    struct Node {
        bool Matched;
        int Fail;
        int Next[5];
    };
    Node Trie[Lim];
    int Total;
};

ACAutomaton Auto;
int N, M;
char ModelString[Lim][101], MainString[Lim];

int main() {
    cin >> N >> M;
    cin >> MainString + 1;
    Auto.clear();
    for (int i = 1; i <= M; i++) {
        cin >> ModelString[i] + 1;
        Auto.insert(ModelString[i]);
    }
    Auto.process();
    Auto.match(MainString);
    for (int i = 1; i <= M; i++) {
        cout << Auto.count(ModelString[i]) << endl;
    }
}