#pragma GCC optimize(2)
#include <iostream>
#include <cstring>
#include <vector>

constexpr int MAX_N = 500 + 5;
constexpr int MOD = 998244353;

template <int MOD>
class ModInteger {
public:
    using Self = ModInteger<MOD>;

    struct Hash {
        unsigned long long operator()(const Self &v) const { return v.hash(); }
    };

    constexpr ModInteger(const int val = 0) : val(val) {}
    constexpr ModInteger(const Self &) = default;
    constexpr ModInteger(Self &&) = default;
    ~ModInteger() = default;

    constexpr operator bool() const { return val != 0; }
    constexpr operator int() const { return val; }

    constexpr bool operator<(const Self &rhs) const { return val < rhs.val; }
    constexpr bool operator>(const Self &rhs) const { return val > rhs.val; }
    constexpr bool operator<=(const Self &rhs) const { return val <= rhs.val; }
    constexpr bool operator>=(const Self &rhs) const { return val >= rhs.val; }
    constexpr bool operator==(const Self &rhs) const { return val == rhs.val; }
    constexpr bool operator!=(const Self &rhs) const { return val != rhs.val; }

    constexpr Self &operator=(const Self &) = default;
    constexpr Self &operator=(Self &&) = default;

    constexpr Self operator+(const Self &rhs) const {
        int tmp = val + rhs.val;
        return Self(tmp >= MOD ? tmp - MOD : tmp);
    }

    constexpr Self operator-(const Self &rhs) const {
        int tmp = val - rhs.val;
        return Self(tmp < 0 ? tmp + MOD : tmp);
    }

    constexpr Self operator*(const Self &rhs) const { return Self(1ll * val * rhs.val % MOD); }
    constexpr Self operator/(const Self &rhs) const { return *this * rhs.power(Self(MOD - 2)); }
    constexpr Self operator%(const Self &rhs) const { return Self(val % rhs.val); }

    constexpr Self operator+() const { return *this; }
    constexpr Self operator-() const { return Self(MOD - val); }

    constexpr Self &operator+=(const Self &rhs) { return (*this = *this + rhs); }
    constexpr Self &operator-=(const Self &rhs) { return (*this = *this - rhs); }
    constexpr Self &operator*=(const Self &rhs) { return (*this = *this * rhs); }
    constexpr Self &operator/=(const Self &rhs) { return (*this = *this / rhs); }
    constexpr Self &operator%=(const Self &rhs) { return (*this = *this % rhs); }
    constexpr Self &operator&=(const Self &rhs) { return (*this = *this & rhs); }
    constexpr Self &operator|=(const Self &rhs) { return (*this = *this | rhs); }
    constexpr Self &operator^=(const Self &rhs) { return (*this = *this ^ rhs); }
    constexpr Self &operator<<=(const Self &rhs) { return (*this = *this << rhs); }
    constexpr Self &operator>>=(const Self &rhs) { return (*this = *this >> rhs); }

    constexpr friend std::istream &operator>>(std::istream &is, Self &v) { return (is >> v.val); }
    constexpr friend std::ostream &operator<<(std::ostream &os, const Self &v) { return (os << v.val); }

    constexpr void set(const int val) {
        this->val = val;
        adjust();
    }

    constexpr const int &get() const { return val; }
    constexpr int &get() { return val; }

    constexpr Self power(Self y) const {
        Self res(1), x(*this);

        for (; y.val; y.val /= 2) {
            if (y.val % 2 == 1)
                res = res * x;

            x = x * x;
        }

        return res;
    }

    constexpr Self inverse() const { return Self(1) / *this; }

    std::string toString() const { return std::to_string(val); }

    constexpr unsigned long long hash() const { return std::hash<int>()(val); }

    constexpr void adjustForAdd() {
        if (val >= MOD)
            val -= MOD;
    }

    constexpr void adjustForSub() {
        if (val < MOD)
            val += MOD;
    }

