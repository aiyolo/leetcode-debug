#include "header.h"

using namespace std;

class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> stk;
        int i=0, j=0;
        while(i<pushed.size() && j<popped.size()){
            stk.push(pushed[i++]);
            while(!stk.empty() && popped[j]==stk.top()){
                stk.pop();
                j++;
            }
        }
        return stk.empty();
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
  Excecutor<Solution, true> exc("../testcases.txt");
  exc.instance = exc.createInstance<void>();
  REGISTER(validateStackSequences)
  exc.run();
}