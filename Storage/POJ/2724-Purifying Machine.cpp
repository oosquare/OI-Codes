#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 10;
const int MAX_NODE = (1 << MAX_N);

int n, m;
vector<int> tmp[MAX_NODE], graph[MAX_NODE];
int match[MAX_NODE];
bool infected[MAX_NODE], exist[MAX_NODE], vis[MAX_NODE], col[MAX_NODE];
int infectedTot, graphTot;
char str[MAX_N + 1];

void link(vector<int> graph[], int x, int y) {
    graph[x].push_back(y);
}

bool augment(int x) {
    for (int i = 0; i < (int) graph[x].size(); ++i) {
        int y = graph[x][i];

        if (vis[y])
            continue;

        vis[y] = true;

        if (match[y] == -1 || augment(match[y])) {
            match[y] = x;
            return true;
        }
    }

    return false;
}

int hungary() {
    int res = 0;

    for (int i = 0; i < (1 << n); ++i)
        match[i] = -1;

    for (int i = 0; i < (1 << n); ++i) {
        if (!exist[i] || col[i])
            continue;

        for (int j = 0; j < (1 << n); ++j)
            vis[j] = false;

        if (augment(i))
            ++res;
    }

    return res;
}

void coloring(int x, bool now) {
    if (vis[x])
        return;

    col[x] = now;
    vis[x] = true;

    for (int i = 0; i < (int) tmp[x].size(); ++i) {
        int y = tmp[x][i];

        if (!now)
            link(graph, x, y);

        coloring(y, !now);
    }
}

int convert(char str[], int len) {
    int res = 0;

    for (int i = len - 1; i >= 0; --i)
        res = (res << 1) + (str[i] - '0');

    return res;
}

void clear() {
    infectedTot = graphTot = 0;

    for (int i = 0; i < (1 << n); ++i) {
        vis[i] = infected[i] = exist[i] = col[i] = false;
        tmp[i].clear();
        graph[i].clear();
    }
}

void input() {
    cin >> n >> m;
    clear();

    for (int i = 1; i <= m; ++i) {
        cin >> str;

        for (int j = 0, k = n - 1; j < k; ++j, --k)
            swap(str[j], str[k]);

        int pos = -1;

        for (int j = 0; j < n; ++j) {
            if (str[j] == '*') {
                pos = j;
                break;
            }
        }

        if (pos == -1) {
            int id = convert(str, n);
            infected[id] = true;
        } else {
            str[pos] = '0';
            int id = convert(str, n);
            infected[id] = true;
            str[pos] = '1';
            id = convert(str, n);
            infected[id] = true;
            str[pos] = '*';
        }
    }
}

void build() {
    for (int i = 0; i < (1 << n); ++i)
        if (infected[i])
            ++infectedTot;

    for (int i = 0; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j) {
            int id1 = (i & (~(1 << j))), id2 = (i | (1 << j));

            if (infected[id1] && infected[id2]) {
                exist[id1] = exist[id2] = true;
                link(tmp, id1, id2);
                link(tmp, id2, id1);
            }
        }
    }

    for (int i = 0; i < (1 << n); ++i) {
        if (!exist[i])
            continue;

        ++graphTot;
        coloring(i, false);
    }
}

bool solve() {
    input();

    if (n == 0 && m == 0)
        return true;

    build();

    cout << ((infectedTot - graphTot) + (graphTot - hungary())) << endl;
    return false;
}

int main() {
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
    ios::sync_with_stdio(false);

    bool end = false;

    do
        end = solve();
    while (!end);

    return 0;
}