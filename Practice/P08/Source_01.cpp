#include <stdio.h>
#include <iostream>

using namespace std;

// example code P08
// stack, queue, and binary tree

#define max_size 100

// P08-01 stack
struct Stack
{
	int values[max_size];
	int size = 0;

	bool push(int element) {
		if (size == max_size) {
			return false; //Stack is already full
		}
		values[size] = element; //Add an element at the last
		size++;
		return true;
	}

	bool pop() {
		if (size == 0) {
			return false; //Stack is empty
		}
		size--; //Remove the last element
		return true;
	}

	void print() { //Print the elements in the stack
		cout << "Stack: ";
		for (int i = 0; i < size; i++) {
			cout << values[i] << " ";
		}
		cout << endl;
	}
};

//delete the number on the method name you want to run, and add one to the main methods you dont want to run
int main() {
	Stack stack = { {},0 };
	stack.push(1);
	stack.push(2);
	stack.push(3);
	stack.push(4);
	stack.print();
	stack.pop();
	stack.pop();
	stack.print();

	return 0;
}