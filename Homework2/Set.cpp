//
//  Set.cpp
//  Homework2
//
//  Created by Collin Prince on 2/2/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//

#include "Set.h"

#include <iostream>
#include <cstdlib>

Set::Set(int capacity)
: m_size(0), m_capacity(capacity)
{
    if (capacity < 0)
    {
        std::cout << "A Set capacity must not be negative." << std::endl;
        std::exit(1);
    }
    m_data = new ItemType[m_capacity];
}

bool Set::insert(const ItemType& value)
{
    if (m_size == m_capacity)
        return false;
    int pos = findFirstAtLeast(value);
    if (pos < m_size  &&  m_data[pos] == value)
        return false;
    for (int k = m_size; k > pos; k--)
        m_data[k] = m_data[k-1];
    m_data[pos] = value;
    m_size++;
    return true;
}

bool Set::erase(const ItemType& value)
{
    int pos = findFirstAtLeast(value);
    if (pos == m_size  ||  m_data[pos] != value)
        return false;
    for ( ; pos < m_size - 1; pos++)
        m_data[pos] = m_data[pos+1];
    m_size--;
    return true;
}

bool Set::get(int i, ItemType& value) const
{
    if (i < 0  ||  i >= m_size)
        return false;
    value = m_data[i];
    return true;
}

void Set::swap(Set& other)
{
    // Swap pointers to the elements.
    
    ItemType* tempData = m_data;
    m_data = other.m_data;
    other.m_data = tempData;
    
    // Swap sizes
    
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
    
    // Swap capacities
    
    int tempCapacity = m_capacity;
    m_capacity = other.m_capacity;
    other.m_capacity = tempCapacity;
}

Set::~Set()
{
    delete [] m_data;
}

Set::Set(const Set& other)
: m_size(other.m_size), m_capacity(other.m_capacity)
{
    m_data = new ItemType[m_capacity];
    
    // Since the only elements that matter are those up to m_size, only
    // they have to be copied.
    
    for (int k = 0; k < m_size; k++)
        m_data[k] = other.m_data[k];
}

Set& Set::operator=(const Set& rhs)
{
    if (this != &rhs)
    {
        Set temp(rhs);
        swap(temp);
    }
    return *this;
}

int Set::findFirstAtLeast(const ItemType& value) const
{
    int begin = 0;
    int end = m_size;
    while (begin < end)
    {
        int mid = (begin + end) / 2;
        if (value < m_data[mid])
            end = mid;
        else if (m_data[mid] < value)
            begin = mid + 1;
        else
            return mid;
    }
    return begin;
}
