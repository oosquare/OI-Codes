#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

constexpr int maxn = 2000 + 10;
constexpr ull seed = 29;

int n;
char str[maxn * 10];
ull power[maxn], val[maxn];
ll cnt[maxn][2];

void preprocess() {
	for (int i = 1; i <= n; ++i)
		val[i] = val[i - 1] * seed + str[i] - '0';
}

ull gethash(int l, int r) {
	return val[r] - val[l - 1] * power[r - l + 1];
}

void calc() {
	memset(cnt, 0, sizeof(cnt));
	for (int i = 1; i <= n; ++i) {
		for (int l = 1; l <= n; ++l) {
			if (i - 2 * l + 1 < 1)
				continue;
			if (gethash(i - 2 * l + 1, i - l) == gethash(i - l + 1, i))
				++cnt[i][0];
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int l = 1; l <= n; ++l) {
			if (i + 2 * l - 1 > n)
				continue;
			if (gethash(i, i + l - 1) == gethash(i + l, i + 2 * l - 1))
				++cnt[i][1];
		}
	}
}

void solve() {
	cin >> (str + 1);
	n = strlen(str + 1);
	preprocess();
	calc();
	ll ans = 0;
	for (int i = 1; i < n; ++i) {
		ans += cnt[i][0] * cnt[i + 1][1];
	}
	cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("project.in", "r", stdin);
	freopen("project.out", "w", stdout);
#else
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	power[0] = 1;
	for (int i = 1; i <= 2000; ++i)
		power[i] = power[i - 1] * seed;
	int t;
	cin >> t;
	while (t--)
		solve();
	
}
