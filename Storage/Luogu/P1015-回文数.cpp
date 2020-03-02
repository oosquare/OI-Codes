#include <cstring>
#include <iostream>
using namespace std;
int n;
int a[500], b[500], step = 0;
char str[500];

void add(int a[], int b[]) {
    int i;
    for (i = 1; i <= a[0]; i++) {
        a[i] += b[i];
        a[i + 1] += a[i] / n;
        a[i] %= n;
    }
    if (a[a[0] + 1] > 0)
        a[0] += 1;
}

bool is(int a[]) {
    int i;
    for (i = 1; i <= a[0] / 2; i++)
        if (a[i] != a[a[0] - i + 1])
            return false;
    return true;
}

void hui(int a[]) {
    int i, j;
    b[0] = a[0];
    j = 1;
    for (i = a[0]; i >= 1; i--) {
        b[j] = a[i];
        j++;
    }
}

int main() {
    cin >> n >> str;
    int len = strlen(str);

    int k = 1;
    for (int i = len - 1; i >= 0; i--) {
        if ('0' <= str[i] && str[i] <= '9') {
            a[k] = str[i] - '0';
            k++;
        } else if ('a' <= str[i] && str[i] <= 'z') {
            a[k] = str[i] - 'a' + 10;
            k++;
        } else if ('A' <= str[i] && str[i] <= 'Z') {
            a[k] = str[i] - 'A' + 10;
            k++;
        }
    }

    a[0] = len;
    while (is(a) == 0) {
        hui(a);
        add(a, b);
        step++;
        if (step > 30)
            break;
    }

    if (step > 30)
        cout << "Impossible!" << endl;
    else
        cout << "STEP=" << step << endl;
    return 0;
}