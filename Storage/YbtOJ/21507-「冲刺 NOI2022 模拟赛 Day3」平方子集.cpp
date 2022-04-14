#include <iostream>
#include <random>
using namespace std;

constexpr int MAX_N = 1e6 + 10;

template <typename T, int size, T mod>
class HashMap {
public:
    void insert(T x, T y) {
        int h = x % mod;
        ++total;
        nodes[total].next = head[h];
        head[h] = total;
        nodes[total].key = x;
        nodes[total].value = y;
    }

    int query(T x) {
        int h = x % mod;
        for (int i = head[h]; i; i = nodes[i].next) {
            if (nodes[i].key == x) {
                return nodes[i].value;
            }
        }
        return 0;
    }
private:
    struct Node {
        T key, value;
        int next;
    };
    Node nodes[size];
    int head[size];
    int total;
};

int n;
int prime[MAX_N], pt;
bool notPrime[MAX_N];
long long f[MAX_N], p;
HashMap<long long, MAX_N * 50, 19260817> mp;

void sieve(int n) {
    mt19937 gen((random_device())());
    uniform_int_distribution<long long> dist(0x3f3f3f3f, 0x3f3f3f3f3f3f3f3f);

    notPrime[1] = true;
    f[1] = 0;

    for (int i = 2; i <= n; ++i) {
        if (!notPrime[i]) {
            prime[++pt] = i;
            f[i] = dist(gen);
        }

        for (int j = 1; j <= pt && i * prime[j] <= n; ++j) {
            notPrime[i * prime[j]] = true;
            f[i * prime[j]] = (f[i] ^ f[prime[j]]);

            if (i % prime[j] == 0)
                break;
        }
    }

    for (int i = 2; i <= n; ++i)
        f[i] ^= f[i - 1];
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("square.in", "r", stdin);
    freopen("square.out", "w", stdout);
#else
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);

    cin >> n;
    sieve(n);

    for (int i = 1; i <= n; ++i)
        p ^= f[i];

    if (p == 0) {
        cout << n << endl;

        for (int i = 1; i <= n; ++i)
            cout << i << " ";

        return 0;
    }

    for (int i = 1; i <= n; ++i) {
        if (p ^ f[i])
            continue;

        cout << n - 1 << endl;

        for (int j = 1; j <= n; ++j) {
            if (j == i)
                continue;

            cout << j << " ";
        }

        return 0;
    }

    if (n % 4 == 0) {
        cout << n - 1 << endl;

        for (int i = 1; i <= n; ++i) {
            if (i == n / 2)
                continue;
            
            cout << i << " ";
        }

        return 0;
    }

    for (int i = 1; i <= n; ++i)
        mp.insert(f[i], i);
    
    for (int i = 1; i <= n; ++i) {
        int t = mp.query(p ^ f[i]);

        if (!t)
            continue;

        cout << n - 2 << endl;

        for (int j = 1; j <= n; ++j) {
            if (j == i || j == t)
                continue;
            
            cout << j << " ";
        }

        return 0;
    }

    if (n % 4 == 2) {
        cout << n - 2 << endl;

        for (int i = 1; i <= n; ++i) {
            if (i == 2 || i == n / 2)
                continue;
            
            cout << i << " ";
        }

        return 0;
    }

    --n;

    if (n % 4 == 0) {
        cout << n - 1 << endl;

        for (int i = 1; i <= n; ++i) {
            if (i == n / 2)
                continue;
            
            cout << i << " ";
        }

        return 0;
    }

    if (n % 4 == 2) {
        cout << n - 2 << endl;

        for (int i = 1; i <= n; ++i) {
            if (i == 2 || i == n / 2)
                continue;
            
            cout << i << " ";
        }

        return 0;
    }
    
    return 0;
}
