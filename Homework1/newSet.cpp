//
//  newSet.cpp
//  Homework1
//
//  Created by Collin Prince on 1/17/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//

#include "newSet.h"

#include <iostream>

const int DEFAULT_MAX_ITEMS = 250;

Set::Set()
{
    m_length = DEFAULT_MAX_ITEMS;
    m_items = 0;
    m_set = new ItemType[DEFAULT_MAX_ITEMS];
}

Set::Set(int length)
{
    if (length <= 0) //return from array if length is negative
    {
        std::cout << "Negative or zero length given." << std::endl;
        exit(1);
    }
    m_length = length;
    m_items = 0;
    m_set = new ItemType[length];
}

Set::Set(const Set &src)
{
    m_length = src.m_length;
    m_items = src.m_items;
    m_set = new ItemType[m_length];
    for (int i = 0; i < m_items; i++)
        m_set[i] = src.m_set[i];
}

Set::~Set()
{
    delete [] m_set;
}
Set& Set::operator=(const Set &src)
{
    if (this == &src)
        return *this;
    delete [] m_set;
    m_length = src.m_length;
    m_items = src.m_items;
    m_set = new ItemType[m_length];
    for (int i = 0; i < m_items; i++)
        m_set[i] = src.m_set[i];
    return *this;
}

bool Set::empty() const
{
    if(m_items == 0)
        return true;
    return false;
}

//Should this return true size of set or number of distinct items?
int Set::size() const
{
    return m_items;
}

bool Set::contains(const ItemType& value) const
{
    for (int i = 0; i < m_items; i++)
    {
        if (value == m_set[i])
            return true;
    }
    return false;
}
// Return true if the value is in the set, otherwise false.


bool Set::insert(const ItemType& value)
{
    //check if set has reached limit
    if (m_items == m_length)
        return false;
    
    //check to see if the set contains the value
    if (this->contains(value))
        return false;
    
    //add to set and increment m_length if value passes previous tests, return true
    m_set[m_items] = value;
    m_items++;
    return true;
}



bool Set::erase(const ItemType& value)
{
    //loop through set
    for (int i = 0; i < m_items; i++)
    {
        //if value is found, sort left and decrement length, return true
        if (value == m_set[i])
        {
            for (int j = i; j < m_items-1; j++)
                m_set[j] = m_set[j+1];
            m_items--;
            return true;
        }
    }
    // if nothing matches, return false
    return false;
}

bool Set::get(int i, ItemType& value) const
{
    //make sure i is in range
    if (i >= 0 && i < m_items)
    {
        //loop through each Item
        int k = 0; // k will be used to see how many items m_set[j] is greater than
        for (int j = 0; j < m_items; j++)
        {
            k = 0;
            // loop through items again to compare against m_set[j]
            for (int z = 0; z < m_items; z++)
            {
                if (m_set[j] > m_set[z])
                    k++;
            }
            // if m_set[j] is greater than the specified number of items, copy it and return true
            if (k == i)
            {
                value = m_set[j];
                return true;
            }
        }
    }
    // if i is not in range, return false
    return false;
}
// If 0 <= i < size(), copy into value the item in the set that is
// strictly greater than exactly i items in the set and return true.
// Otherwise, leave value unchanged and return false.


//Change the implementation of the swap function so that the number of statement executions when swapping two sets is the same no matter how many items are in the sets. (You would not satisfy this requirement if, for example, your swap function caused a loop to visit each item in the sets, since the number of statements executed by all the iterations of the loop would depend on the number of items in the sets.)

void Set::swap(Set& other)
{
    //create temp Set that is a copy of this Set object, then swap
    //default assignment operator will work since it has been updated
    Set temp = *this;
    *this = other;
    other = temp;
}

void Set::dump() const
{
    for (int i = 0; i < m_items; i++)
        std::cerr << m_set[i] << " ";
    std::cerr << std::endl;
}
// Exchange the contents of this set with the other one.
