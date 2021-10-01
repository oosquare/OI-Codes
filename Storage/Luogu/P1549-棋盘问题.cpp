#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 10 + 2;

int n;
int arr[maxn][maxn], selected[maxn * maxn];
int prime[maxn * maxn * 2], notprime[maxn * maxn * 2], tot;

void preprocess(int n) {
    for (int i = 2; i <= n; ++i) {
        if (notprime[i] == false)
            prime[++tot] = i;
        for (int j = 1; j <= tot; ++j) {
            if (i * prime[j] > n)
                break;
            notprime[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
        }
    }
}

bool invaild(int x, int y, int v) {
    if (x == 1 && y == 1)
        return v != 1;
    if (x != 1 && notprime[arr[x - 1][y] + v] == true)
        return true;
    if (y != 1 && notprime[arr[x][y - 1] + v] == true)
        return true;
    return false;
}

bool dfs(int x, int y) {
    if (x == n + 1 && y == 1) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j)
                cout << arr[i][j] << " ";
            cout << endl;
        }
        return true;
    }
    int start = (x == 1 || y == 1 ? 1 : n * n);
    int delta = (x == 1 || y == 1 ? 1 : -1);
    for (int i = start; 1 <= i && i <= n * n; i += delta) {
        if (selected[i] || invaild(x, y, i))
            continue;
        arr[x][y] = i;
        selected[i] = true;
        bool res = false;
        if (y == n)
            res = dfs(x + 1, 1);
        else
            res = dfs(x, y + 1);
        arr[x][y] = 0;
        selected[i] = false;
        if (res == true)
            return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    if (n == 1) {
        cout << "NO" << endl;
        return 0;
    }
    preprocess(2 * n * n);
    if (dfs(1, 1) == false)
        cout << "NO" << endl;
    return 0;
}