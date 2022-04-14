#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

int solve() {
    int n, sum = 0;
    cin >> n;

    for  (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        sum += (x == 1);
    }

    return sum % 2;
}
int main() {
    freopen("chess.in", "r", stdin);
    freopen("chess.out", "w", stdout);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;

    while (t--) {
        if (solve())
            cout << "rabbit" << endl;
        else
            cout << "hamster" << endl;
    }
    
    return 0;
}
