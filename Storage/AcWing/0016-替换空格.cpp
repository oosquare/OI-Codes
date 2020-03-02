class Solution {
  public:
    string replaceSpaces(string &str) {
        stringstream ss;
        for (int i = 0; i < str.size(); i++) {
            if (str[i] == ' ') {
                ss << "%20";
            } else {
                ss << str[i];
            }
        }
        return ss.str();
    }
};