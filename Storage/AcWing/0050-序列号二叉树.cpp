/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
  public:
    void si(TreeNode *root, string &os) {
        if (root == nullptr) {
            os += "null ";
            return;
        }
        os = os + to_string(root->val) + " ";
        si(root->left, os);
        si(root->right, os);
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode *root) {
        string os;
        si(root, os);
        return os;
    }

    TreeNode *di(istringstream &is) {
        string s;
        is >> s;
        if (s == "null") {
            return nullptr;
        }
        TreeNode *nd = new TreeNode(atoi(s.c_str()));
        nd->left = di(is);
        nd->right = di(is);
        return nd;
    }
    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data) {
        TreeNode *rt = nullptr;
        istringstream is(data);
        rt = di(is);
        return rt;
    }
};