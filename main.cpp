
#include "header.h"

using namespace std;

class Solution {
public:
  vector<vector<int>> levelOrder(TreeNode *root) {
    if (root == nullptr)
      return {};
    vector<vector<int>> res;
    queue<TreeNode *> que;
    que.push(root);
    while (!que.empty()) {
      int size = que.size();
      vector<int> vec;
      while (size--) {
        TreeNode *node = que.front();
        vec.push_back(node->val);
        que.pop();
        if (node->left != nullptr)
          que.push(node->left);
        if (node->right != nullptr)
          que.push(node->right);
      }
      res.push_back(vec);
    }
    return res;
  }
};

int main() {
  Excecutor<Solution, true> exc("../testcases.txt");
  exc.instance = exc.createInstance<void>();
  exc.registerMemberFunction("levelOrder", &Solution::levelOrder);
  exc.run();
}