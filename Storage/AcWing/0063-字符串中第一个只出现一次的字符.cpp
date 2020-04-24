class Solution {
public:
    int q[300], u[300], cnt;
    char r[300];
    
    int cast(char c) {
        return static_cast<int>(c);
    }
    
    char firstNotRepeatingChar(string s) {
        for (char c : s) {
            if (u[cast(c)] == 0) {
                u[cast(c)] = ++cnt;
                r[cnt] = c;
            }
            ++q[u[cast(c)]];
        }
        for (int i = 1; i <= cnt; ++i) {
            if (q[i] == 1)
                return r[i];
        }
        return '#';
    }
};