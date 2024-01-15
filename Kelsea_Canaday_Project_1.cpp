/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

// Stack functions
#include <iostream>
#include <fstream>

using namespace std;

#define MAX 10000

class Stack {
	int top;

public:
	int a[MAX]; // Maximum size of Stack
	Stack() { top = -1; }
	bool push(int item);
	int pop();
	int peek();
	bool isEmpty();
};

bool Stack::push(int item)
{
	if (top >= (MAX - 1)) {
		cout << "Stack Overflow";
		return false;
	}
	else {
    top++;
		a[top] = item;
		//cout << item << " is successfully pushed into stack\n";
		return true;
	}
}

int Stack::pop()
{
	if (top < 0) {
		cout << "Stack Underflow";
		return 0;
	}
	else {
    
		int x = a[top];
    top--;
		return x;
	}
}
int Stack::peek()
{
	if (top < 0) {
		//cout << "Stack is Empty";
		return 0;
	}
	else {
		int x = a[top];
		return x;
	}
}

bool Stack::isEmpty()
{
	return (top < 0);
}

int BracketCheck(string expr)
{
	// Declare a stack to hold the opening brackets.
	class Stack openBracketStack;
	// Declare a stack that holds the index of the opening brackets
	class Stack indexStack;

	for (int i = 0; i < expr.length(); i++) {
		if(expr[i]=='('||expr[i]=='{'||expr[i]=='['){
		    // If there is an open bracket, it will be pushed to its respective stack
		    openBracketStack.push(expr[i]);
		    // For each open bracket, its (1-indexed) index is pushed to the index stack
			indexStack.push(i+1);
		}
		else if ((openBracketStack.peek() == '(' && (expr[i]==')')||(openBracketStack.peek() == '{' && (expr[i]=='}'))||(openBracketStack.peek() == '[' && (expr[i]==']')))){
			
			// If we found any complete pair of brackets, the open bracket stack will pop it out along with it's index as the proper bracket pair was validated
			openBracketStack.pop();
			indexStack.pop();
		}
		else if ((openBracketStack.peek() == '(' && (expr[i]==']'||expr[i]=='}')||(openBracketStack.isEmpty() && (expr[i]==')'||expr[i]=='}'||expr[i]==']')||(openBracketStack.peek() == '{' && (expr[i]==']'||expr[i]==')'))||(openBracketStack.peek() == '[' && (expr[i]==')'||expr[i]=='}'))))){
			return i+1;
		}
	}
	if (openBracketStack.isEmpty()) {
		// If stack is empty return Success
		return 0;
	}
	else{
	    //Otherwise return the index of the top opening bracket
	    int x = indexStack.pop();
	    return x;
	}
}

int main()
{
	string line;
	///Open up the allTexts test file
    ifstream myFile("allTexts.txt");
    
    if (myFile.is_open()) {
        while (getline(myFile, line)) {
        if(BracketCheck(line) == 0){ // Checks for success or a failure's index
            cout << "Success" << endl;
     }  else {
          cout << BracketCheck(line) << endl;
        }
    }
    myFile.close();
  }
	return 0;
}
