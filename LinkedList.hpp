#pragma once //headfile guard to not stamp twice; similar to #ifndef GUARD_NAME  #define GUARD_NAME
#include <string>

using namespace std;

// Cameron Ozatalar
// Mariano Gutierrez

// LinkedList class
class LinkedList{
    public:
        class ListNode{ // ListNode class
            public:
                ListNode(string d);
                ~ListNode();

                string data; // essentially a char array
                ListNode* next;
        };
    
        LinkedList();
        ~LinkedList();
        void add(string s);
        string removeFirst();
        string toString();

        ListNode* head;
        ListNode* tail;
        int size;
};