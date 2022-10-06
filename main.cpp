
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


// class OrderedStream {
// public:
//     vector<string> arr;
//     int ptr;
//     OrderedStream(int n) {
//         arr.resize(n+1);
//         ptr =1 ;
//     }
    
//     vector<string> insert(int idKey, string value) {
//         arr[idKey] = value;
//         vector<string> ans;
//         if(idKey==ptr){
//             while(ptr<arr.size() && arr[ptr]!="" ){
//                 ans.push_back(arr[ptr]);
//                 ptr++;
//             }
//         }
//         return ans; 
//     }
// };

class MyCircularDeque {
public:
    vector<int> arr;
    int front, rear;
    int capacity;
    MyCircularDeque(int k) {
        capacity = k;
        arr.resize(k);
        front = rear = 0;
    }
    
    bool insertFront(int value) {
        if(isFull()){
            return false;
        }
        front = (front-1+capacity)%capacity;
        arr[front] = value;
        return true;
    }
    
    bool insertLast(int value) {
        if(isFull()){
            return false;
        }
        arr[rear] = value;
        rear = (rear+1)%capacity;
        return true;
    }
    
    bool deleteFront() {
        if(isEmpty()){
            return false;
        }
        front = (front+1)%capacity;
        return true;
    }
    
    bool deleteLast() {
        if(isEmpty()){
            return false;
        }
        rear = (rear-1 +capacity)%capacity;
        return true;
    }
    
    int getFront() {
        if(isEmpty()){
            return -1;
        }
        return arr[front];
    }
    
    int getRear() {
        if(isEmpty()){
            return -1;
        }
        int back = (rear-1+capacity)%capacity;
        return arr[back];
    }
    
    bool isEmpty() {
        return rear == front;
    }
    
    bool isFull() {
        return (rear-front)==0;
    }
};

int main(){
    Excecutor<MyCircularDeque, false> exc;
    exc.parsefromInputs();
    exc.m_instance = exc.Instance<int>();
    exc.registerMemberFunction("insertFront", &MyCircularDeque::insertFront);
    exc.registerMemberFunction("insertLast", &MyCircularDeque::insertLast);
    exc.registerMemberFunction("deleteFront", &MyCircularDeque::deleteFront);
    exc.registerMemberFunction("deleteLast", &MyCircularDeque::deleteLast);

    exc.registerMemberFunction("getFront", &MyCircularDeque::getFront);
    exc.registerMemberFunction("getRear", &MyCircularDeque::getRear);
    exc.registerMemberFunction("isEmpty", &MyCircularDeque::isEmpty);
    exc.registerMemberFunction("isFull", &MyCircularDeque::isFull);
    exc.run();

// inputs
// ["MyCircularDeque","insertLast","insertLast","insertFront","insertFront","getRear","isFull","deleteLast","insertFront","getFront"]
// [[3],[1],[2],[3],[4],[],[],[],[4],[]]
}