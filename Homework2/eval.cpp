//
//  eval.cpp
//  Homework2
//
//  Created by Collin Prince on 2/2/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//

#include "Set.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>

using namespace std;



int precedence(char op);
bool ifToPf(string infix, string& postfix); //checks whether syntax is valid and converts to pf

int evaluate(string infix, const Set& trueValues, const Set& falseValues,
             string& postfix, bool& result)
{
    if (!ifToPf(infix, postfix))    //check syntax and create pf string
        return 1;   //return 1 for invalid expression
    
    stack <bool> operands;
    char current;   //this will be used to iterate through string
    for (int i = 0; i < postfix.size(); i++)
    {
        current = postfix[i];
        if (isalpha(current))
        {
            if (!trueValues.contains(current) && !falseValues.contains(current))    //neither contain the char
                return 2;
            else if (trueValues.contains(current) && falseValues.contains(current))  //both contain the char
                return 3;
            else if(trueValues.contains(current))   //if operand is true, push true on stack
                operands.push(true);
            else
                operands.push(false);   //else push false
            
        }
        else {
            if (current != '!')
            {
                if(operands.size() < 2)
                    return false;
                bool operand2, operand1;    //pop off operands into operand 2 & 1
                operand2 = operands.top();
                operands.pop();
                operand1 = operands.top();
                operands.pop();
                
                if (current == '&') //carry out operations
                    operands.push(operand1 && operand2);
                else //current is |
                    operands.push(operand1 || operand2);
            }
            else {
                if (operands.empty())
                    return false;
                bool operand = operands.top();  //if the operator is !, replace with opposite boolean
                operands.pop();
                operands.push(!operand);
            }
        }
    }
    
    if (operands.top()) //set result equal to the return value
        result = true;
    else
        result = false;
    return 0;
}

