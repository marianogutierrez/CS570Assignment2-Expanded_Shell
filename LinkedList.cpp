#include <string>

#include "LinkedList.hpp"

// Cameron Ozatalar 
// Mariano Gutierrez

// Construct LinkedList
LinkedList::LinkedList(){
    this -> head = NULL;
    this -> tail = NULL;
    this -> size = 0;
}

// Deconstruct LinkedList
LinkedList::~LinkedList(){
    ListNode *current = this -> head;
    while(this -> size > 0){
        this -> head = current -> next;
        delete current;
        current = this -> head;
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

//Removes the first item of the Linked List
string* LinkedList::removeFirst() {
    if(head == NULL)
        return NULL;
    
    string* token = head -> data;
    ListNode *tmp = head;
    head = head -> next;

    if(head == NULL)
        tail == NULL; // instance in which our list is empty as a result

    size--;
    return token;
}

// Prints all items in LL
string LinkedList::toString(){
    string returnStr = "[";

    ListNode *current = this -> head;
    for(int i = 0; i < this -> size; i++){
        returnStr.append("{");
        returnStr.append(*(current -> data));
        returnStr.append("},");
        current = current -> next;
    }

    returnStr = returnStr.substr(0, returnStr.length()-1);
    returnStr.append("]");
    return returnStr;
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
