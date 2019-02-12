//
//  SSNSet.hpp
//  Homework1
//
//  Created by Collin Prince on 1/16/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//

#ifndef SSNSet_h
#define SSNSet_h

#include "Set.h"

using ItemType = unsigned long;
class SSNSet
{
public:
    SSNSet();          // Create an empty SSN set.
    
    bool add(ItemType ssn);
    // Add an SSN to the SSNSet.  Return true if and only if the SSN
    // was actually added.
    
    int size() const;  // Return the number of SSNs in the SSNSet.
    
    void print() const;
    // Write every SSN in the SSNSet to cout exactly once, one per
    // line.  Write no other text.
    
private:
    Set m_SSN;
    // Some of your code goes here.
};

#endif /* SSNSet_h */
