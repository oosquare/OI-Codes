#include <bits/stdc++.h>
using namespace std;

struct Node {
    int next[26];
    int end;

    int &operator[](int x) {
        return next[x];
    }
};

constexpr int maxn = 30000 + 10;

int n, root = 1, uuid = root, cnt;
Node trie[maxn * 10];
bool ans[maxn];
string str[maxn];
bool graph[26][26];
int in[26];

void clear() {
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j)
            graph[i][j] = false;
        in[i] = 0;
    }
}

void link(int x, int y) {
    if (graph[x][y] == true)
        return;
    graph[x][y] = true;
    ++in[y];
}

bool circle() {
    queue<int> q;
    for (int i = 0; i < 26; ++i) {
        if (in[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int y = 0; y < 26; ++y) {
            if (graph[x][y] == false)
                continue;
            --in[y];
            if (in[y] == 0)
                q.push(y);
        }
    }

    for (int i = 0; i < 26; ++i) {
        if (in[i] != 0) {
            return true;
        }
    }
    return false;
}

void insert(int id) {
    int x = root;
    for (char c : str[id]) {
        if (trie[x][c - 'a'] == 0)
            trie[x][c - 'a'] = ++uuid;
        x = trie[x][c - 'a'];
    }
    trie[x].end = id;
}

bool check(int id) {
    int x = root;
    clear();
    for (char c : str[id]) { 
        if (trie[x].end != 0)
            return false;
        for (int i = 0; i < 26; ++i) {
            if (trie[x][i] == 0 || i == c - 'a')
                continue;
            link(c - 'a', i);
        }
        x = trie[x][c - 'a'];
    }
    return !circle();
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> str[i];
        insert(i);
    }
    
    for (int i = 1; i <= n; ++i) {
        ans[i] = check(i);
        if (ans[i] == true)
            ++cnt;
    }

    cout << cnt << endl;
    for (int i = 1; i <= n; ++i) {
        if (ans[i]) {
            cout << str[i] << endl;
        }
    }
    return 0;
}