
#include "header.h"

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
    /**
    * Definition for singly-linked list.
    * struct ListNode {
    *     int val;
    *     ListNode *next;
    *     ListNode() : val(0), next(nullptr) {}
    *     ListNode(int x) : val(x), next(nullptr) {}
    *     ListNode(int x, ListNode *next) : val(x), next(next) {}
    * };
    */
    class Solution {
    public:
        ListNode* sortList(ListNode* head) {
            return sortList1(head, nullptr);
        }
        ListNode* sortList1(ListNode* head, ListNode* tail){
            if(head==nullptr){
                return head;
            }
            if(head->next==tail){
                head->next=nullptr;
                return head;
            }
            ListNode* slow=head, *fast =head;
            while(fast!=tail && fast->next!=tail){
                slow= slow->next;
                fast= fast->next->next;
            }
            ListNode* mid = slow;
            return merge(sortList1(head, mid), sortList1(mid,tail));
        }

        ListNode* merge(ListNode* head1, ListNode* head2){
            ListNode* dummy = new ListNode(0);
            ListNode* cur = dummy;
            ListNode* cur1=head1, *cur2 = head2;
            while(cur1&& cur2){
                if(cur1->val<cur2->val){
                    cur->next = cur1;
                    cur1 = cur1->next;
                }
                else{
                    cur->next = cur2;
                    cur2 = cur2->next;
                }
                cur = cur->next;
            }
            if(cur1){
                cur->next = cur1;
            }
            if(cur2){
                cur->next = cur2;
            }
            return dummy->next;
        }
    };

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
  Excecutor<Solution, true> exc("../testcases.txt");
  exc.instance = exc.createInstance<void>();
  REGISTER(sortList)
  exc.run();
}