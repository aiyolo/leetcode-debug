
#include "header.h"
#include <functional>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size(), n= matrix[0].size();
        int left=0,right=n-1;
        int up=0, down=m-1;
        int r=0, c=0;
        vector<int> ans;
        while(left<=right && up<=down){
            for(int i=left,j=up ; j<=right; j++){
                ans.push_back(matrix[i][j]);
            }
            for(int i=up+1, j=right; i<=down; i++){
                ans.push_back(matrix[i][j]);
            }
            if(left<right && up<down){
                for(int i=down, j=right-1; j>=left; j--){
                ans.push_back(matrix[i][j]);
                }
                for(int i=down-1, j=left; i>=up+1; i--){
                    ans.push_back(matrix[i][j]);
                }
            }
            left++;
            right--;
            up++;
            down--;
        }
        return ans;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
  Excecutor<Solution, true> exc("../testcases.txt");
  exc.instance = exc.createInstance<void>();
  REGISTER(spiralOrder)
  exc.run();
}