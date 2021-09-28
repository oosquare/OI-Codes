#include <bits/stdc++.h>
using namespace std;

struct node {
    int x, y, step, dis;
};

int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, { -1, 0}};
int keyboard[100][100];
node nxt[100][100][4];
int vis[100][100];
int str[10100];
char tmpstr[10100];
int mapping[300];
int r, c, len;

void debug() {
    printf("<<<debug>>>\n");
}

void transform() {
    for (int i = 0; i <= 9; ++i) mapping[(char)('0' + i)] = i + 1;
    for (int i = 0; i < 26; ++i) mapping[(char)('A' + i)] = i + 11;
    mapping['-'] = 37; mapping['*'] = 38;
}

void preprocess() {
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            for (int k = 0; k < 4; k++) {
                int x = i, y = j;
                while (keyboard[x][y] == keyboard[x + dir[k][0]][y + dir[k][1]]) {
                    x += dir[k][0];
                    y += dir[k][1];
                }
                nxt[i][j][k] = (node) {x, y, 0, 0};
            }
        }
    }
}

int bfs() {
    memset(vis, 0, sizeof(vis));
    queue<node> q;
    int k = 1;
    int ans;
    while (str[k] == keyboard[1][1] && k <= len)++k;
    q.push((node) {1, 1, k, k - 1});
    vis[1][1] = k;
    while (!q.empty()) {
        node u = q.front(); q.pop();
        if (keyboard[u.x][u.y] == str[u.step]) {
            if (u.step == len) {ans = u.dis + 1; break;}
            vis[u.x][u.y] = u.step + 1;
            q.push((node) {u.x, u.y, u.step + 1, u.dis + 1});
            continue;
        }
        for (int i = 0; i < 4; i++) {
            node v = nxt[u.x][u.y][i];
            v.x += dir[i][0]; v.y += dir[i][1];
            if (v.x < 1 || v.x > r || v.y < 1 || v.y > c)continue;
            if (vis[v.x][v.y] >= u.step)continue;
            vis[v.x][v.y] = u.step;
            q.push((node) {v.x, v.y, u.step, u.dis + 1});
        }
    }
    return ans;
}

int main() {
    transform();
    while (scanf("%d%d", &r, &c) != EOF) {
        len = 0;
        for (int i = 1; i <= r; i++) {
            scanf("%s", tmpstr + 1);
            for (int j = 1; j <= c; j++) {
                keyboard[i][j] = mapping[tmpstr[j]];
            }
        }
        scanf("%s", tmpstr + 1);
        len = strlen(tmpstr + 1);
        for (int i = 1; i <= len; i++) {
            str[i] = mapping[tmpstr[i]];
        }
        str[++len] = 38;
        preprocess();
        printf("%d\n", bfs());

    }
}