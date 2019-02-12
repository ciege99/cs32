//
//  cs32Tests.cpp
//  Homework2
//
//  Created by Collin Prince on 2/3/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//



#include "Set.h"  // with ItemType being a type alias for char
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


int main()
{
    string trueChars  = "tywz";
    string falseChars = "fnx";
    Set trues;
    Set falses;
    for (int k = 0; k < trueChars.size(); k++)
        trues.insert(trueChars[k]);
    for (int k = 0; k < falseChars.size(); k++)
        falses.insert(falseChars[k]);
    
    string pf;
    bool answer;
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  answer);
    assert(evaluate("y|", trues, falses, pf, answer) == 1);
    assert(evaluate("n t", trues, falses, pf, answer) == 1);
    assert(evaluate("nt", trues, falses, pf, answer) == 1);
    assert(evaluate("()", trues, falses, pf, answer) == 1);
    assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
    assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
    assert(evaluate("(n&(t|7)", trues, falses, pf, answer) == 1);
    assert(evaluate("", trues, falses, pf, answer) == 1);
    assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
           &&  pf == "ff!tn&&|"  &&  !answer);
    assert(evaluate(" x  ", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  !answer);
    trues.insert('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 3);
    falses.erase('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  answer);
    trues.erase('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 2);
    falses.insert('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  !answer);
    cout << "Passed all tests" << endl;
    }
