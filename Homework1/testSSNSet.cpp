//
//  testSSNSet.cpp
//  Homework1
//
//  Created by Collin Prince on 1/16/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//


#include "SSNSet.h"
#include <assert.h>

int main() {
    
    //basic function checks
    SSNSet set;
    assert(set.add(111111111));
    assert(set.add(222222222));
    assert(set.add(333333333));
    assert(! set.add(333333333));   //assert that add won't add a duplicate
    assert(set.add(444444444));
    assert(set.size() == 4);    // assert size function works
    set.print();
    
    
    //copy constructor check
    SSNSet set2(set);
    set.add(777777777);
    set.add(888888888);
    set2.print();   //check that set2 is not being modified by changes to original set
    assert(set2.size() == 4);
    
    //assignment operator check
    SSNSet set3;
    set3 = set;
    assert(set.add(555555555));
    assert(set.add(666666666));

    set3.print(); //check that set3 is not being modified by changes to original set
    assert(set3.size() == 6);
    assert(set.size() == 8);
    
    
    
}
