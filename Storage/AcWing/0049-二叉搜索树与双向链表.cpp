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
    vector<TreeNode*> l;
    
    void DFS(TreeNode* x) {
        if (!x)
            return;
        DFS(x->left);
        l.push_back(x);
        DFS(x->right);
    }
    
    TreeNode* convert(TreeNode* root) {
        DFS(root);
        for (TreeNode*& p : l)
            p->left = p->right = nullptr;
        if (l.size() == 0)
            return nullptr;
        if (l.size() == 1)
            return l[0];
        TreeNode* head = l[0], * now = head;
        now->right = l[1];
        now = l[1];
        for (int i = 1; i < l.size() - 1; ++i) {
            now->right = l[i + 1];
            now->left = l[i - 1];
            now = l[i + 1];
        }
        now->left = l[l.size() - 2];
        return head;
    }
    
};