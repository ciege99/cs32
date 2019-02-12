//
//  Set.hpp
//  Project2
//
//  Created by Collin Prince on 1/23/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//

#ifndef Set_h
#define Set_h

#include <string>

using ItemType = std::string;
//using ItemType = unsigned long;

//#include "IntWrapper.h"      // TODO: remove this line after testing
//using ItemType = IntWrapper; // TODO: replace this line after testing


class Set
{
public:
    Set(); //done
    bool empty() const; //done
    int size() const; //done
    bool insert(const ItemType& value); //done
    bool erase(const ItemType& value); //done
    bool contains(const ItemType& value) const; //done
    bool get(int pos, ItemType& value) const; //done
    void swap(Set& other); //done
    
    //maintenance functions
    Set(const Set &src); //done
    Set& operator=(const Set &src); //done
    ~Set(); //done

private:
    struct Node {
        ItemType value;
        Node *prev;
        Node *next;
    } *head, *tail;
    
    int m_size;
    
    //helper functions
    Node* find(const ItemType& value) const;    //function to find item

    void deleteNodes(Node* p);  //function to delete all nodes from p to end
    
    //function to link inserted nodes
    void link(Node *prevNode, Node *nextNode, Node *newNode, const ItemType &value);
    
};

//inline functions
inline bool Set::empty() const {
    return head == nullptr;
}

inline int Set::size() const {
    return m_size;
}

//public functions
void unite(const Set& s1, const Set& s2, Set& result);

void subtract(const Set& s1, const Set& s2, Set& result);


#endif /* Set_h */