bool ifToPf(string infix, string& postfix)
{
    stack<char> ops;
    postfix = "";
    
    for (int i = 0; i < infix.size(); i++)
    {
        
        if (infix[i] == ' ') //erase spaces that pop up in infix
        {
            infix.erase(i, 1);
            i--;
            continue;
        }
        if (!islower(infix[i]) && infix[i] != '&'    //if character isn't a lowercase letter or op or paren
            && infix[i] != '|' && infix[i] != '!'
            && infix[i] != '(' && infix[i] != ')')
            return false;
        
        
        if (i == 0 && !islower(infix[i]) && infix[i] != '!' && infix[i] != '(')    //if start isn't a character or ! or (
            return false;
        
        //algo
        if (islower(infix[i]))
        {
            if (i > 0 && islower(infix[i-1]))   //if infix had multiple letters in a row, false
                return false;
            else if (i > 0 && infix[i-1] == ')') //if no op after paren and then a letter, false
                return false;
            postfix += infix[i];    //add letters
        }
        else if (infix[i] == '(')
        {
            if (i > 0 && (infix[i-1] != '!' && infix[i-1] != '&' && infix[i-1] != '|' && infix[i-1] != '('))
                return false;   //return false if there isn't an op before the paren after start
            ops.push(infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (!ops.empty() && ops.top() != '(')
            {
                postfix += ops.top();   //add operators until end of parentheses is reached
                ops.pop();
            }
            
            if (ops.empty())    //there was never a (, invalid string
                return false;
            ops.pop();  //pop off the other paren
        }
        else if (!(islower(infix[i]))) //if current char is an operator
        {
            if (infix[i] != '!')
            {
                if (!islower(infix[i-1]) && infix[i-1] != ')' && infix[i-1] != '!')   //if op isn't a !, then there should be an operand or ) b4 the operator
                    return false;
                if (i+1 >= infix.size())
                    return false;   //if string ends in an op, false
            }
            else {
                if (i+1 >= infix.size() || infix[i+1] == '&' || infix[i+1] == '|')
                    return false;   //if ! at end or in front of operator, return false
                if (i > 0 && islower(infix[i-1]))
                    return false;   //false if there is a letter then !
            }
            
            //need to look at this with respect to a ! in front of an operator
            while (!ops.empty() && ops.top() != '(' && precedence(infix[i]) <= precedence(ops.top()))
            {
                if (postfix.size() == 0 && infix[i] == '!') //if there are ! at start, break
                    break;
                if (i > 0 && infix[i] == '!' && (infix[i-1] == '&' || infix[i-1] == '|' ||infix[i-1] == '!'))
                    break;  //if there is a after an operator, then wait to apply this to it's operand
                postfix += ops.top();   //push op from stack onto post fix until end of paren or prec is <
                ops.pop();
            }
            ops.push(infix[i]); //push op on stack after looping
        }
        
    }
    while (!ops.empty())
    {
        if (ops.top() == '(')
            return false;   //if there are (, then there weren't enough ) in the infix to be valid;
        postfix += ops.top(); //add on leftover operators till empty
        ops.pop();
    }
    
    if(postfix.size() == 0)
        return false;
    
    return true;
}


int precedence (char op)    //precedence function sets ! to be 2, & to be 1, and | to be 0
{
    switch (op)
    {
        case '!':
            return 2;
        case '&':
            return 1;
        case '|':
            return 0;
    }
    return 0;
}


int main() {
    Set a;
    Set b;
    a.insert('u');
    a.insert('c');
    a.insert('l');
    a.insert('a');
    b.insert('n');
    b.insert('s');
    b.insert('f');
    b.insert('b');
    
    //Set a has true values ucla and b has false values nso
    
    //invalid string cases
    
    //case 1: capital letters
    string if1 = "A&C&F";
    string pf1;
    bool result1 = true;
    assert(evaluate(if1, a, b, pf1, result1) == 1 && result1 == true);
    
    //case 2: non operator non alphanumerics
    string if2 = "a&f}a";
    string pf2;
    bool result2 = true;
    assert(evaluate(if2, a, b, pf2, result2) == 1 && result2 == true);
    
    //case 3: operator at start
    string if3 = "&a|b";
    string pf3;
    bool result3 = true;
    assert(evaluate(if3, a, b, pf3, result3) == 1 && result3 == true);
    
    //case 4: wrong facing parentheses at start
    string if4 = ")a|f|c(";
    string pf4;
    bool result4 = true;
    assert(evaluate(if4, a, b, pf4, result4) == 1 && result4 == true);
    
    //case 5: wrong facing parenthes later
    string if5 = "a&f&)a|c(";
    string pf5;
    bool result5 = true;
    assert(evaluate(if5, a, b, pf5, result5) == 1 && result5 == true);
    
    //case 6: open paren without close
    string if6 = "a&(n|f";
    string pf6;
    bool result6 = true;
    assert(evaluate(if6, a, b, pf6, result6) == 1 && result6 == true);
    
    //case 7: close paren without open
    string if7 = "a&c|l)";
    string pf7;
    bool result7 = true;
    assert(evaluate(if7, a, b, pf7, result7) == 1 && result7 == true);
    
    //case 8: too many letters in a row
    string if8 = "ac&b";
    string pf8;
    bool result8 = false;
    assert(evaluate(if8, a, b, pf8, result8) == 1 && result8 == false);
    
    //case 9: operator at start
    string if9 = "&a&c";
    string pf9;
    bool result9 = true;
    assert(evaluate(if9, a, b, pf9, result9) == 1 && result9 == true);
    
    //case 10: opeartor at end
    string if10 = "a&c&";
    string pf10;
    bool result10 = true;
    assert(evaluate(if10, a, b, pf10, result10) == 1 && result10 == true);
    
    //case 11: ! at end
    string if11 = "a&c!";
    string pf11;
    bool result11 = true;
    assert(evaluate(if11, a, b, pf11, result11) == 1 && result11 == true);

    
    
    //tests for returns for sets
    //case 1: a character is in neither sets
    string ifret1 = "a&b|m";
    string pfret1;
    bool resret1 = true;
    assert(evaluate(ifret1, a, b, pfret1, resret1) == 2 && resret1 == true);
    
    //case 2: a character is in neither sets
    b.insert('u');   //temporarily insert u into our false set
    string ifret2 = "u&b";
    string pfret2;
    bool resret2 = true;
    assert(evaluate(ifret2, a, b, pfret2, resret2) == 3 && resret2 == true);
    
    b.erase('u');   //remove u again for our future tests
    
    
    //tests for actual boolean evaluation
    
    //case 1: standard & comparison to pf
    string inf1 = "a&b";
    string pof1;
    bool res1 = true;
    assert(evaluate(inf1, a, b, pof1, res1) == 0 && pof1 == "ab&" && res1 == false);
    
    //case 2: standard | comparison to pf
    string inf2 = "a|b";
    string pof2;
    bool res2 = false;
    assert(evaluate(inf2, a, b, pof2, res2) == 0 && pof2 == "ab|" && res2 == true);
    
    //case 3: ! at start
    string inf3 = "!a";
    string pof3;
    bool res3 = true;
    assert(evaluate(inf3, a, b, pof3, res3) == 0 && pof3 == "a!" && res3 == false);
    
    //case 4: () at start
    string inf4 = "(a&b)";
    string pof4;
    bool res4 = true;
    assert(evaluate(inf4, a, b, pof4, res4) == 0 && pof4 == "ab&" && res4 == false);
    
    //case 5: !() at start
    string inf5 = "!(a&b)";
    string pof5;
    bool res5 = false;
    assert(evaluate(inf5, a, b, pof5, res5) == 0 && pof5 == "ab&!" && res5 == true);
    
    //case 6: mix of & and |
    string inf6 = "a&b|c";
    string pof6;
    bool res6 = false;
    assert(evaluate(inf6, a, b, pof6, res6) == 0 && pof6 == "ab&c|" && res6 == true);
    
    //case 7: mix of & and !
    string inf7 = "!a&b";
    string pof7;
    bool res7 = true;
    assert(evaluate(inf7, a, b, pof7, res7) == 0 && pof7 == "a!b&" && res7 == false);
    
    //case 8: mix of &, |, and !
    string inf8 = "!a&b|c";
    string pof8;
    bool res8 = false;
    assert(evaluate(inf8, a, b, pof8, res8) == 0 && pof8 == "a!b&c|" && res8 == true);
    
    //case 9: mix of &, |, !, and ()
    string inf9 = "!(a|b)&c";
    string pof9;
    bool res9 = true;
    assert(evaluate(inf9, a, b, pof9, res9) == 0 && pof9 == "ab|!c&" && res9 == false);
    
    //case 10: test of ! coming immediately after an operator
    string inf10 = "a&!b";
    string pof10;
    bool res10 = true;
    assert(evaluate(inf10, a, b, pof10, res10) == 0 && res10 == true && pof10 == "ab!&");
    
    //case 11: test of ! coming immediately after operator and before parentheses
    string inf11 = "a&!(b&a|!b)";
    string pof11;   //pof = aba&b!|!&   --> false
    bool res11 = true;     //ops = &!
    assert(evaluate(inf11, a, b, pof11, res11) == 0 && res11 == false && pof11 == "aba&b!|!&");
    
    //test if pf is not empty
    string if12 = "(!!!!a&c)&!!!(a&a)";
    string pf12 = "I hope this isn't here in a second";
    bool something;
    //a!!!!c&aa&!!!&
    assert(evaluate(if12, a, b, pf12, something) == 0 && pf12 == "a!!!!c&aa&!!!&" && something == false);
    

    // testing test cases
    Set newTrue, newFalse;
    bool something2;
    assert(newTrue.insert('a') && newTrue.insert('e') && newTrue.insert('i') &&
           newTrue.insert('o') && newTrue.insert('u'));
    assert(newFalse.insert('b') && newFalse.insert('g') && newFalse.insert('k') &&
           newFalse.insert('p'));
    assert(evaluate("(o|k)u", newTrue, newFalse, pf12, something2) == 1);
    assert(evaluate("e!i", newTrue, newFalse, pf12, something2) == 1);
    
    
    //tests from spec
    Set fresh, freak;
    fresh.insert('u');
    fresh.insert('c');
    fresh.insert('l');
    fresh.insert('a');
    freak.insert('n');
    freak.insert('s');
    freak.insert('x');

    string pff;
    bool resultt;
    assert(evaluate("u", fresh, freak, pff, resultt) == 0 && resultt == true);
    assert(evaluate("u&c&l&a & !(u&s&c)", fresh, freak, pff, resultt) == 0 && resultt == true);
    assert(evaluate("(n)", fresh, freak, pff, resultt) == 0 && resultt == false);
    assert(evaluate("a&(s)", fresh, freak, pff, resultt) == 0 && resultt == false);
    assert(evaluate("a & !s", fresh, freak, pff, resultt) == 0 && resultt == true);
    assert(evaluate("!(n|u)", fresh, freak, pff, resultt) == 0 && resultt == false);
    assert(evaluate("!n|u", fresh, freak, pff, resultt) == 0 && resultt == true);
    assert(evaluate("a|n&n", fresh, freak, pff, resultt) == 0 && resultt == true);
    assert(evaluate("a&!(s|u&c|n)|!!!(s&u&n)", fresh, freak, pff, resultt) == 0 && resultt == true);
    
    cout << "All tests passed" << endl;
}
