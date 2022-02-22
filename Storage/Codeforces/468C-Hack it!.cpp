#include <iostream>
using namespace std;

long long a, l, r;
constexpr long long INFINITY = 1e18; 

int main() {
    ios::sync_with_stdio(false);
    cin >> a;
    l = a - INFINITY % a * 9 % a * 9 % a;
    r = INFINITY + l - 1;
    cout << l << " " << r << endl;
    return 0;
}