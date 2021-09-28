#include <bits/stdc++.h>
using namespace std;

int dis[1 << 21], vis[1 << 21];
int n, m;
int t[1000];
char before[1000][50], after[1000][50];

bool dijkstra() {
    priority_queue<pair<int, int> > q;
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[(1 << n) - 1] = 0;
    q.push(make_pair(0, (1 << n) - 1));
    while (!q.empty()) {
        int x = q.top().second; q.pop();
        if (vis[x])continue;
        vis[x] = 1;
        if (x == 0)return 1;
        for (int i = 1; i <= m; i++) {
            int vaild = 1;
            for (int j = 0; j < n; j++) {
                if (before[i][j] == '-' && (x & (1 << j))) vaild = 0;
                if (before[i][j] == '+' && !(x & (1 << j))) vaild = 0;
            }
            if (vaild) {
                int y = x;
                for (int j = 0; j < n; j++) {
                    if (after[i][j] == '-') y &= ~(1 << j);
                    if (after[i][j] == '+') y |= (1 << j);
                }
                if (dis[y] > dis[x] + t[i]) {
                    dis[y] = dis[x] + t[i];
                    q.push(make_pair(-dis[y], y));
                }
            }
        }
    }
    return 0;
}

int main() {
    int task;
    while (1) {
        scanf("%d%d", &n, &m);
        if (!n && !m) return 0;
        for (int i = 1; i <= m; i++) {
            scanf("%d%s%s", &t[i], before[i], after[i]);
        }
        printf("Product %d\n", ++task);
        if (dijkstra()) {
            printf("Fastest sequence takes %d seconds.\n\n", dis[0]);
        } else {
            printf("Bugs cannot be fixed.\n\n");
        }
    }
}