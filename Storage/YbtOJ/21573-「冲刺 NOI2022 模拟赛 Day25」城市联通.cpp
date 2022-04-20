#include <cstdio>
#include <vector>
#include <cmath>

constexpr int MAX_N = 50 + 5;
constexpr double EPS = 1e-8;

class Matrix {
public:
    void init(int n) {
        this->n = n;

        for (int i = 1; i <= n; ++i)
            mat[i].resize(n + 1);
    }

    std::vector<double> &operator[](int x) { return mat[x]; }

    double determinant() {
        double res = 1;
        --n;

        for (int i = 1; i <= n; ++i) {
            int p = -1;

            for (int j = i; j <= n; ++j) {
                if (mat[j][i] != 0) {
                    p = j;
                    break;
                }
            }

            if (p == -1)
                return 0;

            if (p != i) {
                res = -res;
                std::swap(mat[i], mat[p]);
            }

            res *= mat[i][i];

            for (int j = i + 1; j <= n; ++j) {
                if (mat[j][i] == 0)
                    continue;

                double r = mat[j][i] / mat[i][i];

                for (int k = i; k <= n; ++k)
                    mat[j][k] -= mat[i][k] * r;
            }
        }

        return res;
    }

private:
    int n;
    std::vector<double> mat[MAX_N];
};

int n;
Matrix mat;
double ans = 1;

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("city.in", "r", stdin);
    std::freopen("city.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::scanf("%d", &n);
    mat.init(n);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            double p;
            std::scanf("%lf", &p);

            if (p == 1)
                p -= EPS;

            if (i < j)
                ans *= 1 - p;

            mat[i][i] += p / (1 - p);
            mat[i][j] -= p / (1 - p);
        }
    }

    ans *= mat.determinant();
    std::printf("%.5lf", std::abs(ans));
    return 0;
}