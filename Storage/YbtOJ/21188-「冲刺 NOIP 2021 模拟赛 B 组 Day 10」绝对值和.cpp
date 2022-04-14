#include <iostream>
#include <iomanip>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

constexpr int maxn = 3e5 + 10;
constexpr double eps = 1e-6;

struct Function {
    int a, b;
    double x;

    bool operator<(const Function &rhs) const {
        return rhs.x - x > eps;
    }
};

int n;
Function func[maxn];
long long sa[2][maxn], sb[2][maxn];
double ans = 1e18;

int main() {
    freopen("spongebob.in", "r", stdin);
    freopen("spongebob.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> func[i].a >> func[i].b;

        if (func[i].a < 0) {
            func[i].a *= -1;
            func[i].b *= -1;
        }

        func[i].x = -1.0 * func[i].b / func[i].a;
    }

    sort(func + 1, func + 1 + n);

    for (int i = 1; i <= n; ++i) {
        sa[0][i] = sa[0][i - 1] + func[i].a;
        sb[0][i] = sb[0][i - 1] + func[i].b;
    }

    for (int i = n; i >= 1; --i) {
        sa[1][i] = sa[1][i + 1] - func[i].a;
        sb[1][i] = sb[1][i + 1] - func[i].b;
    }

    for (int i = 1; i <= n; ++i) {
        double x = func[i].x;
        double res = sa[0][i - 1] * x + sb[0][i - 1];
        res += sa[1][i + 1] * x + sb[1][i + 1];
        ans = min(ans, res);
    }

    cout << fixed << setprecision(6) << ans << endl;
    return 0;
}
