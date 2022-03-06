#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int MAX_N = 5e3 + 10;

int d, n[3], ord[4] = { 0, 1, 2, 0 }, pos[3];
bool exist[MAX_N];
int sta[MAX_N][MAX_N];
vector<pair<int, int>> graph[MAX_N];
bool vis[MAX_N];
int match[MAX_N];
int ans = 0x3f3f3f3f;

inline void link(int x, int y, int state) {
    graph[x].push_back({ y, state });
}

bool augment(int x, int state) {
    for (auto [y, s] : graph[x]) {
        // cout << s << " " << state << "----\n";
        if ((s | state) == state || vis[y])
            continue;

        vis[y] = true;

        if (!match[y] || augment(match[y], state)) {
            match[y] = x;
            return true;
        }
    }

    return false;
}

int hungary(int state) {
    int res = 0;

    for (int i = 1; i <= n[2]; ++i)
        match[i] = 0;

    for (int i = 1; i <= n[1]; ++i) {
        for (int j = 1; j <= n[2]; ++j)
            vis[j] = false;

        res += augment(i, state);
    }

    return res;
}

void check(int state, int count) {
    int res = count + hungary(state);
    ans = min(ans, res);
}

void dfs(int dep, int state, int count) {
    if (dep == n[0] + 1) {
        check(state, count);
        return;
    }

    dfs(dep + 1, state, count);

    if (exist[dep])
        dfs(dep + 1, (state | (1 << (dep - 1))), count + 1);
}

void reorder(int pos[]) {
    int tmp[3] = { pos[0], pos[1], pos[2] };

    for (int i = 0; i < 3; ++i)
        pos[i] = tmp[ord[i]];
}

void solve() {
    cin >> n[0] >> n[1] >> n[2];

    for (int i = 0; i < 3; ++i)
        ord[i] = i;

    sort(ord, ord + 3, [](int l, int r) {
        return n[l] < n[r];
    });


    for (int i = 1; i <= n[0]; ++i) {
        for (int j = 1; j <= n[1]; ++j) {
            for (int k = 1; k <= n[2]; ++k) {
                int x;
                cin >> x;

                if (x) {
                    pos[0] = i;
                    pos[1] = j;
                    pos[2] = k;
                    reorder(pos);
                    exist[pos[0]] = true;
                    sta[pos[1]][pos[2]] |= (1 << (pos[0] - 1));
                }
            }
        }
    }

    reorder(n);

    for (int i = 1; i <= n[1]; ++i)
        for (int j = 1; j <= n[2]; ++j)
            if (sta[i][j])
                link(i, j, sta[i][j]);

    ans = 0x3f3f3f3f;
    dfs(1, 0, 0);
    cout << ans << endl;

    for (int i = 1; i <= n[1]; ++i) {
        for (int j = 1; j <= n[2]; ++j)
            sta[i][j] = 0;

        graph[i].clear();
    }

    for (int i = 1; i <= n[0]; ++i)
        exist[i] = false;
}

int main() {
    ios::sync_with_stdio(false);

    cin >> d;

    while (d--)
        solve();

    return 0;
}