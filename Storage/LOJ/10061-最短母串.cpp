#include <bits/stdc++.h>
using namespace std;

struct node {
    int next[26];
    int fail;
    int status;
    int &operator[](int x) { return next[x]; }
};

struct record {
    int pre, val;
};

struct record2 {
    int present, status, recordid;
};

constexpr int maxn = 15;
constexpr int maxl = 6000;
int n;
node ac[maxl];
int total = 1, root = 1;
record path[2000000];
int ptotal = 0;
bool vis[maxl][1 << 15];
char ss[maxl];

void insert(char s[], int id) {
    int len = strlen(s), x = root;
    for (int i = 0; i < len; ++i) {
        int y = s[i] - 'A';
        if (!ac[x][y])
            ac[x][y] = ++total;
        x = ac[x][y];
    }
    ac[x].status |= 1 << (id - 1);
}

void build() {
    queue<int> q;
    for (int i = 0; i < 26; ++i)
        ac[0][i] = root;
    q.push(root);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 0; i < 26; ++i) {
            if (!ac[x][i])
                ac[x][i] = ac[ac[x].fail][i];
            else {
                ac[ac[x][i]].fail = ac[ac[x].fail][i];
                ac[ac[x][i]].status |= ac[x].status;
                q.push(ac[x][i]);
            }
        }
    }
    for (int i = 1; i <= total; ++i)
        ac[i].status |= ac[ac[i].fail].status;
}

void output(int id) {
    if (id == 0)
        return;
    output(path[id].pre);
    printf("%c", (char)(path[id].val + 'A'));
}

void DP() {
    queue<record2> q;
    q.push((record2){1, 0, 0});
    vis[1][0] = 1;
    int ends = (1 << n) - 1;
    while (!q.empty()) {
        int x = q.front().present, s = q.front().status, r = q.front().recordid;
        q.pop();
        if (s == ends) {
            output(r);
            return;
        }
        for (int i = 0; i < 26; ++i) {
            int y = ac[x][i];
            int ns = ac[y].status | s;
            if (vis[y][ns])
                continue;
            path[++ptotal] = (record){r, i};
            vis[y][ns] = true;
            q.push((record2){y, ns, ptotal});
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", ss);
        insert(ss, i);
    }
    build();
    DP();
    return 0;
}