    constexpr void adjust() {
        val = val % MOD;
        adjustForSub();
    }

private:
    int val;
};

namespace std {
    template <int MOD>
    struct hash<ModInteger<MOD>> {
        unsigned long long operator()(const ModInteger<MOD> &v) const { return v.hash(); }
    };
} // namespace std

class Matrix {
public:
    void init(int n) {
        this->n = n;

        for (int i = 1; i <= n; ++i)
            mat[i].resize(n + 1);
    }

    std::vector<ModInteger<MOD>> &operator[](int x) { return mat[x]; }

    ModInteger<MOD> determinant() {
        ModInteger<MOD> res = 1;

        for (int i = 1; i <= n; ++i) {
            int p = -1;

            for (int j = i; j <= n; ++j) {
                if (mat[j][i]) {
                    p = j;
                    break;
                }
            }

            if (p == -1)
                return 0;

            if (p != i)
                res = -res;

            std::swap(mat[i], mat[p]);
            res *= mat[i][i];
            auto inv = mat[i][i].inverse();

            for (int j = i + 1; j <= n; ++j) {
                if (!mat[j][i])
                    continue;

                auto r = mat[j][i] * inv;

                for (int k = i; k <= n; ++k)
                    mat[j][k] -= mat[i][k] * r;
            }
        }

        return res;
    }

private:
    int n;
    std::vector<ModInteger<MOD>> mat[MAX_N];
};

int n;
Matrix mat;
ModInteger<MOD> a[MAX_N * 2][MAX_N * 2], val[MAX_N * 2][MAX_N * 2];
/** f[i][j] 表示从当前行左边起第 i 列，从最底部起第 j 行的乘积和 */
ModInteger<MOD> f[MAX_N * 2][MAX_N * 2];
ModInteger<MOD> ans = 1;

inline ModInteger<MOD> calc(ModInteger<MOD> x, ModInteger<MOD> y) {
    return ModInteger<MOD>(x.get() ^ y.get()) / (x * y);
}

void preprocess() {
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= 2 * i; ++j)
            val[i][n - i + j] = calc(a[i][n - i + j], a[i - 1][n - i + j]);

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= 2 * (n - i + 1); ++j)
            val[n + i][i + j - 1] = calc(a[n + i][i + j - 1], a[n + i - 1][i + j - 1]);
}

void update(int r, int i, int j) {
    /** 向左边转移，若 a 为 0 则越界 */
    if (a[2 * n - j + 1][n - r + i + 1] && a[2 * n - j + 1][n - r + i + 2])
        f[i + 2][j] += f[i][j];

    /** 向上转移 */
    if (val[2 * n - j + 1][n - r + i + 1])
        f[i + 1][j + 1] += f[i][j] * val[2 * n - j + 1][n - r + i + 1];

    /** 向下转移 */
    if (j >= 2 && val[2 * n - j + 2][n - r + i + 1])
        f[i + 1][j - 1] += f[i][j] * val[2 * n - j + 2][n - r + i + 1];
}

void dp(int r) {
    /** r 为从下往上数 */
    f[0][r] = 1;

    for (int i = 0; i < r + n; ++i) {
        for (int j = 1; j <= r + i; ++j) {
            if (!f[i][j])
                continue;

            update(r, i, j);
        }
    }
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("magic.in", "r", stdin);
    std::freopen("magic.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);

    std::cin >> n;
    mat.init(n);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= 2 * i; ++j) {
            std::cin >> a[i][n - i + j];
            ans *= a[i][n - i + j];
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= 2 * (n - i + 1); ++j) {
            std::cin >> a[n + i][i + j - 1];
            ans *= a[n + i][i + j - 1];
        }
    }

    preprocess();

    for (int i = 1; i <= n; ++i) {
        std::memset(f, 0, sizeof(f));
        dp(i);

        for (int j = 1; j <= n; ++j)
            mat[i][j] = f[i + j][j];
    }

    ans *= mat.determinant();
    std::cout << ans << std::endl;
    return 0;
}
