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
    ListNode *current;
    while(head != NULL){
       current = head;
       head = head -> next;
       delete current;
    }
}

// Add Node to LL
void LinkedList::add(string str){ 
    ListNode *node = new ListNode(str);

    if(this -> size == 0){
        this -> head = this -> tail = node;
    }else{
        this -> tail -> next = node;
        this -> tail = node;
    }

    this -> size++;
}

//Removes the first item of the Linked List
string LinkedList::removeFirst() {
    if(head == NULL)
        return NULL;
    
    string token = head -> data;
    
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
        returnStr.append((current -> data));
        returnStr.append("},");
        current = current -> next;
    }

    returnStr = returnStr.substr(0, returnStr.length()-1);
    returnStr.append("]");
    return returnStr;
}

// Construct ListNode
LinkedList::ListNode::ListNode(string data){
    this -> data = data;
    this -> next = NULL;
}

// Deconstruct ListNode
// NOTE: not needed since contains a string allocated for the classs; will be autodestroyed
LinkedList::ListNode::~ListNode(){
    //delete this -> data; 
}
