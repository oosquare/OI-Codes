#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

constexpr int MAX_M = 60 + 5;
constexpr int MAX_S = 20 + 5;

int n, m, sr, sg, sb, p;
vector<int> perm[MAX_M];
bool vis[MAX_M];
int f[2][MAX_S][MAX_S][MAX_S], ans;

void parse(const string & in, vector<int> & nums) {
    nums.push_back(0);
    istringstream iss(in);
    int tmp;

    while (iss >> tmp)
        nums.push_back(tmp);
}

int power(int x, int y) {
    int res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = 1ll * res * x % p;

        x = 1ll * x * x % p;
    }

    return res;
}

int dfs(int now, const vector<int> & perm) {
    if (vis[now])
        return 0;
    
    vis[now] = true;
    return dfs(perm[now], perm) + 1;
}

vector<int> findLoop(const vector<int> & perm) {
    vector<int> res = { 0 };

    for (int i = 1; i <= n; ++i)
        vis[i] = false;

    for (int i = 1; i <= n; ++i)
        if (!vis[i])
            res.push_back(dfs(i, perm));
    
    return res;
}

int dp(const vector<int> & loop) {
    int e = loop.size() - 1;
    int res = 0;

    for (int r = 0; r <= sr; ++r)
        for (int g = 0; g <= sg; ++g)
            for (int b = 0; b <= sb; ++b)
                f[0][r][g][b] = 0;
    
    f[0][0][0][0] = 1;

    for (int i = 1; i <= e; ++i) {
        int now = (i & 1), pre = (now ^ 1);

        for (int r = 0; r <= sr; ++r) {
            for (int g = 0; g <= sg; ++g) {
                for (int b = 0; b <= sb; ++b) {
                    int & val = f[now][r][g][b] = 0;

                    if (r - loop[i] >= 0)
                        val = (val + f[pre][r - loop[i]][g][b]) % p;
                    
                    if (g - loop[i] >= 0)
                        val = (val + f[pre][r][g - loop[i]][b]) % p;
                    
                    if (b - loop[i] >= 0)
                        val = (val + f[pre][r][g][b - loop[i]]) % p;
                    
                    if (i == e)
                        res = (res + val) % p;
                }
            }
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> sr >> sg >> sb >> m >> p;

    if (cin.peek() == '\n')
        cin.ignore();

    for (int i = 1; i <= m; ++i) {
        string in;
        getline(cin, in, '\n');
        parse(in, perm[i]);
    }

    n = perm[1].size() - 1;

    bool found = false;

    for (int i = 1; i <= m; ++i) {
        bool found2 = true;

        for (int j = 1; j <= n; ++j) {
            if (perm[i][j] != j) {
                found2 = false;
                break;
            }
        }

        if (found2) {
            found = true;
            break;
        }
    }

    if (!found) {
        ++m;

        for (int i = 0; i <= n; ++i)
            perm[m].push_back(i);
    }

    for (int i = 1; i <= m; ++i)
        ans = (ans + dp(findLoop(perm[i]))) % p;
    
    ans = 1ll * ans * power(m, p - 2) % p;
    cout << ans << endl;
    return 0;
}