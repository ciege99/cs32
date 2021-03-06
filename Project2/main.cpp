//
//  main.cpp
//  Project2
//
//  Created by Collin Prince on 1/23/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//

#include <iostream>
#include <cassert>
#include "Set.h"

int main() {
    
    //insert & contain tests
    Set list;
    assert(list.empty() == true);
    assert(list.insert("C") && list.insert("B") && list.insert("A")); //check that insert returns true
    assert(! list.insert("A")); //make sure copies are not insert
    assert(list.contains("A")); // make sure contains works
    assert(! list.contains("D")); //make sure contain returns false for no match
    
    assert(list.size() == 3);
    assert(list.empty() != true);
    
    
    //erase cases
    //case 1: empty
    Set list1;
    assert(! list1.erase("A") && list1.empty());
    //case 2: only 1 item
    Set list2;
    assert(list2.insert("A"));
    assert(! list2.erase("B") && list2.erase("A")); // assert that erase is false for B and true for A
    assert(list2.empty()); // assert list2 is empty after erase is run on A

    //case 3: only 2 items, head is match
    Set list3;
    assert(list3.insert("A") && list3.insert("B"));
    assert(list3.erase("A"));
    assert(list3.size() == 1 && list3.contains("B") && !list3.contains("A")); // assert that size is decremented by erase, list3 still contains b, and list3 does not contain A
    
    //case 4: only 2 items, tail is match
    Set list4;
    assert(list4.insert("A") && list4.insert("B"));
    assert(list4.erase("B"));
    assert(list4.size() == 1 && list4.contains("A") && !list4.contains("B"));
    //make sure size is decremented, list4 still contains A, and list 4 does not contain B
    
    //case 5: somewhere in the middle
    Set list5;
    assert(list5.insert("B") && list5.insert("A") && list5.insert("C"));
    assert(list5.contains("A") && list5.contains("B") && list5.contains("C"));
    assert(list5.erase("B"));
    assert(list5.contains("A") && list5.contains("C") && !list5.contains("B"));
    assert(list5.size() == 2);
    
    
    //tests for get
    Set list6;
    assert(list6.insert("D") && list6.insert("A") && list6.insert("C") && list6.insert("E") && list6.insert("Z"));
    
    ItemType x = "blank";
    assert(! list6.get(-1, x) && x == "blank");     //check get -1
    assert(list6.get(0, x) && x == "A");           //check get 0
    assert(list6.get(1, x) && x == "C");            //check get for pos > 0 & i < pos
    assert(list6.get(2, x) && x == "D");
    assert(list6.get(3, x) && x == "E");
    assert(list6.get(4, x) && x == "Z");            //test for greatest value
    assert(!list6.get(5, x) && x == "Z");           // check get for pos = size
    assert(!list6.get(100, x) && x == "Z");         //check get for pos > size
    
    
    //tests for copy constructor
    
    //case 1: copying an empty set
    Set src1;
    ItemType y1 = "blank";
    Set copy1(src1);
    //make sure both arrays are empty and get fails (i.e. nothing to get)
    assert(src1.empty() && copy1.empty() && !src1.get(0, y1) && !copy1.get(0, y1) && y1 == "blank");
    
    //case 2: items in the list
    Set src2;
    ItemType y2 = "blank";
    assert(src2.insert("D") && src2.insert("A") && src2.insert("Z") && src2.insert("R"));
    Set copy2(src2);
    assert(copy2.contains("D") && copy2.contains("A") && copy2.contains("Z") && copy2.contains("R"));
    assert(copy2.size() == 4 && copy2.empty() == false); // make sure size functions working correctly
    assert(copy2.get(0, y2) && y2 == "A");    //make sure get is working correctly
    assert(copy2.get(3, y2) && y2 == "Z");
    //check erase from copy does not affect contents of src
    assert(copy2.erase("A") && !copy2.contains("A") && src2.contains("A"));
    //check erase from src does not affect contents of copy
    assert(src2.erase("Z") && !src2.contains("Z") && copy2.contains("Z"));
    assert(src2.size() == 3 && copy2.size() == 3);
    
    
    
    //tests for assignment operator
    
    
    
    //case 1: setting equal to same object
    Set aSrc1;
    assert(aSrc1.insert("A") && aSrc1.insert("Z") && aSrc1.insert("D"));
    aSrc1 = aSrc1;
    assert(aSrc1.contains("A") && aSrc1.contains("Z") && aSrc1.contains("D"));
    
    //case 2: setting two empty sets equal to each other
    Set aSrc2, aCopy2;
    assert(aCopy2.empty() && aSrc2.empty());
    aCopy2 = aSrc2;
    assert(aCopy2.empty() && aSrc2.empty());    //check that they are both still empty
    assert(aSrc2.insert("A") && !aCopy2.contains("A")); //check that changing one does not change the other
    assert(aCopy2.insert("B") && !aSrc2.contains("B"));
    
    //case 3: setting a full set equal to an empty set
    Set aSrc3, aCopy3;
    assert(aCopy3.insert("A") && aCopy3.insert("B") && aCopy3.insert("C"));
    aCopy3 = aSrc3;
    assert(aCopy3.empty() && aCopy3.size() == 0 && !aCopy3.contains("A"));  //make sure they are both empty
    assert(aCopy3.insert("A") && !aSrc3.contains("A"));  //make sure changing one doesn't change other
    assert(aSrc3.insert("B") && !aCopy3.contains("B"));
    
    //case 4: setting an empty set equal to a full set
    Set aSrc4, aCopy4;
    assert(aSrc4.insert("D") && aSrc4.insert("E") && aSrc4.insert("A"));
    assert(aCopy4.empty());
    aCopy4 = aSrc4;
    assert(aCopy4.contains("D") && aCopy4.contains("E") && aCopy4.contains("A"));
    assert(aSrc4.insert("G") && !aCopy4.contains("G")); //make sure changing one doesn't change other
    assert(aCopy4.insert("H") && !aSrc4.contains("H"));
    
    //case 5: setting two full sets equal to each other
    Set aSrc5, aCopy5;
    assert(aSrc5.insert("Y") && aSrc5.insert("U") && aSrc5.insert("MAD"));
    assert(aCopy5.insert("I") && aCopy5.insert("DONT") && aCopy5.insert("KNOW"));
    aCopy5 = aSrc5;
    assert(aCopy5.contains("Y") && aCopy5.contains("U") && aCopy5.contains("MAD"));
    assert(aSrc5.insert("YEET") && !aCopy5.contains("YEET"));
    assert(aCopy5.insert("SKRT") && !aSrc5.contains("SKRT"));
    
    
    
    //swap tests
    
    //case 1: swapping two empty sets
    Set a1, b1;
    a1.swap(b1);
    assert(a1.empty() && b1.empty());
    assert(a1.insert("A") && !b1.contains("A"));    //make sure changing one does not change the other
    assert(b1.insert("B") && !a1.contains("B"));
    
    //case 2: swapping an empty set and a full set
    Set a2, b2;
    assert(a2.insert("C") && a2.insert("B") && a2.insert("A"));
    a2.swap(b2);
    assert(b2.contains("C") && b2.contains("B") && b2.contains("A"));   //check contents are swapped
    assert(a2.empty() && b2.size() == 3);
    assert(b2.insert("Z") && !a2.contains("Z"));    //check that changing one does not change other
    assert(a2.insert("X") && !b2.contains("X"));
    
    
    //case 3: swapping a full set and an empty set
    Set a3, b3;
    assert(b3.insert("1") && b3.insert("2") && b3.insert("3"));
    a3.swap(b3);
    assert(a3.contains("1") && a3.contains("2") && a3.contains("3") && b3.empty()); //check contents swap
    assert(a3.size() == 3);
    assert(a3.insert("4") && !b3.contains("4"));    //check that changing one doesn't change other
    assert(b3.insert("5") && !a3.contains("5"));
    
    
    //case 4: swapping two full sets
    Set a4, b4;
    assert(a4.insert("A") && a4.insert("B") && a4.insert("C"));
    assert(b4.insert("1") && b4.insert("2") && b4.insert("3") && b4.insert("4"));
    assert(a4.size() == 3 && b4.size() == 4);
    a4.swap(b4);    //swap full arrays of different sizes
    assert(b4.contains("A") && b4.contains("B") && b4.contains("C"));   //check contents are swapped
    assert(a4.contains("1") && a4.contains("2") && a4.contains("3") && a4.contains("4"));
    assert(a4.size() == 4 && b4.size() == 3);   //check sizes are swapped
    assert(a4.insert("5") && !b4.contains("5"));    //check that changing one does not change other
    assert(b4.insert("D") && !a4.contains("D"));
    
    
    
    
    //unite test cases
    //case 1: they all refer to the same set, result is empty
    Set xSrc1;
    Set* uP1;
    uP1 = &xSrc1;
    unite(xSrc1, xSrc1, xSrc1);
    assert(&xSrc1 == uP1 && xSrc1.empty()); //check that result is completely unchanged and address is same
    
    //case 2: s1 and s2 are the same set, result is empty
    Set xSrc2, uResult2;
    assert(xSrc2.insert("A") && xSrc2.insert("B") && xSrc2.insert("D"));
    unite(xSrc2, xSrc2, uResult2);
    assert(uResult2.contains("A") && uResult2.contains("B") && uResult2.contains("D")); //check contents
    assert(uResult2.size() == 3);
    assert(&uResult2 != &xSrc2); //check that src and result do not refer to same memory address
    
    //case 3: s1 and result are the same set
    Set xSrc3, ySrc3;
    assert(xSrc3.insert("A") && xSrc3.insert("E") && xSrc3.insert("I"));
    assert(ySrc3.insert("O") && ySrc3.insert("U"));
    unite(xSrc3, ySrc3, xSrc3);
    assert(xSrc3.contains("A") && xSrc3.contains("E") && xSrc3.contains("I")); //check original contents
    assert(xSrc3.contains("O") && xSrc3.contains("U")); //check new contents are present
    assert(xSrc3.size() == 5 && ySrc3.size() == 2); //check that other src is not changed
    
    //case 4: s2 and result are the same set
    Set xSrc4, ySrc4;
    assert(xSrc4.insert("AYE") && xSrc4.insert("WUS") && xSrc4.insert("POPPIN"));
    assert(ySrc4.insert("JIM") && ySrc4.insert("BO"));
    unite(xSrc4, ySrc4, ySrc4);
    assert(ySrc4.contains("AYE") && ySrc4.contains("WUS") && ySrc4.contains("POPPIN")); //check OG contents
    assert(ySrc4.contains("JIM") && ySrc4.contains("BO"));  //check that new contents are there
    assert(xSrc4.contains("AYE") && xSrc4.contains("WUS") && xSrc4.contains("POPPIN"));
    assert(!xSrc4.contains("JIM") && !xSrc4.contains("BO"));    //make sure contents of other are same
    assert(ySrc4.size() == 5 && xSrc4.size() == 3);
    
    //case 5: they are all unique sets, result is empty
    Set xSrc5, ySrc5;
    Set uResult5;
    assert(xSrc5.insert("So") && xSrc5.insert("you") && xSrc5.insert("think"));
    assert(ySrc5.insert("you're") && ySrc5.insert("a") && ySrc5.insert("comic"));
    unite(xSrc5, ySrc5, uResult5);
        //check that reuslt now holds contents of both but original contents of Srcs are same
    assert(uResult5.contains("So") && uResult5.contains("you") && uResult5.contains("think"));
    assert(uResult5.contains("you're") && uResult5.contains("a") && uResult5.contains("comic"));
    assert(xSrc5.size() == 3 && ySrc5.size() == 3 && uResult5.size() == 6);
    
    //case 6: they all refer to the same set, result has nodes
    Set xSrc6;
    assert(xSrc6.insert("stuff") && xSrc6.insert("more stuff") && xSrc6.insert("and other stuff"));
    unite(xSrc6, xSrc6, xSrc6);
    assert(xSrc6.contains("stuff") && xSrc6.contains("more stuff") && xSrc6.contains("and other stuff"));
    assert(xSrc6.size() == 3);
    
    //case 7: s1 and s2 are the same set, result has nodes
    Set xSrc7, uResult7;
    assert(uResult7.insert("this") && uResult7.insert("will be gone soon"));
    assert(uResult7.size() == 2);
    assert(xSrc7.insert("A") && xSrc7.insert("B") && xSrc7.insert("D"));
    unite(xSrc7, xSrc7, uResult7);
    assert(uResult7.contains("A") && uResult7.contains("B") && uResult7.contains("D")); //check contents
    assert(!uResult7.contains("this") && !uResult7.contains("will be gone soon"));
    assert(uResult7.size() == 3);
    assert(&uResult7 != &xSrc7); //check that src and result do not refer to same memory address
    
    
    //case 8: they are all unique sets, result has nodes
    Set xSrc8, ySrc8;
    Set uResult8;
    assert(uResult8.insert("i exist") && uResult8.insert("solely to be replaced"));
    assert(xSrc8.insert("So") && xSrc8.insert("you") && xSrc8.insert("think"));
    assert(ySrc8.insert("you're") && ySrc8.insert("a") && ySrc8.insert("comic"));
    unite(xSrc8, ySrc8, uResult8);
    //check that reuslt now holds contents of both but original contents of Srcs are same
    assert(uResult8.contains("So") && uResult8.contains("you") && uResult8.contains("think"));
    assert(uResult8.contains("you're") && uResult8.contains("a") && uResult8.contains("comic"));
    assert(xSrc8.size() == 3 && ySrc8.size() == 3 && uResult8.size() == 6);
    
    
    //subtract test cases
    
    //case 1: s1, s2, and result are the same empty set
    
    Set sub1s1;
    subtract(sub1s1, sub1s1, sub1s1);
    assert(sub1s1.empty());
    
    
    //case 2: s1, s2, and result are the same full set
    
    Set sub2s1;
    assert(sub2s1.insert("A") && sub2s1.insert("B") && sub2s1.insert("Z"));
    subtract(sub2s1, sub2s1, sub2s1);
    assert(sub2s1.empty()); // make sure set is now empty
    
    
    //case 3: s1 & s2 are the same set, result is empty
    
    Set sub3s1, sub3result;
    assert(sub3s1.insert("yah") && sub3s1.insert("yeet") && sub3s1.insert("aye"));
    assert(sub3s1.size() == 3);
    subtract(sub3s1, sub3s1, sub3result);
    assert(sub3s1.size() == 3 && sub3result.empty());
    assert(!sub3result.contains("yah") && !sub3result.contains("yeet") && !sub3result.contains("aye"));
    assert(sub3s1.contains("yah") && sub3s1.contains("yeet") && sub3s1.contains("aye"));
    
    
    //case 4: s1 & s2 are the same set, result has nodes
    
    Set sub4s1, sub4result;
    assert(sub4s1.insert("yah") && sub4s1.insert("yeet") && sub4s1.insert("aye"));
    assert(sub4result.insert("goodbye") && sub4result.insert("cruel") && sub4result.insert("world"));
    assert(sub4s1.size() == 3 && sub4result.size() == 3);
    subtract(sub4s1, sub4s1, sub4result);
    assert(sub4s1.size() == 3 && sub4result.empty());
    assert(!sub3result.contains("yah") && !sub3result.contains("yeet") && !sub3result.contains("aye"));
    assert(sub3s1.contains("yah") && sub3s1.contains("yeet") && sub3s1.contains("aye"));
    
    
    //case 5: s1 & s2 are different sets with nothing in common, result is empty
    
    Set sub5s1, sub5s2, sub5result;
    assert(sub5s1.insert("hoo") && sub5s1.insert("dee") && sub5s1.insert("who"));
    assert(sub5s2.insert("okokok") && sub5s2.insert("this aint chipotle"));
    subtract(sub5s1, sub5s2, sub5result);
    assert(sub5result.contains("hoo") && sub5result.contains("dee") && sub5result.contains("who"));
    assert(!sub5result.contains("okokok") && !sub5result.contains("this aint chipotle"));
    assert(sub5result.size() == 3 && sub5s1.size() == 3 && sub5s2.size() == 2);
    
    
    //case 6: s1 & s2 are different sets with nothing in common, result has nodes
    
    Set sub6s1, sub6s2, sub6result;
    assert(sub6result.insert("peace") && sub6result.insert("out"));
    assert(sub6s1.insert("hoo") && sub6s1.insert("dee") && sub6s1.insert("who"));
    assert(sub6s2.insert("okokok") && sub6s2.insert("this aint chipotle"));
    subtract(sub6s1, sub6s2, sub6result);
    assert(sub6result.contains("hoo") && sub6result.contains("dee") && sub6result.contains("who"));
    assert(!sub6result.contains("okokok") && !sub6result.contains("this aint chipotle"));
    assert(sub6result.size() == 3 && sub6s1.size() == 3 && sub6s2.size() == 2);
    
    
    //case 7: s1 & s2 are different sets with some items in common, result is empty
    
    Set sub7s1, sub7s2, sub7result;
    assert(sub7s1.insert("hoo") && sub7s1.insert("dee") && sub7s1.insert("who"));
    assert(sub7s2.insert("this aint chipotle") && sub7s2.insert("hoo"));
    subtract(sub7s1, sub7s2, sub7result);
    assert(sub7result.contains("dee") && sub7result.contains("who"));   //make sure result is correct
    assert(!sub7result.contains("hoo") && !sub7result.contains("this aint chipotle"));
    //make sure the sources still contain their sets
    assert(sub7s1.contains("hoo") && sub7s1.contains("dee") && sub7s1.contains("who"));
    assert(sub7s2.contains("hoo") && sub7s2.contains("this aint chipotle"));
    assert(sub7result.size() == 2 && sub7s1.size() == 3 && sub7s2.size() == 2);
    
    
    //case 8: s1 & s2 are different sets with some items in common, result has nodes
    
    Set sub8s1, sub8s2, sub8result;
    assert(sub8result.insert("bye bye") && sub8result.insert("miss american pie"));
    assert(sub8s1.insert("hoo") && sub8s1.insert("dee") && sub8s1.insert("who"));
    assert(sub8s2.insert("this aint chipotle") && sub8s2.insert("hoo"));
    subtract(sub8s1, sub8s2, sub8result);
    assert(sub8result.contains("dee") && sub8result.contains("who"));   //make sure result is correct
    assert(!sub8result.contains("hoo") && !sub8result.contains("this aint chipotle"));
    //make sure the sources still contain their sets
    assert(sub8s1.contains("hoo") && sub8s1.contains("dee") && sub8s1.contains("who"));
    assert(sub8s2.contains("hoo") && sub8s2.contains("this aint chipotle"));
    assert(sub8result.size() == 2 && sub8s1.size() == 3 && sub8s2.size() == 2);
    
    
    //case 9: s1 & s2 are different sets with identical items, result is mepty
    
    Set sub9s1, sub9s2, sub9result;
    assert(sub9s1.insert("1") && sub9s1.insert("2") && sub9s1.insert("4"));
    assert(sub9s2.insert("1") && sub9s2.insert("2") && sub9s2.insert("4"));
    subtract(sub9s1, sub9s2, sub9result);
    //make sure sources still have og constants
    assert(sub9s1.contains("1") && sub9s1.contains("2") && sub9s1.contains("4"));
    assert(sub9s2.contains("1") && sub9s2.contains("2") && sub9s2.contains("4"));
    assert(sub9result.empty()); // result should be empty
    
    
    //case 10: s1 & s2 are different sets with identical items, result has nodes
    
    Set sub10s1, sub10s2, sub10result;
    assert(sub10result.insert("8") && sub10result.insert("16") && sub10result.insert("32"));
    assert(sub10s1.insert("1") && sub10s1.insert("2") && sub10s1.insert("4"));
    assert(sub10s2.insert("1") && sub10s2.insert("2") && sub10s2.insert("4"));
    subtract(sub10s1, sub10s2, sub10result);
    //make sure sources still have og constants
    assert(sub10s1.contains("1") && sub10s1.contains("2") && sub10s1.contains("4"));
    assert(sub10s2.contains("1") && sub10s2.contains("2") && sub10s2.contains("4"));
    assert(sub10result.empty()); // result should be empty
           
    
    
    std::cout << "All tests passed" << std::endl;
}
