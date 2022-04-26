#include <iostream>
#include <queue>

constexpr int MAX_N = 100000 + 10;
constexpr int INF = 0x3f3f3f3f;

int n;
char str[MAX_N];
int d[MAX_N];
bool vis[MAX_N];
int f[MAX_N][8], dis[8][8];
int mark[MAX_N];
int num[MAX_N][1 << 8];
int ans;
long long cnt;

void bfs(int c) {
    std::queue<int> q;

    for (int i = 1; i <= n; ++i) {
        if (str[i] - 'a' == c) {
            q.push(i);
            d[i] = 0;
        } else {
            d[i] = -1;
        }
    }

    for (int i = 0; i < 8; ++i)
        vis[i] = (i == c);

    while (!q.empty()) {
        int x = q.front();
        q.pop();

        if (!vis[str[x] - 'a']) {
            vis[str[x] - 'a'] = true;

            for (int y = 1; y <= n; ++y) {
                if (str[y] != str[x] || d[y] != -1)
                    continue;

                d[y] = d[x] + 1;
                q.push(y);
            }
        }

        if (x > 1 && d[x - 1] == -1) {
            d[x - 1] = d[x] + 1;
            q.push(x - 1);
        }

        if (x < n && d[x + 1] == -1) {
            d[x + 1] = d[x] + 1;
            q.push(x + 1);
        }
    }

    for (int i = 1; i <= n; ++i)
        f[i][c] = (d[i] == -1 ? INF : d[i]);
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("map.in", "r", stdin);
    std::freopen("map.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);

    std::cin >> n;
    std::cin >> (str + 1);

    for (int i = 0; i < 8; ++i)
        bfs(i);

    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            dis[i][j] = INF;

    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < 8; ++j)
            dis[str[i] - 'a'][j] = std::min(dis[str[i] - 'a'][j], f[i][j]);

    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < 8; ++j)
            if (f[i][j] != dis[str[i] - 'a'][j])
                mark[i] |= (1 << j);

    for (int i = 1; i <= n; ++i) {
        for (int j = std::max(i - 15, 1); j < i; ++j) {
            int now = i - j;

            for (int k = 0; k < 8; ++k)
                now = std::min(now, f[i][k] + 1 + f[j][k]);

            if (now > ans) {
                ans = now;
                cnt = 1;
            } else if (now == ans) {
                ++cnt;
            }
        }

        int t = i - 16;

        if (t >= 1)
            ++num[str[t] - 'a'][mark[t]];

        for (int j = 0; j < 8; ++j) {
            for (int k = 0; k < (1 << 8); ++k) {
                if (!num[j][k])
                    continue;

                int now = INF;

                for (int l = 0; l < 8; ++l)
                    now = std::min(now, f[i][l] + 1 + dis[l][j] + ((k >> l) & 1));

                if (now > ans) {
                    ans = now;
                    cnt = num[j][k];
                } else if (now == ans) {
                    cnt += num[j][k];
                }
            }
        }
    }

    std::cout << ans << " " << cnt << std::endl;
    return 0;
}