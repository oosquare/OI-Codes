#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int MAXN = 500 + 10;
constexpr int MAXM = 125000 + 10;

struct Equation {
    double a[MAXN];

    double &operator[](int x) {
        return a[x];
    }
};

struct EquationGroup {
    Equation e[MAXN];  
    int n;

    void init(int n) {
        this->n = n;
    }

    Equation &operator[](int x) {
        return e[x];
    }

    void transform() {
        for (int i = 1; i <= n; ++i) {
            int p = i;
            
            for (int j = i + 1; j <= n; ++j)
                if (abs(e[p][i]) < abs(e[j][i]))
                    p = j;
            
            if (p != i)
                for (int j = 1; j <= n + 1; ++j)
                    swap(e[i][j], e[p][j]);
            
            for (int j = i + 1; j <= n; ++j) {
                double rate = e[j][i] / e[i][i];

                for (int k = 1; k <= n + 1; ++k)
                    e[j][k] -= e[i][k] * rate;
            }
        }
    }

    void calc() {
        for (int i = n; i >= 1; --i) {
            for (int j = i + 1; j <= n; ++j)
                e[i][n + 1] -= e[i][j] * e[j][n + 1];
            
            e[i][n + 1] /= e[i][i];
        }
    }

    vector<double> solve() {
        transform();
        calc();
        vector<double> res(n + 1);

        for (int i = 1; i <= n; ++i)
            res[i] = e[i][n + 1];
        
        return res;
    }
};

struct Edge {
    int x, y;
    double p;

    bool operator<(const Edge &rhs) const {
        return p > rhs.p;
    }
};

int n, m;
EquationGroup e;
vector<int> graph[MAXN];
int deg[MAXN];
Edge edges[MAXM];
double ans;

void link(int x, int y) {
    graph[x].push_back(y);
    graph[y].push_back(x);
    ++deg[x];
    ++deg[y];
}

int main() {
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(3);
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        auto &[x, y, p] = edges[i];
        cin >> x >> y;
        link(x, y);
    }

    e.init(n - 1);

    for (int i = 1; i < n; ++i) {
        for (int j : graph[i])
            if (j != n)
                e[i][j] = -1.0 / deg[j];
        
        e[i][i] = 1;
    }

    e[1][n] = 1;

    auto f = e.solve();

    for (int i = 1; i <= m; ++i) {
        auto &[x, y, p] = edges[i];
        p = (x != n ? f[x] / deg[x] : 0) + (y != n ? f[y] / deg[y] : 0);
    }

    sort(edges + 1, edges + 1 + m);

    for (int i = 1; i <= m; ++i)
        ans += i * edges[i].p;

    cout << ans << endl;
    return 0;
}