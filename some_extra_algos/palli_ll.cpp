#include <iostream>
using namespace std;

//  *Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class Solution {
public:
    string print_list(ListNode* head){
        ListNode* temp = head;
        string data = "";
        while (temp != NULL){
            data = data + to_string(temp->val);
            temp = temp->next;
        }
        return data;
    }

    ListNode* reverseList(ListNode* head) {
        ListNode *prev = NULL;
        ListNode *curr = head;
        ListNode *fur = NULL;

        while(curr != NULL){
            fur = curr->next;
            curr->next = prev;
            prev = curr;
            curr = fur;
        }
        head = prev;
        return head;
    }

    bool isPalindrome(ListNode* head) {
        if (print_list(head) == print_list(reverseList(head))){
            return true;
        } else {
            return false;
        }
        
    }
};
int main() {

    return 0;
}