//
//  testSet.cpp
//  Homework1
//
//  Created by Collin Prince on 1/17/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//


#include "newSet.h"
#include <iostream>
#include <cassert>
#include <string>
using namespace std;

int main()
{
    //Tests for unsigned long with set.cpp
    
//    Set *ss1, *ss2, *ss3;
//    ss1 = new Set;
//    ss2 = new Set;
//    assert(ss1->insert(111));
//    assert(ss1->insert(222));
//    assert(ss1->insert(333));
//    assert(! ss1->insert(111)); //check that insert does not duplicate
//    assert(ss1->erase(111)); // check that erase works
//
//    ss3 = new Set(*ss1);
//    *ss3 = *ss1;
//    ss3->erase(333);
//    ss3->dump();
//    assert(! ss1->erase(111)); // assert that erase does not work when item is not present
//    assert(ss1->erase(222));
//    assert(ss1->contains(333)); // assert that contains works
//    assert(! ss1->contains(111)); // assert that contains returns false when item not present
//    ss1->dump();
//    ss3->dump();
//    //begin swap and check again
//    ss2->swap(*ss1);
//    assert(ss1->empty()); //check that ss1 is now empty
//    assert(! ss2->empty()); //check that ss2 is not empty
//    assert(ss2->contains(333)); //check that ss2 contains 333 since ss1 did before
//    assert(ss2->insert(222));
//    assert(ss2->insert(111));
//    assert(ss2->insert(110));
//    assert(ss2->insert(444));
//    unsigned long x;
//    assert(ss2->get(0, x)); // check that get returns correctly for all values
//    assert(x == 110);
//    assert(ss2->get(1,x));
//    assert(x == 111);
//    assert(ss2->get(2, x));
//    assert(x == 222);
//    assert(ss2->get(3, x));
//    assert(x == 333);
//    assert(ss2->get(4, x));
//    assert(x == 444);
//    assert(! ss2->get(5, x)); // check that get returns false for greater than value not in range
//    assert(x == 444); //assert that x is unchanged
//    assert(! ss2->get(-1, x));
//    assert(ss2->size() == 5);
//    assert(ss2->erase(444) && ss2->size() == 4); // check that erase works and decrements size
//    assert(!ss2->erase(444) && ss2->size() == 4); //check that size isn't decreased if erase is false
//    delete ss1;
//    ss2->dump();
//
//    delete ss2;
//    delete ss3;
//
//    cout << "All tests passed" << endl;
    
    
    
    //Tests for strings
    
    Set set1, set2, set3;
    
    //insert tests
    assert(set1.insert("bill") && set1.insert("mandy") && set1.insert("jimmy")); //standard inserts
    assert(! set1.insert("bill")); //insert should fail for duplicate
    assert(set1.insert("")); //insert for an empty string should work
    assert(! set1.insert(""));
    
    ItemType arr[246];
    for (int i = 0; i < 246; i++)
    {
        arr[i] = to_string(i);
    }
    //fill up set all the way
    for (int i = 0; i < 246; i++)
        assert(set1.insert(arr[i]));
    //check that nothing else can be added
    assert(! set1.insert("full"));
    assert(! set1.empty()); //test empty
    assert(set1.size() == 250); //test size
    
    //erase and contains test
    assert(set2.insert("a") && set2.insert("b") && set2.insert("c"));
    assert(set2.contains("a"));
    assert(! set2.contains("A"));
    assert(set2.erase("a"));
    assert(! set2.erase("a"));
    assert(! set2.contains("a"));
    
    assert(set2.insert("a"));
    
    //get checks
    assert(set3.insert("1") && set3.insert("2") && set3.insert("3"));
    ItemType x;
    assert(set3.get(0, x) && x == "1"); //check that each get statement is correct
    assert(set3.get(1, x) && x == "2");
    assert(set3.get(2, x) && x == "3");
    assert(!set3.get(3, x) && x == "3");    //check that get does not try to go out of range
    assert(!set3.get(-1, x) && x == "3");
    assert(set3.insert("4"));
    
    
    //swap checks
    set2.swap(set3);
    assert(set2.contains("1") && set2.contains("2") && set2.contains("3") && set2.contains("4"));
    assert(set3.contains("a") && set3.contains("b") && set3.contains("c"));
    assert(set3.size() == 3 && set2.size() == 4);
    assert(!set2.empty() && !set3.empty());
    
    cout << "All tests passed" << endl;
    
    
}
