#include <iostream>
#include <vector>
#include <algorithm>

constexpr int MAX_N = 1e4 + 10;

int n, d[MAX_N];
std::vector<int> graph[MAX_N];
bool vis[MAX_N], fixed[MAX_N];
int match[MAX_N], ans[MAX_N];

inline void link(int x, int y) {
    graph[x].push_back(y);
}

bool augment(int x) {
    for (int y : graph[x]) {
        if (vis[y])
            continue;
        
        vis[y] = true;

        if (match[y] == -1 || augment(match[y])) {
            match[y] = x;
            return true;
        }
    }

    return false;
}

bool exchange(int x) {
    if (fixed[x])
        return false;
    
    for (int y : graph[x]) {
        if (vis[y])
            continue;
        
        vis[y] = true;

        if (match[y] == -1 || exchange(match[y])) {
            match[y] = x;
            return true;
        }
    }

    return false;
}

bool hungary() {
    int res = 0;

    for (int i = 0; i < n; ++i)
        match[i] = -1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            vis[j] = false;
        
        if (augment(i))
            ++res;
    }

    if (res != n)
        return false;
    
    for (int i = 0; i < n; ++i) {
        int other = -1;

        for (int j = 0; j < n; ++j) {
            vis[j] = false;
            
            if (match[j] == i)
                other = j;
        }

        match[other] = -1;

        if (!exchange(i))
            match[other] = i;
        
        fixed[i] = true;
    }

    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::cin >> d[i];
        
        if (d[i] > n - d[i])
            continue;
        
        if (i - d[i] >= 0)
            link(i, i - d[i]);
        
        if (i + d[i] < n)
            link(i, i + d[i]);
        
        if (i - (n - d[i]) >= 0)
            link(i, i - (n - d[i]));
        
        if (i + (n - d[i]) < n)
            link(i, i + (n - d[i]));
    }

    if (hungary()) {
        for (int i = 0; i < n; ++i)
            ans[match[i]] = i;
        
        for (int i = 0; i < n; ++i)
            std::cout << ans[i] << " ";
        
        std::cout << std::endl;
    } else {
        std::cout << "No Answer" << std::endl;
    }

    return 0;
}