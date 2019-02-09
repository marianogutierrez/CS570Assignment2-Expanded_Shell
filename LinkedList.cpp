#include <string>

#include "LinkedList.hpp"

// Cameron Ozatalar
//  820087470

// Construct LinkedList
LinkedList::LinkedList(){
    this -> head = NULL;
    this -> tail = NULL;
    this -> size = 0;
}

// Deconstruct LinkedList
LinkedList::~LinkedList(){
    ListNode *c = this -> head;
    while(this -> size > 0){
        this -> head = c -> next;
        delete c;
        c = this -> head;
        this -> size--;
    }
}

// Add Node to LL
void LinkedList::add(string s){
    ListNode *node = new ListNode(new string(s));

    if(this -> size == 0){
        this -> head = this -> tail = node;
    }else{
        this -> tail -> next = node;
        this -> tail = node;
    }

    this -> size++;
}

// Prints all items in LL
string LinkedList::toString(){
    string r = "[";

    ListNode *current = this -> head;
    for(int i = 0; i < this -> size; i++){
        r.append("{");
        r.append(*(current -> data));
        r.append("},");
        current = current -> next;
    }

    r = r.substr(0, r.length()-1);
    r.append("]");
    return r;
}

// Construct ListNode
LinkedList::ListNode::ListNode(string* d){
    this -> data = d;
    this -> next = NULL;
}

// Deconstruct ListNode
LinkedList::ListNode::~ListNode(){
    delete this -> data;
}
