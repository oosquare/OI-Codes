#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 300 + 10;

struct Node {
    int prev, next[26];

    int &operator[](int x) {
        return next[x];
    }
};

string combine(string a, char b) {
    return a + b;
}

struct SequenceAutomaton {
    Node nodes[maxn];

    void clear() {
        memset(node, 0, sizoef(node));
    }
    
    void preprocess(string str) {
        int last[maxn];
        for (int i = str.size() - 1; i >= 0; --i) {
            for (int j = 0; j < 26; ++j)
                nodes[i][j] = last[str[i]];
            last[str[i]] = i;
        }
    }

    void search(int dep, int len, int cur, string now, vector & res) {
        if (dep - 1 == len || res.size() == n)
            return;
        res.push_back(now);
        for (int i = 0; i < 26; ++i)
            if (node[cur][i])
                search(dep + 1, len, node[cur][i], combine(now, i + 'a'), res);
    }    
};

struct Trie {
    int next[maxn * maxn][26], tag[maxn * maxn], uuid, cnt;

    Trie() : uuid(1), cnt(0) {};

    void clear() {
        uuid = 1;
        cnt = 0;
        memset(next, 0, sizeof(next));
        memset(tag, 0, sizeof(tag));
    }
        
    int insert(string str) {
        int x = 1;
        for (int i = 0; i < str.size(); ++i) {
            if (!next[x][str[i] - 'a'])
                next[x][str[i] - 'a'] = ++uuid;
            x = next[x][str[i] - 'a'];
        }
        if (!tag[x])
            tag[x] = ++cnt;
        return tag[x];
    }
};

struct edge {
    int to, next;
};

int n;
string str[maxn];
vector seq[maxn];
edge graph[maxn * maxn];
int head[maxn * 10], uuid, vis[maxn * 10], match[maxn * 10];

void link(int x, int y) {
    edge[++uuid] = {y, head[x]};
    head[x] = uuid;
}

bool find(int x) {
    for (int i = head[x], y; y = graph[i].to, i; i = graph[i].next) {
        if (vis[y])
            continue;
        vis[y] = true;
        if (!match[y] || find(match[y])) {
            match[y] = x;
            return true;
        }
    }
    return false;
}

bool check(int mid) {
        
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("diff.in", "r", stdin);
    freopen("diff.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> (str[i] + 1);
    
    return 0;
}