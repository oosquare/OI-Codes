#include <iostream>
#include <algorithm>
using namespace std;

const int lim = 101;
const int inf = 0x7fffffff;

struct edge {
    int x, y, w;
};

edge e[10001];
int father[101];
int n, m, tot;

bool cmp(edge a, edge b) {
    return a.w > b.w;
}

int find(int x) {
    if (father[x] == x)return x;
    return father[x] = find(father[x]);
}

void sln() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> e[i].x >> e[i].y >> e[i].w;
    }
    sort(e + 1, e + 1 + m, cmp);
    int ans = inf;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            father[j] = j;
        }
        int k = 0;
        for (int j = i; j <= m; j++) {
            int x = find(e[j].x), y = find(e[j].y);
            if (x != y) {
                father[x] = y;
                k++;
                if (k == n - 1) {
                    ans = min(ans, e[i].w - e[j].w);
                    break;
                }
            }

        }

    }
    if (ans < inf)printf("%d\n", ans);
    else printf("-1\n");
}

int main() {
    while (1) {
        cin >> n >> m;
        if (!n && !m)break;
        for (int i = 1; i <= m; i++) {
            cin >> e[i].x >> e[i].y >> e[i].w;
        }
        sort(e + 1, e + 1 + m, cmp);
        int ans = inf;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                father[j] = j;
            }
            int k = 0;
            for (int j = i; j <= m; j++) {
                int x = find(e[j].x), y = find(e[j].y);
                if (x != y) {
                    father[x] = y;
                    k++;
                    if (k == n - 1) {
                        ans = min(ans, e[i].w - e[j].w);
                        break;
                    }
                }
            }

        }
        if (ans < inf)printf("%d\n", ans);
        else printf("-1\n");
    }
}