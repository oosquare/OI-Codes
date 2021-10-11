#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int mod = 998244353;

struct Function {
    int type, p, v;
    vector<int> c;
};

int n, m, q, b, a[maxn], k[maxn], id[maxn];
int mul[maxn], f[maxn], in[maxn], pre[maxn];
Function func[maxn];

void toposort() {
    queue<int> q;
    for (int i = 1; i <= m; ++i)
        if (in[i] == 0)
            q.push(i);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (func[x].type == 1) {
            k[func[x].p] = (k[func[x].p] + 1LL * func[x].v * f[x]) % mod;
        } else if (func[x].type == 3) {
            for (int i = func[x].c.size() - 1; i >= 0; --i) {
                int y = func[x].c[i];
                f[y] = (f[x] + f[y]) % mod;
                f[x] = 1LL * f[x] * mul[y] % mod;
                --in[y];
                if (in[y] == 0)
                    q.push(y);
            }
        }
    }
}

void dfs(int x) {
    if (mul[x] != -1)
        return;
    if (func[x].type == 1) {
        mul[x] = 1;
        return;
    } else if (func[x].type == 2) {
        mul[x] = func[x].v;
        return;
    } else {
        mul[x] = 1;
        for (int y : func[x].c) {
            dfs(y);
            mul[x] = 1LL * mul[x] * mul[y] % mod;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> func[i].type;
        if (func[i].type == 1) {
            cin >> func[i].p >> func[i].v;
            func[i].v %= mod;
        } else if (func[i].type == 2) {
            cin >> func[i].v;
            func[i].v %= mod;
        } else {
            int c, x;
            cin >> c;
            for (int j = 1; j <= c; ++j) {
                cin >> x;
                func[i].c.push_back(x);
                ++in[x];
            }
        }
    }
    memset(mul, -1, sizeof(mul));
    for (int i = 1; i <= m; ++i)
        if (mul[i] == -1)
            dfs(i);
    cin >> q;
    for (int i = 1; i <= q; ++i)
        cin >> id[i];
    b = 1;
    for (int i = q; i >= 1; --i) {
        if (func[id[i]].type == 1) {
            f[id[i]] = (f[id[i]] + b) % mod;
        } else if (func[id[i]].type == 2) {
            b = 1LL * b * func[id[i]].v % mod;
        } else {
            f[id[i]] = (f[id[i]] + b) % mod;
            b = 1LL * b * mul[id[i]] % mod;
        }
    }
    toposort();
    for (int i = 1; i <= n; ++i) {
        cout << (1LL * a[i] * b + k[i]) % mod << " ";
    }
    return 0;
}