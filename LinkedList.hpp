#include <string>

using namespace std;

// Cameron Ozatalar
//  820087470

// LinkedList class
class LinkedList{
    public:
        class ListNode{ // ListNode class
            public:
                ListNode(string* d);
                ~ListNode();

                string* data;
                ListNode* next;
        };
    
        LinkedList();
        ~LinkedList();
        void add(string s);
        string toString();

        ListNode* head;
        ListNode* tail;
        int size;
};