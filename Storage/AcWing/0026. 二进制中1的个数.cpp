class Solution {
public:
    int NumberOf1(int n) {
        int ans = 0;
        for (int i = 1; i <= 32; ++i) {
            if (n & 1)
                ++ans;
            n >>= 1;
        }
        return ans;
    }
};