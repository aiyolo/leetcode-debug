
#include "header.h"
using namespace std;

class Solution {
public:
    vector<int> shuffle(vector<int> nums, int n) {
        vector<int> ans(2*n, 0);
        for(int i=0; i<n; i++){
            ans[2*i] = nums[i];
            ans[2*i+1] = nums[n+i];
        }
        return ans;
    }
};


int main(){
    Excecutor<Solution> exc;
    using function_type = function_traits<decltype(&Solution::shuffle)>::stl_function_type;
    using tuple_type = function_traits<decay_t<decltype(&Solution::shuffle)>>::tuple_type;
    vector<int> a = {1,2};
    tuple_type tp = make_tuple(a, 2);
    cout << get<0>(tp);
    // auto ans = exc.init(&Solution::shuffle);
}