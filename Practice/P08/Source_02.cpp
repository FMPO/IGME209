#include <stdio.h>
#include <iostream>

using namespace std;

// example code P08
// stack, queue, and binary tree

#define max_size 100

// P08-02 queue
struct Queue
{
	int values[max_size];
	int size = 0;

	bool enqueue(int element) {
		if (size == max_size) {
			return false; //Queue is already full
		}
		values[size] = element; //Add an element at the last
		size++;
	}

	bool dequeue() {
		if (size == 0) {
			return false; //Queue is empty
		}
		for (int i = 0; i < size - 1; i++) { //Remove the first element
			values[i] = values[i + 1];
		}
		size--;
		return true;
	}

	void print() { //Print the elements in the queue
		cout << "Queue: ";
		for (int i = 0; i < size; i++) {
			cout << values[i] << " ";
		}
		cout << endl;
	}
};

struct LoopQueue // we can re-use the memory by loop queue， loop queue will not be tested in exercise or exam
{
	int values[max_size];
	int head = 0;
	int tail = 0;
	int size = 0;

	bool enqueue(int element) {
		if (size == max_size) {
			return false; //Queue is already full
		}
		values[tail] = element;  //Add an element at the last
		tail++;
		size++;
		if (tail >= max_size) { // loop to use the queue
			tail = 0;
		}
	}

	bool dequeue() {
		if (size == 0) {
			return false; //Queue is empty
		}
		head++;
		size--;
		if (head >= max_size) {
			head = 0; // loop to use the queue
		}
		return true;
	}

	void print() {  //Print the elements in the queue
		cout << "Loop Queue: ";
		for (int i = head, count = 0; count < size; i++, count++) {
			if (i >= max_size)
				i = 0;
			cout << values[i] << " ";
		}
		cout << endl;
	}
};

//delete the number on the method name you want to run, and add one to the main methods you dont want to run
int main2() {
	Queue queue = { {},0 };
	queue.enqueue(1);
	queue.enqueue(2);
	queue.enqueue(3);
	queue.enqueue(4);
	queue.print();
	queue.dequeue();
	queue.dequeue();
	queue.print();
	return 0;
}