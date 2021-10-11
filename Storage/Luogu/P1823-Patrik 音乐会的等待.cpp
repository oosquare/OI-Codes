#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e5 + 10;

int n, a[maxn];
int st[maxn], top;
long long ans;

int find(int x) {
    int l = 1, r = top, res = 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (a[st[mid]] > a[x]) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return res;
}

void print() {
    printf("stack (top = %d) : ", top);
    for (int i = 1; i <= top; ++i)
        printf("(%d, %d) ", st[i], a[st[i]]);
    printf("\n");    
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    st[top = 1] = 1;
    // print();
    for (int i = 2; i <= n; ++i) {
        int pos = find(i);
        // cout << i << " " << pos << endl;
        ans += top - pos + 1;
        while (top > 0 && a[st[top]] < a[i])
            --top;
        st[++top] = i;
        // print();
    }
    cout << ans << endl;
    return 0;
}