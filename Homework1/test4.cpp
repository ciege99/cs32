//
//  test4.cpp
//  Homework1
//
//  Created by Collin Prince on 1/19/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//

//in newSet.h change the type alias for the Set's item type to specify unsigned long as the item type without making any other changes, recompile newSet.cpp, and link it to a file containing

#include "newSet.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Set uls;
    assert(uls.insert(20));
    assert(uls.insert(10));
    assert(uls.size() == 2);
    assert(uls.contains(10));
    ItemType x = 30;
    assert(uls.get(0, x)  &&  x == 10);
    assert(uls.get(1, x)  &&  x == 20);
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}
