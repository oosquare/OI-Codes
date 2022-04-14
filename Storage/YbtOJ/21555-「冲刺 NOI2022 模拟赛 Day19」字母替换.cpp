#include <iostream>
#include <cstring>

constexpr int MAX_N = 100000 + 10;

int n, m;
char s[MAX_N], t[MAX_N], tmps[MAX_N], tmpt[MAX_N];
int p[MAX_N];
int fa[MAX_N], cnt[MAX_N];
int ans[MAX_N];

void update(int val) {
    p[1] = 0;

    for (int i = 2, j = 0; i <= m; ++i) {
        while (j && tmpt[j + 1] != tmpt[i])
            j = p[j];

        if (tmpt[j + 1] == tmpt[i])
            ++j;

        p[i] = j;
    }

    for (int i = 1, j = 0; i <= n; ++i) {
        while (j && tmpt[j + 1] != tmps[i])
            j = p[j];

        if (tmpt[j + 1] == tmps[i])
            ++j;

        if (j == m) {
            ans[i] = std::min(ans[i], val);
            j = p[j];
        }
    }
}

void check() {
    for (int i = 0; i < 6; ++i)
        cnt[i] = 0;
    
    for (int i = 0; i < 6; ++i)
        if (fa[i] != i)
            ++cnt[fa[i]];

    int val = 0;

    for (int i = 0; i < 6; ++i) {
        if (fa[i] != i && cnt[i] != 0)
            return;

        val += cnt[i];
    }

    for (int i = 1; i <= n; ++i)
        tmps[i] = 'a' + (char) fa[s[i] - 'a'];

    for (int i = 1; i <= m; ++i)
        tmpt[i] = 'a' + (char) fa[t[i] - 'a'];

    update(val);
}

void dfs(int dep) {
    if (dep == 6) {
        check();
        return;
    }

    for (int i = dep; i < 6; ++i) {
        fa[dep] = i;
        dfs(dep + 1);
    }
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("Antetokounmpo.in", "r", stdin);
    std::freopen("Antetokounmpo.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    std::cin >> (s + 1);
    std::cin >> (t + 1);
    n = (int) std::strlen(s + 1);
    m = (int) std::strlen(t + 1);

    for (int i = 1; i <= n; ++i)
        ans[i] = 0x3f3f3f3f;
    
    dfs(0);

    for (int i = m; i <= n; ++i)
        std::cout << ans[i] << " ";

    return 0;
}
