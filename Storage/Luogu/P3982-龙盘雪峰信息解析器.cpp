#include <bits/stdc++.h>
using namespace std;

int getNumber(string s) {
    int res = 0;
    for (int i = 0; i < (int)s.size(); ++i)
        res = res * 2 + (int)(s[i] - '0');
    return res;
} 

string parse(string str) {
    if (str.size() % 8 != 0)
        return "Error";
    for (char c : str)
        if (c != '0' && c != '1')
            return "Error";

    string res;
    for (int i = 0; i + 7 < (int)str.size(); i += 8) {
        if (str.substr(i, 3) == "101") {
            int ch = getNumber(str.substr(i + 3, 5));
            if (ch >= 26)
                return "Error";
            res.push_back((char)(ch + 'A'));
        } else if (str.substr(i, 3) == "111") {
            res.push_back(' ');
        } else if (str[i] == '0') {
            int op1 = getNumber(str.substr(i, 8));
            if (i + 8 >= (int)str.size())
                return "Error";
            if (str[i + 8] != '0')
                return "Error";
            int op2 = getNumber(str.substr(i + 8, 8));
            res += to_string(op1 / 2 + op2 / 2);
            i += 8;
        } else {
            return "Error";
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    string s;
    cin >> s;
    cout << parse(s) << endl;
    return 0;
}