#include "header.h"

// 在此处定义 Solution 类
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(root==nullptr) return {};
        vector<vector<int>> res;
        queue<TreeNode*> que;
        que.push(root);
        while(!que.empty()){
            int size = que.size();
            vector<int> vec;
            while(size--){
                TreeNode* node = que.front();
                vec.push_back(node->val);
                que.pop();
                if(node->left!=nullptr) que.push(node->left);
                if(node->right!=nullptr) que.push(node->right);
            }
            res.push_back(vec);
        }
        return res;
    }
};

int main(){
    Solution s;
    ifstream cin("../testcases.txt");
    // 在此处定义 Solution 成员函数的参数
    TreeNode* root;
    parse(cin, root);
    vector<vector<int>> ans = s.levelOrder(root);
    cout << ans << endl;
    
}
