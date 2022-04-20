#include <cstddef>
#include <iostream>
#include <vector>
#include <cstring>

constexpr int MAX_N = 200000 + 10;
constexpr int MOD = 998244353;

template <int MOD>
class ModInteger {
public:
    using Self = ModInteger<MOD>;

    struct Hash {
        unsigned long long operator()(const Self &v) const { return v.hash(); }
    };

    ModInteger(const int val = 0) : val(val) {}
    ModInteger(const Self &) = default;
    ModInteger(Self &&) = default;
    ~ModInteger() = default;

    operator bool() const { return val != 0; }
    operator int() const { return val; }

    bool operator<(const Self &rhs) const { return val < rhs.val; }
    bool operator>(const Self &rhs) const { return val > rhs.val; }
    bool operator<=(const Self &rhs) const { return val <= rhs.val; }
    bool operator>=(const Self &rhs) const { return val >= rhs.val; }
    bool operator==(const Self &rhs) const { return val == rhs.val; }
    bool operator!=(const Self &rhs) const { return val != rhs.val; }

    Self &operator=(const Self &) = default;
    Self &operator=(Self &&) = default;

    Self operator+(const Self &rhs) const {
        int tmp = val + rhs.val;
        return Self(tmp >= MOD ? tmp - MOD : tmp);
    }

    Self operator-(const Self &rhs) const {
        int tmp = val - rhs.val;
        return Self(tmp < 0 ? tmp + MOD : tmp);
    }

    Self operator*(const Self &rhs) const { return Self(1ll * val * rhs.val % MOD); }
    Self operator/(const Self &rhs) const { return *this * rhs.power(Self(MOD - 2)); }
    Self operator%(const Self &rhs) const { return Self(val % rhs.val); }

    Self operator+() const { return *this; }
    Self operator-() const { return Self(MOD - val); }

    Self &operator+=(const Self &rhs) { return (*this = *this + rhs); }
    Self &operator-=(const Self &rhs) { return (*this = *this - rhs); }
    Self &operator*=(const Self &rhs) { return (*this = *this * rhs); }
    Self &operator/=(const Self &rhs) { return (*this = *this / rhs); }
    Self &operator%=(const Self &rhs) { return (*this = *this % rhs); }
    Self &operator&=(const Self &rhs) { return (*this = *this & rhs); }
    Self &operator|=(const Self &rhs) { return (*this = *this | rhs); }
    Self &operator^=(const Self &rhs) { return (*this = *this ^ rhs); }
    Self &operator<<=(const Self &rhs) { return (*this = *this << rhs); }
    Self &operator>>=(const Self &rhs) { return (*this = *this >> rhs); }

    friend std::istream &operator>>(std::istream &is, Self &v) { return (is >> v.val); }
    friend std::ostream &operator<<(std::ostream &os, const Self &v) { return (os << v.val); }

    void set(const int val) {
        this->val = val;
        adjust();
    }

    const int &get() const { return val; }
    int &get() { return val; }

    Self power(Self y) const {
        Self res(1), x(*this);

        for (; y.val; y.val /= 2) {
            if (y.val % 2 == 1)
                res = res * x;

            x = x * x;
        }

        return res;
    }

    Self inverse() const { return Self(1) / *this; }

    std::string toString() const { return std::to_string(val); }

    unsigned long long hash() const { return std::hash<int>()(val); }

    void adjustForAdd() {
        if (val >= MOD)
            val -= MOD;
    }

    void adjustForSub() {
        if (val < MOD)
            val += MOD;
    }

    void adjust() {
        val = val % MOD;
        adjustForSub();
    }

private:
    int val;
};

using mint = ModInteger<MOD>;

int n;
int p[MAX_N], q[MAX_N];
mint f[MAX_N][2], cnt[MAX_N];
std::vector<int> graph[MAX_N];
bool vis[MAX_N];
mint ans;

void link(int x, int y) { graph[x].push_back(y); }

int dfs(int x) {
    if (vis[x])
        return 0;

    vis[x] = true;
    return dfs(graph[x].front()) + 1;
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("A.in", "r", stdin);
    std::freopen("A.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);

    std::cin >> n;

    for (int i = 1; i <= n; ++i)
        std::cin >> p[i];

    for (int i = 1; i <= n; ++i) {
        std::cin >> q[i];
        link(p[i], q[i]);
    }

    f[1][0] = 1;

    for (int i = 2; i <= n; ++i) {
        f[i][0] += f[i - 1][1];
        f[i][1] += f[i - 1][0] + f[i - 1][1];
    }

    for (int i = 1; i <= n; ++i)
        cnt[i] += f[i][1];

    std::memset(f, 0, sizeof(f));

    f[1][1] = 1;

    for (int i = 1; i <= n; ++i) {
        f[i][0] += f[i - 1][1];
        f[i][1] += f[i - 1][0] + f[i - 1][1];
    }

    for (int i = 1; i <= n; ++i)
        cnt[i] += f[i][0] + f[i][1];

    ans = 1;

    for (int i = 1; i <= n; ++i)
        if (!vis[i])
            ans *= cnt[dfs(i)];

    std::cout << ans << std::endl;
    return 0;
}
