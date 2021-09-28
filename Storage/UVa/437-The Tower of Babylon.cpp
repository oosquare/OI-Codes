#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

struct Cube {
    int x, y, z;
    void init(int a, int b, int cu) {x = a; y = b; z = cu;}
};

struct Node {
    int to, nxt, weight;
};

const int lim = 100;

Cube cu[lim * lim];
Node e[lim * lim];
int head[lim];
int in[lim];
int f[lim];
int tot, n;

void insert(int x, int y, int w) {
    tot++;
    e[tot].to = y;
    e[tot].weight = w;
    e[tot].nxt = head[x];
    head[x] = tot;
    in[y]++;
}

int topology() {
    queue<int> q;
    int ans = -0x3f3f3f3f;
    for (int i = 1; i <= 3 * n; i++) {
        if (!in[i]) {
            q.push(i);
        }
        f[i] = cu[i].z;
    }
    while (!q.empty()) {
        int x = q.front(); q.pop();
        ans = max(ans, f[x]);
        for (int i = head[x]; i; i = e[i].nxt) {
            int y = e[i].to;
            int w = e[i].weight;
            f[y] = max(f[y], f[x] + w);
            if (--in[y] == 0)q.push(y);
        }
    }
    return ans;
}

void input() {
    tot = 0;
    memset(e, 0, sizeof(e));
    memset(head, 0, sizeof(head));
    memset(in, 0, sizeof(in));
    memset(cu, 0, sizeof(cu));
    scanf("%d", &n);
    if (!n)exit(0);
    for (int i = 1; i <= 3 * n; i += 3) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        cu[i].init(max(x, y), min(x, y), z);
        cu[i + 1].init(max(x, z), min(x, z), y);
        cu[i + 2].init(max(z, y), min(z, y), x);
    }
    for (int i = 1; i <= n * 3; i++) {
        for (int j = 1; j <= n * 3; j++) {
            if (cu[i].x > cu[j].x && cu[i].y > cu[j].y) {
                insert(i, j, cu[j].z);
            }
        }
    }
}

int main() {
    int cases = 0;
    while (1) {
        input();
        printf("Case %d: maximum height = %d\n", ++cases, topology());
    }
}