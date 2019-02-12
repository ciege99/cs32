//
//  test3.cpp
//  Project2
//
//  Created by Collin Prince on 1/25/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//

//must set ItemType to be unsigned long

#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Set uls;
    assert(uls.insert(10));
    assert(uls.insert(20));
    assert(uls.size() == 2);
    assert(uls.contains(20));
    ItemType x = 30;
    assert(uls.get(0, x)  &&  x == 10);
    assert(uls.get(1, x)  &&  x == 20);
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
    }
