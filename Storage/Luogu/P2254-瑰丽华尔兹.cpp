#include <bits/stdc++.h>
#define FILE_IO true
#define TIME_LIMIT 1000
using namespace std;

template <typename T> void read(T &number) {
    number = 0;
    int symbol = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-')
            symbol *= -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        number = (number << 3) + (number << 1) + c ^ '0';
        c = getchar();
    }
    number *= symbol;
}

struct info {
    int val, pos;
};

int f[205][205];
info q[40001];
char mapp[205][205];
int dx[5] = {0, -1, 1, 0, 0};
int dy[5] = {0, 0, 0, -1, 1};
int n, m, k, sx, sy, ans;

void solve(int x, int y, int l, int d) {
    int front = 1, back = 0;
    for (int i = 1; 1 <= x && x <= n && 1 <= y && y <= m;
         ++i, x += dx[d], y += dy[d]) {
        if (mapp[x][y] == 'x') {
            front = 1;
            back = 0;
        } else {
            while (front <= back && q[back].val + i - q[back].pos < f[x][y])
                --back;
            q[++back] = (info){f[x][y], i};
            if (q[back].pos - q[front].pos > l)
                ++front;
            f[x][y] = q[front].val + i - q[front].pos;
            ans = max(ans, f[x][y]);
        }
    }
}

int main(int argc, char *argv[]) {
#if !defined(ONLINE_JUDGE) && FILE_IO
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
    clock_t stime = clock();
#endif
    // [ Codes ] ////////////////////////

    scanf("%d%d%d%d%d", &n, &m, &sx, &sy, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%s", mapp[i] + 1);
    memset(f, 0xf3, sizeof(f));
    f[sx][sy] = 0;
    for (int kk = 1; kk <= k; ++kk) {
        int s, t, d;
        scanf("%d%d%d", &s, &t, &d);
        int l = t - s + 1;
        if (d == 1)
            for (int i = 1; i <= m; ++i)
                solve(n, i, l, d);
        if (d == 2)
            for (int i = 1; i <= m; ++i)
                solve(1, i, l, d);
        if (d == 3)
            for (int i = 1; i <= n; ++i)
                solve(i, m, l, d);
        if (d == 4)
            for (int i = 1; i <= n; ++i)
                solve(i, 1, l, d);
    }
    printf("%d\n", ans);

    // [ Codes ] ////////////////////////
#if !defined(ONLINE_JUDGE) && FILE_IO
    clock_t etime = clock();
    printf("\n----------------------------\n");
    printf("Time : %dms\n", etime - stime);
    if (etime - stime >= TIME_LIMIT) {
        printf("<<< Warning >>> Time Limited Exceeded\n");
    }
#endif
    return 0;
}
