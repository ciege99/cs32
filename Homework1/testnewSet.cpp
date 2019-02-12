//
//  testnewSet.cpp
//  Homework1
//
//  Created by Collin Prince on 1/17/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//

#include <cassert>
#include <iostream>
#include "newSet.h"

int main()
{
    
    //unsigned long tests for newSet
    
//    Set *set1, *set2, *set3;
//    set1 = new Set(5);
//    assert(set1->insert(1));
//    assert(set1->insert(2));
//    assert(set1->insert(3));
//    assert(set1->insert(4));
//    assert(set1->insert(5));
//    assert(!set1->insert(6));    // check that you cannot add numbers past original length
//
//
//    //assignment operator check
//    set2 = new Set(10);
//    set2->insert(10);
//    *set2 = *set1;
//    assert(set2->contains(1) && set2->contains(2) && set2->contains(3) && set2->contains(4) && set2->contains(5));
//    assert(set1->erase(1)); //check that erasing from one does not delete from another
//    assert(set2->contains(1));
//    assert(set1->size() == 4 && set2->size() == 5);
//
//    //copy constructor check
//    set3 = new Set(*set2);
//    assert(set3->contains(1) && set3->contains(2) && set3->contains(3) && set3->contains(4) && set3->contains(5)); // check that values were carried over
//    assert(set2->erase(1) && set3->contains(1)); // check that deleting from one does not affect the other
//    assert(set2->size() == 4 && set3->size() == 5);
//
//    //empty/erase check
//    assert(set1->erase(2) && set1->erase(3) && set1->erase(4) && set1->erase(5) && set1->size() == 0);
//
//
//    delete set1;
//    delete set2;
//    delete set3;
//
//    //original basic set test
//    Set *ss1, *ss2, *ss3;
//    ss1 = new Set;
//    ss2 = new Set;
//    assert(ss1->insert(111));
//    assert(ss1->insert(222));
//    assert(ss1->insert(333));
//    assert(! ss1->insert(111)); //check that insert does not duplicate
//    assert(ss1->erase(111)); // check that erase works
//                        //ss1 should only contain 222 & 333 at this point
//    ss3 = new Set(*ss1);
//    *ss3 = *ss1;
//    ss3->erase(333);
//    ss3->dump();
//    assert(! ss1->erase(111)); // assert that erase does not work when item is not present
//    assert(ss1->erase(222));
//    assert(ss1->contains(333)); // assert that contains works
//    assert(! ss1->contains(111)); // assert that contains returns false when item not present
//    ss1->dump();    //ss1 should only contain 333 at this point
//    ss3->dump();    //ss3 should only contain 222 at this point
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

    
    //string tests for newSet
    Set set1(5);
    Set set2(10);
    Set set3;
    

    //insert checks
    assert(set1.insert("bill") && set1.insert("mandy") && set1.insert("jimmy")); //standard inserts
    assert(! set1.insert("bill")); //insert should fail for duplicate
    assert(set1.insert("")); //insert for an empty string should work
    assert(! set1.insert(""));
    assert(set1.insert("dave"));
    assert(! set1.insert("ope")); //make sure insert fails past given range
    
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
    
    //copy constructor checks
    Set set4(set3);
    assert(set4.contains("a") && set4.contains("b") && set4.contains("c"));
    assert(set4.size() == 3);
    assert(set3.erase("a"));
    assert(set4.contains("a")); // make sure that deleting from original does not affect copy
    assert(set3.insert("A"));
    assert(! set4.contains("A")); // make sure that adding to original does not affect copy
    assert(set4.erase("c") && set3.contains("c")); //make sure changing copy does not affect original
    assert(set4.insert("c"));
    
    //assignment operator check
    Set set5(5);
    assert(set5.insert("blah") && set5.insert("bleh") && set5.insert("blih") && set5.insert("bloh") && set5.insert ("bluh"));
    set4 = set5;
    assert(set4.contains("blah") && set4.contains("bleh") && set4.contains("blih") && set4.contains("bloh") && set4.contains("bluh"));
    assert(set4.erase("bluh") && set5.contains("bluh")); //make sure deleting from copy does not affect OG
    assert(set5.erase("blah") && set4.contains("blah")); //make sure reverse is true
    assert(set4.size() == 4 && set5.size() == 4);
    
    //test that constructor doesn't work for negative input
    Set set6(-5);
    
    
    std::cout << "All tests passed" << std::endl;
    
}
