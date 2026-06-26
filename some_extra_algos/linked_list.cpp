#include <iostream>
using namespace std;

class node{
    public:
    int data;
    node *next;

    node(int val){
        data = val;
        next = NULL;
    }
};

class list{
    node *head;
    node *tail;

    public:
    list(){
        head = tail = NULL;
    }

    void push_front(int val){
        node *new_node = new node(val);
        if(head == NULL){
            head = tail = new_node;
            return;
        } else{
            new_node->next = head;
            head = new_node;
            return;
        }
    }

    void push_back(int val){
        node *new_node = new node(val);
        if(head == NULL){
            head = tail = new_node;
            return;
        } else{
            tail->next = new_node;
            tail = new_node;
            return;
        }

    }

    void print_list(){
        node *temp = head;
        while(temp != NULL){
            cout << temp->data << " " << endl;
            temp = temp->next;
        }
        return;
    }

    void pop_front(){
        node *temp = head;
        cout << "Popped value: " << temp->data << endl;
        head = temp->next;
        temp->next = NULL;
        delete temp;
        return;
    }

    void pop_back(){
        node *temp = head;
        while(temp->next != tail){
            temp = temp->next;
        }
        cout << endl << "Popped value: " << tail->data << endl;
        temp->next = NULL;
        delete tail;
        tail = temp;
        return;
    }

    void insert(int val, int i){
        int pos = 0;
        node *new_node = new node(val);
        node *temp = head;
        if(i==0){
            push_front(val);
        } else {
            while(pos < i-1 && temp != NULL){
                temp = temp->next;
                pos+=1;
            }
            new_node->next = temp->next;
            temp->next = new_node;
            return;
        }
    }

    void search_ele(int val){
        node *temp = head;
        int pos = 0;
        while(temp != NULL){
            if(temp->data == val){
                cout << endl << val << " found at index " << pos << endl;
                return;
            }
            temp = temp->next;
            pos++;
        }
        cout << "Element not found";
        return;
    }

    node* reverse_list(){
        node *prev = NULL;
        node *curr = head;
        node *fur = NULL;
        while (curr != NULL){
            fur = curr->next;
            curr->next = prev;
            prev = curr;
            curr = fur;
        }
        tail = head;
        head = prev;
    }

    int length(){
        node *temp = head;
        int len = 0;
        while(temp != NULL){
            temp = temp->next;
            len++;
        }
        return len;
    }

    int print_middle(){
        node *temp = head;
        int len = length()/2;
        int pos = 0;
        while(pos != len){
            temp = temp->next;
            pos++;
        }
        return temp->data;
    }

    int max_element(){
        int max = head->data;
        node *temp = head;
        while (temp!= NULL) {
            if (temp->data >= max){
                max = temp->data;
            }
            temp = temp->next;
        }
        return max;
    }

    void sort(){
        
    }
};

int main() {
    list l1;
    l1.push_front(5);
    l1.push_back(7);
    l1.insert(2,1);
    l1.print_list();
    l1.pop_back();
    l1.print_list();
    l1.search_ele(2);
    l1.push_back(9);
    l1.push_back(0);
    l1.print_list();
    // l1.reverse_list();
    // l1.print_list();
    cout << l1.print_middle() << endl;
    cout << l1.length() << endl;
    return 0;
}