
#include "header.h"

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> umap;
        for(int i=0; i<nums.size(); i++){
            if(umap.count(target-nums[i])){
                return {i, umap[target-nums[i]]};
            }
            else{
                umap.insert({nums[i], i});
            }
        }
        return {};
    }
};

int main(){
    Excecutor<Solution, true> exc;
    exc.parsefromInputs();
    exc.m_instance = exc.Instance<void>();
    exc.registerMemberFunction("twoSum", &Solution::twoSum);
    exc.run();

}