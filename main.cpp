//  CC 273 DATA infixUCTURE 1 FinalProject Spring 2020

#include <iostream>
#include <string.h>
#include <string>
#include <stack>
#include <math.h>
#include <fstream>
#include <queue>

using namespace std;


bool checkPeriority (char a, char b)
{
    int aWeight, bWeight = 2;
    if ( a == '*' || a == '/' )
        aWeight = 2;
    else
        aWeight = 1;
    return aWeight >= bWeight;
}

bool isAnOperator(char a)
{
    if (a == '+' || a== '-' || a == '*' || a== '/') {
        return true;
    }
    else
        return false;
}

bool isNegative (char *x)
{
    if(x[0] == '-' && isdigit(x[1]))
        return true;
    else
        return false;
}

string infixToPostfix (string infix)
{
    string postfix;
    stack <char> stack;
    for (int i=0; i<infix.length(); i++)
    {
        if(isdigit(infix[i]) || infix[i] == '.')
        {
            postfix += infix[i];
            if (isAnOperator(infix[i+1]) || (infix[i+1] == '('))
            {
                postfix += " ";
            }
        }
        else if(infix[i] == '-' && isdigit(infix[i+1]) && stack.empty() && !isdigit(infix[i-1]))
        {
            postfix += infix[i];
            postfix += infix[i+1];
            if(!isdigit(infix[i+2]))
               postfix += " ";
            i=i+1;
        }
        else if(infix[i] == '*' && infix[i+1] == '-' && isdigit(infix[i+2]))
        {
            postfix += infix[i+1];
            postfix += infix[i+2];
            postfix += " ";
            postfix += '*';
            i=i+2;
        }
        else if (infix [i] == '(')
        {
            stack.push(infix[i]);
        }
        else if(isAnOperator(infix[i]))
        {
            if ( stack.empty() || stack.top() == '(' )
            {
                stack.push( infix[i] );
            }

            else if ( checkPeriority( infix[i], stack.top() ) )
            {
                stack.push( infix[i] );
            }

            else
            {
                postfix += " ";
                postfix += stack.top();
                postfix += " ";
                stack.pop();
                stack.push( infix[i] );
            }
        }
        else if ( infix[i] == ')' )
        {
            while ( stack.top() != '(' )
            {
                postfix += " ";
                postfix += stack.top();
                stack.pop();
            }
            if ( stack.top() == '(' )
                stack.pop();
        }
        if (infix[i] == ' ')
        {
            continue;
        }
    }
    while ( ! stack.empty() )
    {
        postfix += " ";
        if(stack.top() != '(')
            postfix += stack.top();
        stack.pop();
    }
    return postfix;
}

double evaluatePostfix(string postfix)
{
    double op1,op2;
    stack <double> stack;
    char p[postfix.length()];
    strcpy(p, postfix.c_str());
    char *token = strtok(p, " ");
    while(token != NULL)
    {
        if (isdigit(*token) || isNegative(token))
        {
            stack.push(atof(token));
        }
        else if(*token == '+')
        {
            op1 = stack.top();
            stack.pop();
            op2 = stack.top();
            stack.pop();
            stack.push(op1 + op2);
        }
        else if(*token == '-')
        {
            op1 = stack.top();
            stack.pop();
            op2 = stack.top();
            stack.pop();
            stack.push(op2 - op1);
        }
        else if(*token == '*')
        {
            op1 = stack.top();
            stack.pop();
            op2 = stack.top();
            stack.pop();
            stack.push(op1 * op2);
        }
        else if(*token == '/')
        {
            op1 = stack.top();
            stack.pop();
            op2 = stack.top();
            stack.pop();
            stack.push(op2 / op1);
        }
        else
        {
            cout << "WRONG OPERATORS! \n";
        }
        token = strtok(NULL, " ");
    }
    return stack.top();
}


int main()
{
    string s;
    cout << "WELCOME TO ANY NUMBERS INFIX TO POSTFIX EVALUATION: \n";
    cout << "----------------------------------------------------\n";
    cin >> s;
    string x = infixToPostfix(s);
    cout << "YOUR POSTFIX = " << x;
    cout << "\n";
    cout << "YOUR RESULT = " << evaluatePostfix(x);
    cout << "\n";
    
    return 0;
}
