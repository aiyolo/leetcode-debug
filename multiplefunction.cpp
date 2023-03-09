
#include "header.h"
#include <algorithm>
using namespace std;

class MinStack {
public:
    /** initialize your data structure here. */
    stack<pair<int,int>> stk;
    stack<pair<int,int>> minStk;
    int id;
    MinStack() {
        id = 0;
    }
    
    void push(int x) {
        stk.push({id, x});
        if(minStk.empty() || x<=minStk.top().second){
            minStk.push({id, x});
        }
        id++;
    }
    
    void pop() {
        auto [tid, tx] = stk.top();
        stk.pop();
        if(!minStk.empty() && tid==minStk.top().first){
            minStk.pop();
        }
    }
    
    int top() {
        return stk.top().second;
    }
    
    int min() {
        return minStk.top().second;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &MinStack::func);

int main() {
  Excecutor<MinStack, false> exc("../multiplefunction.txt");
  exc.instance = exc.createInstance<void>();
  REGISTER(push)
  REGISTER(pop)
  REGISTER(top)
  REGISTER(min)
  // REGISTER(getFront)
  // REGISTER(getRear)
  // REGISTER(isEmpty)
  // REGISTER(isFull)
  exc.run();

  // inputs
  // ["MyCircularDeque","insertLast","insertLast","insertFront","insertFront","getRear","isFull","deleteLast","insertFront","getFront"]
  // [[3],[1],[2],[3],[4],[],[],[],[4],[]]
}