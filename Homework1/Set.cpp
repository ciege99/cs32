//
//  Set.cpp
//  Homework1
//
//  Created by Collin Prince on 1/16/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//

#include "Set.h"

#include <iostream>

Set::Set()
{
    m_length = 0;
}

bool Set::empty() const
{
    if(m_length == 0)
        return true;
    return false;
}

int Set::size() const
{
    return m_length;
}

bool Set::contains(const ItemType& value) const
{
    for (int i = 0; i < m_length; i++)
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
    if (m_length == DEFAULT_MAX_ITEMS)
        return false;
    
    //check to see if the set contains the value
    if (this->contains(value))
            return false;
    
    //add to set and increment m_length if value passes previous tests, return true
    m_set[m_length] = value;
    m_length++;
    return true;
}



bool Set::erase(const ItemType& value)
{
    //loop through set
    for (int i = 0; i < m_length; i++)
    {
        //if value is found, sort left and decrement length, return true
        if (value == m_set[i])
        {
            for (int j = i; j < m_length-1; j++)
                m_set[j] = m_set[j+1];
            m_length--;
            return true;
        }
    }
    // if nothing matches, return false
    return false;
}

bool Set::get(int i, ItemType& value) const
{
    //make sure i is in range
    if (i >= 0 && i < m_length)
    {
        //loop through each Item
        int k = 0; // k will be used to see how many items m_set[j] is greater than
        for (int j = 0; j < m_length; j++)
        {
            k = 0;
            // loop through items again to compare against m_set[j]
            for (int z = 0; z < m_length; z++)
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

void Set::swap(Set& other)
{
    //create temp Set that is a copy of this Set object, then swap
    //default assignment operator will work since there is no dynamic alloc memory
//    Set temp = *this;
//    *this = other;
//    other = temp;
    
    //multiple iteration approach without using set
    //see which length is greater and then iterate through the greater length and swap values
    if (m_length > other.m_length)
    {
        for (int i = 0; i < m_length; i++)
        {
            ItemType temp = m_set[i];
            m_set[i] = other.m_set[i];
            other.m_set[i] = temp;
        }
    }
    else
    {
        for (int i = 0; i < other.m_length; i++)
        {
            ItemType temp = m_set[i];
            m_set[i] = other.m_set[i];
            other.m_set[i] = temp;
        }
    }
    //swap length values
    int temp = m_length;
    m_length = other.m_length;
    other.m_length = temp;
    
}

void Set::dump() const
{
    for (int i = 0; i < m_length; i++)
        std::cerr << m_set[i] << " ";
    std::cerr << std::endl;
}


