#include <stdio.h>
#include <iostream>

using namespace std;

#define max_size 100

struct Stack
{
	char values[max_size]; // the data type stored in the stack is char 
	int size = 0;

	bool push(char element) {
		if (size == max_size) {
			return false; //Stack is already full
		}
		values[size] = element; //Add an element at the last
		size++;
		return true;
	}

	char pop() {
		if (size == 0) {
			return '0'; //Stack is empty
		}
		char element = values[size - 1];
		size--; //Remove the last element
		return element;
	}

	void print() { //Print the elements in the stack
		cout << "Stack: ";
		for (int i = 0; i < size; i++) {
			cout << values[i] << " ";
		}
		cout << endl;
	}
};


bool Solution(char* carr, int size) {
	Stack stack;

	// write your code blow

	for (int i = 0; i < size; i++) {
		if (carr[i] == '(' || carr[i] == '{') {
			stack.push(carr[i]);
		}
		else if (carr[i] == ')') {
			if (stack.values[stack.size-1] != '(') {
				return false;
			}
			stack.pop();
		}
		else if (carr[i] == '}') {
			if (stack.values[stack.size-1] != '{') {
				return false;
			}
			stack.pop();
		}
	}
	if (stack.size > 0) {
		return false;
	}
	return true;
	// write your code above
}

int main() {
	char carr1[] = "{(())}";
	cout << "Input: " << carr1 << ", Output: " << Solution(carr1, sizeof(carr1) / sizeof(char)) << endl;

	char carr2[] = "{}(";
	cout << "Input: " << carr2 << ", Output: " << Solution(carr2, sizeof(carr2) / sizeof(char)) << endl;

	char carr3[] = "(){}";
	cout << "Input: " << carr3 << ", Output: " << Solution(carr3, sizeof(carr3) / sizeof(char)) << endl;

	return 0;
}