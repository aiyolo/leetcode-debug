
#include "header.h"
class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        vector<int> ans(2*n, 0);
        for(int i=0; i<n; i++){
            ans[2*i] = nums[i];
            ans[2*i+1] = nums[n+i];
        }
        return ans;
    }
    void func(vector<int>&nums, int n){
        cout << "func";
    }
};


int main(){
    Excecutor<Solution> exc;
    // exc.init(&Solution::shuffle);
    exc.parse();
    exc.callMemFunc("shuffle", &Solution::shuffle);
    // exc.run();
}