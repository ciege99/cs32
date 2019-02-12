//
//  test1.cpp
//  Homework1
//
//  Created by Collin Prince on 1/19/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//

//Given Set.h with the type alias for the Set's item type specifying std::string, if we make no change to your Set.cpp, then if we compile your Set.cpp and link it to a file containing

#include "Set.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Set ss;
    assert(ss.insert("roti"));
    assert(ss.insert("pita"));
    assert(ss.size() == 2);
    assert(ss.contains("pita"));
    ItemType x = "laobing";
    assert(ss.get(0, x)  &&  x == "pita");
    assert(ss.get(1, x)  &&  x == "roti");
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
    }
