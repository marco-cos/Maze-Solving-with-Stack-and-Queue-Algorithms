#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

 bool precEval(const stack<char> stck, const char operat);
 char funcEval(const char operand1, const char operand2, const char operat);

int evaluate(string infix, string& postfix, bool& result) {
	//If infix is a syntactically valid infix boolean expression,
	//   then set postfix to the postfix form of that expression, set
	//   result to the value of the expression, and return zero. If
	//   infix is not a syntactically valid expression, return 1; in
	//   that case, postfix may or may not be changed, but result must
	//   be unchanged.

	//Adjust infix to remove spaces
	string tempinfix;
	for (int i = 0; i < infix.length(); i++) {
		if (infix[i] != ' ')
			tempinfix += infix[i];
	}
	infix = tempinfix;
	

	//Checking syntax of paranthesis 
	string paranthesis = "";
	for (int i = 0; i < infix.length(); i++) { //Makes string of paranthesis in order
		if (infix[i] == '(') {

			if (i == infix.length() - 1) //Opening paranthesis at end case
				return 1;
			if ((infix[i + 1] == ')')|| (infix[i + 1] == '&') || (infix[i + 1] == '^')) //Empty pair of paranthesis AND incorrect operator after paranthesis case
				return 1;
			paranthesis += "(";
		}
		if (infix[i] == ')')
			paranthesis += ")";

		if (infix[i] == 't') //Make uncapatilized t and fs capitalized to allow further analysis 
			infix[i] = 'T';
		if (infix[i] == 'f')
			infix[i] = 'F';
		if (!(infix[i] == 'T' || infix[i] == 'F' || infix[i] == '^' || infix[i] == '&' || infix[i] == '!' || infix[i] == '(' || infix[i] == ')')) //check for illegal characters
			return 1;
	}

	int occurences = 1;
	while (occurences != 0) { //Iterates until a pair of paranthesis is no longer found, ensures paranthesis are syntatically correct and each opening paranthesis has a corresponding closed paranthesis
		occurences = 0;
		for (int i = 0; i < paranthesis.size(); i++) {
			if ((i > 0) && (paranthesis[i] == ')') && (paranthesis[i - 1] == '(')) { 
				paranthesis.erase(i - 1, 2); 
				i--;
				occurences++;
			}
		}

	}

	if (paranthesis.length() != 0) //If any paranthesis don't have matching paranthesis 
		return 1;

	//Infix to postfix
	postfix = "";
	stack<char> stck;
	for (char c : infix) { //Iterating for every character in infix
		switch (c) {

		case 'T': //Operand T case
			postfix += c;
			break;

		case 'F': //Operand F case
			postfix += c;
			break;

		case '(': //Open paranthesis case
			stck.push(c);
			break;
		
		case ')': //Close paranthesis case
			while (stck.top() != '(') {
				postfix += stck.top();
				stck.pop();
			}
			stck.pop();
			break;

		case '!': //! Operator case
			while ((!stck.empty() && (stck.top() != '('))&&(precEval(stck,c))) {
				postfix += stck.top();
				stck.pop();
			}
			stck.push(c);
			break;
		case '^': //^ Operator case
			while ((!stck.empty() && (stck.top() != '(')) && (precEval(stck, c))) {
				postfix += stck.top();
				stck.pop();
			}
			stck.push(c);
			break;
		case '&': //& Operator case
			while ((!stck.empty() && (stck.top() != '(')) && (precEval(stck, c))) {
				postfix += stck.top();
				stck.pop();
			}
			stck.push(c);
			break;

		}
	}

	//Emptying stack
	while (!stck.empty()) {
		postfix += stck.top();
		stck.pop();
	}
	
	//Evaluating postfix
	char operand2;
	char operand1;
	for (char c : postfix) {
		if ((c == 'F') || (c == 'T'))
			stck.push(c);
		else {
			if ((stck.size()>=2) && (c != '!')) { //Avoids undefined behavior in accessing a top that doesn't exist in a syntatically-incorrect notation
				operand2 = stck.top();
				stck.pop();
				operand1 = stck.top();
				stck.pop();
				stck.push(funcEval(operand1, operand2, c)); //Evaluates the expression assuming a pair
			}
			else if (c == '!') { //Evalues ! case, where only one operand is needed
				if (stck.top() == 'T') {
					stck.pop();
					stck.push('F');
				}
				else if (stck.top() == 'F') {
					stck.pop();
					stck.push('T');
				}
			}
			else { //If operator is attempting to be applied to one operand and it is not !, infix must not be well formated
				return 1;
			}
		}
	}

	//Final checks to return values 
	if ((stck.size() == 1) && (stck.top() == 'T')) {
		result = true;
		return 0;
	}
	if ((stck.size() == 1)&&(stck.top() == 'F')) {
		result = false;
		return 0;
	}
	else { //This else statement takes care of checking for remaining syntatic errors, as if it the infix was not well formated then size != 1 and/or top != T or F
		return 1;
	}
}

bool precEval(const stack<char> stck, const char operat) {
	//Returns true if precedence of passed in operator <= precedence of stack top

	if (stck.empty()) //Return if stack is empty to avoid undefined behavior 
		return true;
	char top = stck.top();

	switch (operat) {
	case '!': //! highest precedence, will be <= top if top is !
		if (stck.top() == '!')
			return true;
		else
			return false;
		break;

	case '&': //& second highest precedence, will be <= top if top isn't ^
		if (top == '^')
			return false;
		else
			return true;
		break;

	case '^': //^ Lowest precedence, will always be <= stack top 
		return true;
		break;

	}

	return false; //To avoid errors relating to not returning 
}

char funcEval(const char operand1, const char operand2, const char operat) {
	//Gets the result of one operator on two operands
	
	switch (operat) {
	case '!': //For operations with !, only operand1 is considered
		if (operand1 == 'T')
			return 'F';
		if (operand1 == 'F')
			return 'T';
		break;

	case '&': //For operations with &
		if ((operand1 == 'T') && (operand2 == 'T'))
			return 'T';
		else
			return 'F';
		break;
	
	case '^': //For operations with ||
		if ((operand1 == 'T' && operand2 == 'F') || (operand1 == 'F' && operand2 == 'T'))
			return 'T';
		else
			return 'F';
		break;

	}

	return 'F'; //To avoid errors relating to not returning 


}

