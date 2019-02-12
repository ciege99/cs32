//
//  Set.cpp
//  Project2
//
//  Created by Collin Prince on 1/23/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//

#include "Set.h"
class Node;

Set::Set() {
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}

bool Set::insert(const ItemType& value) {
    if (head == nullptr)    // if list is empty
    {
        Node *n = new Node; //allocate & link
        link(nullptr, nullptr, n, value);
        return true;
    }
    else if (head->value == value)
        return false;
    else if (head->value > value) // if it needs to be at the top
    {
        Node *n = new Node; // allocate & link
        link(nullptr, head, n, value);
        return true;
    }
    else if (tail->value < value)   // if value is greater than tail's value, it should be new tail
    {
        Node *n = new Node; //allocate & link
        link(tail, nullptr, n, value);
        return true;
    }
    Node *p = head;
    while (p->next != nullptr)  //if this point is reached, value should be somewhere in middle
    {
        if (value == p->next->value) //if value in list, return false
            return false;
        if (value < p->next->value)   //sort list on insert from least to greatest
        {
            Node *n = new Node; //allocate new node and link it to list
            link(p, p->next, n, value);
            return true;
        }
        p = p->next; //increment p if no conditionals are true
    }
    return false; //return false if there is some sort of error and it is not added to list
}

             
bool Set::contains(const ItemType& value) const {
    return (this->find(value) != nullptr); // if a valid ptr is returned, return true
}

bool Set::erase(const ItemType& value) {
    if (head == nullptr)
        return false;
    else if (head->value == value && head->next == nullptr){ // if head is only item and matches
        delete head;
        head = nullptr;
        tail = nullptr;
        m_size--;
        return true;
    }
    else if (head->value == value) { //if head is the value and next node is not null
        Node* killMe = head;
        head = head->next;
        head->prev = nullptr;
        delete killMe;
        m_size--;
        return true;
    }
    else if (this->contains(value)) {
        Node* killMe = this->find(value); //set killMe equal to matching node address
        Node* prevNode = killMe->prev;
        prevNode->next = killMe->next; //link the node that follows killMe to the node before
        if (prevNode->next == nullptr) //if killMe was tail, set prevNode to be tail
        {
            tail = prevNode;
            delete killMe;
            m_size--;
            return true;
        }
        Node* nextNode = killMe->next;
        nextNode->prev = prevNode; //link the node that comes before killMe to the node after
        delete killMe;
        m_size--;
        return true;
    }
    else {
        return false; //list does not contain value, return false
    }
}

bool Set::get(int pos, ItemType& value) const {
    if (pos < 0 || pos >= m_size) //pos out of range, return false
        return false;
    Node* p = head;
    int counter = 0; //use counter to keep track of # of items traversed
    while (p != nullptr && counter < pos)
    {
        p = p->next; //iterate through list and count how many items have been traversed
        counter++;
    }
    value = p->value; //p after loop will give node that matches the pos parameter
    return true;
}

void Set::swap(Set &other) {
    
    Node* temp = this->head;
    this->head = other.head;
    other.head = temp;
    
    temp = this->tail;
    this->tail = other.tail;
    other.tail = temp;
    
    int itemTemp = this->m_size;
    this->m_size = other.m_size;
    other.m_size = itemTemp;
    
}

Set& Set::operator=(const Set &src) {
    if (this == &src)   //return object if they are identical
        return *this;

    Set temp(src); //construct temp with contents of src
    swap(temp); //swap contents of temp and this    (temp holds previous contents of src)
    return *this;

}

Set::Set(const Set &src) {
    
    //startout by initializing a new set
    head = nullptr;
    tail = nullptr;
    m_size = 0;
    
    if (src.empty())
        return; //if copying an empty set, then just our empty constructed set is fine
    
    for (int i = 0; i < src.m_size; i++) //for the rest of the values, insert can handle the case
    {
        ItemType x; //create an item and then assign it value from src
        src.get(i, x); // loop through and get each value out of src
        this->insert(x);
    }
}

Set::~Set() {
//    Node* p = head;
    this->deleteNodes(head);   //use helper function to delete all the nodes
}


//Non-member functions

//When this function returns, result must contain one copy of each of the values that appear in s1 or s2 or both, and must not contain any other values. (You must not assume result is empty when it is passed in to this function; it might not be.)

void unite(const Set& s1, const Set& s2, Set& result) {
    
    if (&result == &s1 && &result == &s2)   //if they all refer to the same set, exit
        return;
    
    Set united; //create a set that will hold all of the unique values from src1 and src2

    int size = s1.size();  //create size variable so we don't call size function for each loop
    for (int i = 0; i < size; i++)
    {
        ItemType x; //insert all values from s1 since result is not the same as s1
        s1.get(i, x);
        united.insert(x);
    }

    size = s2.size();   //now set size equalt to s2's size
    for (int i = 0; i < size; i++)
    {
        ItemType x; //insert in all values from s2
        s2.get(i, x);
        united.insert(x);
    }
    result = united;    //set result equal to the United object
}

void subtract(const Set& s1, const Set& s2, Set& result) {
    
    Set subtracted;
    if (&s1== &s2){
        result = subtracted;  //if the srcs are the same, set result = to an empty set and return;
        return;
    }
    
    int size = s1.size();
    for (int i = 0; i < size; i++)  //insert values from s1 into subtracted
    {
        ItemType x;
        s1.get(i, x);
        subtracted.insert(x);
    }
    
    size = s2.size();
    for (int i = 0; i < size; i++)
    {
        ItemType x;
        s2.get(i, x);
        if (subtracted.contains(x)) //if subtracted contains x, then erase the shared value
            subtracted.erase(x);
    }
    
    result = subtracted; //after loops, set result = subtracted
}
//insert one set into it
//then insert the other set and do an if statement that if insert returns false, then erase that value





//helper functions
Set::Node* Set::find(const ItemType& value) const {
    if (head == nullptr)
    {
        Node* p = nullptr;
        return p;
    }
    else if (head->value == value)  // check if tail or head match
        return head;
    else if (tail->value == value)
        return tail;
    else {
        Node* p = head; //create a pointer to array and then iterate through
        while (p->next != nullptr && p->next->value <= value) //iterate until end or > than item
        {
            if (p->next->value == value) //if p->next == value, return pointer to this object
                return p->next;
            p = p->next; //continue on if no match is found
        }
        p = nullptr; // if it makes it out of loop then no match is found, so return nullptr
        return p;
    }
}


void Set::deleteNodes(Node* p) {
    while (p != nullptr)    //loop through each node and delete each
    {
        Node* killMe = p;
        p = p->next;
        delete killMe;
    }
}

//link function to be used in insert
void Set::link(Node *prevNode, Node *nextNode, Node *newNode, const ItemType &value) {
    //assume node has been allocated and assign values
    newNode->next = nextNode;
    newNode->prev = prevNode;
    newNode->value = value;
    if (prevNode == nullptr)    //check if it should the head
        this->head = newNode;
    else                        //else set prevNode's next pointer to new node
        prevNode->next = newNode;
    if (nextNode == nullptr)    //check if it should be the tail
        this->tail = newNode;
    else
        nextNode->prev = newNode;   //else set nextNode's prev pointer to new node
    
    this->m_size++; //increment size

}


