#include <iostream>
#include <cstring>
using namespace std;

int n, len;
char k[100];
long long weight = 1, power[30], ans;

int main() {
    ios::sync_with_stdio(false);
    power[0] = 1;
    
    for (int i = 1; i <= 29; ++i)
        power[i] = power[i - 1] * 10;

    cin >> n >> (k + 1);
    len = strlen(k + 1);
    
    for (int i = len; i >= 1; weight *= n) {
        int j = 0;
        long long sum = 0;

        while (i - j > 0 && sum + (k[i - j] - '0') * power[j] < n) {
            if (power[j] > n)
                break;

            sum += (k[i - j] - '0') * power[j];
            ++j;
        }

        while (k[i - j + 1] == '0' && j > 1)
            --j;

        ans += sum * weight;
        i = i - j;
    }

    cout << ans << endl;
    return 0;
}