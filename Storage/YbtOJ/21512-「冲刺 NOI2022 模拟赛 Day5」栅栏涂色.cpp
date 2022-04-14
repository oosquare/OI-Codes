#include <iostream>

constexpr int MAX_N = 1e5 + 10;
constexpr int MAX_M = 5e3 + 10;

int n, m;
int a[MAX_N];
int left[MAX_N], right[MAX_N], pos[MAX_N];
int seq[MAX_N], tot;
int f[MAX_M][MAX_M], ans;

void add(int p) {
    int x = p;
    tot = 0;

    while (pos[x]) {
        int t = pos[x];
        pos[x] = 0;
        seq[++tot] = right[t] - left[t] + 1;
        x = right[t] + 1;
    }
}

int dp() {
    for (int i = 1; i <= tot; ++i)
        seq[i] += seq[i - 1];
    
    for (int l = 1; l <= tot; ++l)
        for (int i = 1, j = l; j <= tot; ++i, ++j)
            f[i][j] = std::max(f[i + 1][j], f[i][j - 1]) + seq[j] - seq[i - 1];
    
    return f[1][tot];
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
#else
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];
    
    for (int i = n; i >= 1; --i)
        left[a[i]] = i;
    
    for (int i = 1; i <= n; ++i)
        right[a[i]] = i;
    
    for (int i = 1; i <= n; ++i)
        pos[left[i]] = i;
    
    for (int i = 1; i <= n; ++i) {
        if (!pos[i])
            continue;
        
        add(i);
        ans += dp();
    }

    std::cout << ans << std::endl;
    return 0;
}
