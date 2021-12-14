#include <iostream>
#include <cstring>
using namespace std;

constexpr int maxn = 1e5 + 10;

struct Node {
    int next[26];
    int size;

    int &operator[](int x) {
        return next[x];
    }
};

int n, k;
char str[maxn];
Node tree[maxn];
int uuid;
bool f[maxn][2];

void insert(char str[]) {
    int len = strlen(str + 1), x = 0;

    for (int i = 1; i <= len; ++i) {
        if (!tree[x][str[i] - 'a']) {
            ++tree[x].size;
            tree[x][str[i] - 'a'] = ++uuid;
        }

        x = tree[x][str[i] - 'a'];
    }
}

void dfs1(int x) {
    for (int i = 0; i < 26; ++i) {
        if (!tree[x][i])
            continue;

        dfs1(tree[x][i]);
        f[x][0] |= (f[tree[x][i]][0] == false);
    }
}

void dfs2(int x) {
    if (!tree[x].size) {
        f[x][1] = true;
        return;
    }

    for (int i = 0; i < 26; ++i) {
        if (!tree[x][i])
            continue;

        dfs2(tree[x][i]);
        f[x][1] |= (f[tree[x][i]][1] == false);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;

    for (int i = 1; i <= n; ++i) {
        cin >> (str + 1);
        insert(str);
    }

    dfs1(0);
    dfs2(0);

    if (f[0][0] && !f[0][1])
        cout << (k % 2 ? "First" : "Second") << endl;
    else if (f[0][0] && f[0][1])
        cout << "First" << endl;
    else
        cout << "Second" << endl;

    return 0;
}