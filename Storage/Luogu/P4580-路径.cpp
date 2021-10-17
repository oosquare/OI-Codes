#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 20 + 10;
constexpr int maxk = 30 + 10;
constexpr int mod = 1e9 + 7;

int n, m, k, ans;
vector<int> graph[maxn];
int f[maxn][maxk][maxk][2];
char sym[maxn];

bool vaild(char now, char front) {
    if ('0' <= now && now <= '9') {
        if ('0' <= front && front <= '9')
            return true;
        if (front == '+' || front == '-' || front == '*' || front == '/')
            return true;
        if (front == '(')
            return true;
        return false;
    }
    if (now == '+' || now == '-' || now == '*' || now == '/') {
        if ('0' <= front && front <= '9')
            return true;
        if (front == ')')
            return true;
        if (front == '(' && now == '-')
            return true;
        return false;
    }
    if (now == '(') {
        if (front == '+' || front == '-' || front == '*' || front == '/')
            return true;
        if (front == '(')
            return true;
        return false;
    }
    if (now == ')') {
        if ('0' <= front && front <= '9')
            return true;
        if (front == ')')
            return true;
        return false;
    }
    return false;
}

void link(int x, int y) {
    graph[x].push_back(y);
    graph[y].push_back(x);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    cin >> (sym + 1);

    for (int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
    }

    for (int x = 1; x <= n; ++x) {
        if (sym[x] == '0')
            f[x][1][0][1] = 1;
        if ('1' <= sym[x] && sym[x] <= '9')
            f[x][1][0][0] = 1;
        if (sym[x] == '(')
            f[x][1][1][0] = 1;
        if (sym[x] == '-')
            f[x][1][0][0] = 1;
    }

    for (int i = 2; i <= k; ++i) {
        for (int x = 1; x <= n; ++x) {
            for (int j = 0; j <= (k + 1) / 2; ++j) {
                for (int y : graph[x]) {
                    char now = sym[x], front = sym[y];

                    if (!vaild(now, front))
                        continue;

                    if (now == '0') {
                        if (front == '+' || front == '-' || front == '*' || front == '/' || front == '(')
                            (f[x][i][j][1] += f[y][i - 1][j][0]) %= mod;
                        else
                            (f[x][i][j][0] += f[y][i - 1][j][0]) %= mod;
                    }

                    if ('1' <= now && now <= '9') {
                        (f[x][i][j][0] += f[y][i - 1][j][0]) %= mod;
                    }

                    if (now == '+' || now == '-' || now == '*' || now == '/') {
                        (f[x][i][j][0] += f[y][i - 1][j][0]) %= mod;

                        if (front == '0')
                            (f[x][i][j][0] += f[y][i - 1][j][1]) %= mod;
                    }

                    if (now == '(') {
                        if (j > 0)
                            (f[x][i][j][0] += f[y][i - 1][j - 1][0]) %= mod;
                    }

                    if (now == ')') {
                        (f[x][i][j][0] += f[y][i - 1][j + 1][0]) %= mod;

                        if (front == '0')
                            (f[x][i][j][0] += f[y][i - 1][j + 1][1]) %= mod;
                    }
                }
            }
        }
    }

    for (int x = 1; x <= n; ++x) {
        if (sym[x] == '+' || sym[x] == '-' || sym[x] == '*' || sym[x] == '/' || sym[x] == '(')
            continue;
        
        (ans += f[x][k][0][0]) %= mod;
        
        if (sym[x] == '0')
            (ans += f[x][k][0][1]) %= mod;
    }

    cout << ans << endl;
    return 0;
}