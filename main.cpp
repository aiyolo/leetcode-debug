
#include "header.h"

// class Solution {
//     vector<int> nums;
// public:
//     Solution(vector<int>& nums) : nums(nums){
//     }
    
//     int pick(int target) {
//         int ans;
//         for(int i=0, cnt=0; i<nums.size(); i++){
//             if(target == nums[i]){
//                 cnt++;
//                 if(rand()%cnt==0){
//                     ans = i;
//                 }
//             }
//         }
//         return ans;
//     }
// };

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */


class OrderedStream {
public:
    vector<string> arr;
    int ptr;
    OrderedStream(int n) {
        arr.resize(n+1);
        ptr =1 ;
    }
    
    vector<string> insert(int idKey, string value) {
        arr[idKey] = value;
        vector<string> ans;
        if(idKey==ptr){
            while(ptr<arr.size() && arr[ptr]!="" ){
                ans.push_back(arr[ptr]);
                ptr++;
            }
        }
        return ans; 
    }
};

int main(){
    Excecutor<OrderedStream, false> exc;
    exc.parsefromInputs();
    exc.m_instance = exc.Instance<int>();
    exc.registerMemberFunction("insert", &OrderedStream::insert);
    exc.run();

    // // exc.init(&Solution::shuffle);
    // exc.parse();
    // exc.callMemFunc("Solution", &Solution);
    // exc.run();
}