/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> printListReversingly(ListNode* head) {
        dfs(head);
        return tmp;
    }
    vector<int> tmp;
    void dfs(ListNode* p){
        if(p==NULL) return;
        dfs(p->next);
        tmp.push_back(p->val);
    }

};