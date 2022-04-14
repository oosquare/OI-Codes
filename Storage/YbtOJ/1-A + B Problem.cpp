#include <bits/stdc++.h>

struct node {
    int x, y;
    inline bool operator<(const node &rhs) { return y < rhs.y; }
};

int main() {
    int a, b;
    std::cin >> a >> b;
    std::cout << a + b << std::endl;
    return 0;
}
