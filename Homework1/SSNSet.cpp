//
//  SSNSet.cpp
//  Homework1
//
//  Created by Collin Prince on 1/16/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//

#include "SSNSet.h"
#include "Set.h"
#include <iostream>

SSNSet::SSNSet() : m_SSN() {}

bool SSNSet::add(ItemType ssn)
{
    if (m_SSN.insert(ssn))
        return true;
    return false;
}
// Add an SSN to the SSNSet.  Return true if and only if the SSN
// was actually added.

int SSNSet::size() const
{
    return m_SSN.size();
}
// Return the number of SSNs in the SSNSet.

void SSNSet::print() const
{
    for (int i = 0; i < m_SSN.size(); i++)
    {
        //create a variable of ItemType so we can use the get function to fetch each value
        ItemType x;
        m_SSN.get(i, x);
        std::cout << x << std::endl;
    }
    
}
// Write every SSN in the SSNSet to cout exactly once, one per
// line.  Write no other text.
