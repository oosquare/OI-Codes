#include <bits/stdc++.h>
using namespace std;

template <typename T, int maxsize, T mod>
class Hashset {
public:
	void insert(T x) {
		int h = (x % mod + mod) % mod;
		for (int i = head[h]; i; i = hset[i].next) {
			if (hset[i].val == x) {
				return;
			}
		}
		++total;
		hset[total].next = head[h];
		head[h] = total;
		hset[total].val = x;
	}

	bool query(T x) {
		int h = (x % mod + mod) % mod;
		for (int i = head[h]; i; i = hset[i].next) {
			if (hset[i].val == x) {
				return true;
			}
		}
		return false;
	}

	int size() {
		return total;
	}
private:
	struct Node {
		T val;
		int next;
	};
	Node hset[maxsize];
	int head[maxsize];
	int top;
	int total;
};

Hashset<unsigned, 500000, 491299> hashset;
string s;
int n;

unsigned h(const string &s) {
	int cnt[26] = {0};
	for (char c : s)
		++cnt[(int)(c - 'A')];
	unsigned hashv = 0;
	for (int i = 0; i < 26; ++i)
		hashv = (1LL * hashv * 100 + cnt[i]) % 9989729;
	return hashv;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("project.in", "r", stdin);
	freopen("project.out", "w", stdout);
#else
	freopen("word.in", "r", stdin);
	freopen("word.out", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> s;
		hashset.insert(h(s));
	}
	cout << hashset.size() << endl;
	return 0;
}
