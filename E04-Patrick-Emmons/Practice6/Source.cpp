#include <stdio.h>
#include <iostream>

using namespace std;

// example code P06
// recursion algorithm

int Sum(int* arr, int n) {
	if (n < 0) {
		cout << "Error message" << endl;
		return -1;
	}
	else if (n == 0)
		return arr[n];
	else
		return Sum(arr, n - 1) + arr[n];
}

int Factorial(int n) {
	if (n < 1) {
		cout << "Error message" << endl;
		return -1;
	}
	else if (n == 1) {
		return 1;
	}
	else
		return Factorial(n - 1) * n;
}

int Fibonacci(int n) {
	if (n < 0) {
		cout << "Error message" << endl;
		return -1;
	}
	else if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return Fibonacci(n - 2) + Fibonacci(n - 1);
}

int FrogJump(int n) {
	if (n == 1)
		return 1;
	if (n == 2)
		return 2;
	return FrogJump(n - 2) + FrogJump(n - 1);
}

bool BashGame(int n) {
	if (n == 0)
		return false;
	if (n == 1)
		return true;
	if (n == 2)
		return true;
	else
		return (!BashGame(n - 1)) || (!BashGame(n - 2));
}

int BinarySearch(int* arr, int value, int low, int high) {
	if (low > high)
		return -1;
	else {
		int mid = (low + high) / 2;
		if (value == arr[mid])
			return mid;
		else if (value < arr[mid])
			return BinarySearch(arr, value, low, mid - 1);
		else
			return BinarySearch(arr, value, mid + 1, high);
	}
}

// sum
void P06_01() {
	int* arr = new int[10] { 1, 5, 7, 12, 15, 18, 20, 50, 78, 100 };
	cout << "Sum of the array = " << Sum(arr, 9) << endl;
}

// Factorial
void P06_02() {
	int n = 10;
	cout << "Fibonacci(" << n << ") = " << Fibonacci(n) << endl;
}

// Fibonacci
void P06_03() {
	int n = 10;
	cout << "Factorial of " << n << " = " << Factorial(10) << endl;
}

// Frog Jump
void P06_04() {
	int n = 10;
	cout << "Jump up " << n << " stairs = " << FrogJump(n) << endl;
}

// Binary Search
void P06_05() {
	int* arr = new int[10] { 1, 5, 7, 12, 15, 18, 20, 50, 78, 100 };
	int valueToSearch = 7;

	cout << "The position of given integer in the array is " << BinarySearch(arr, valueToSearch, 0, 9) << endl;
}

// Bash Game
void P06_06() {
	int n = 10;
	if (BashGame(n))
		cout << "Who plays first win with the number of " << n << endl;
	else
		cout << "Who plays first lose with the number of " << n << endl;

	//for (int i = 0; i < 10; i++) {
	//	cout << "(" << i << ": " << BashGame(i) << "), ";
	//}
}

int main() {

	int type = 1;
	cout << "Input the id of the practice you want to print: ";
	cin >> type;

	switch (type) {
	case 1:
		P06_01(); break;
	case 2:
		P06_02(); break;
	case 3:
		P06_03(); break;
	case 4:
		P06_04(); break;
	case 5:
		P06_05(); break;
	case 6:
		P06_06(); break;
	default:
		cout << "no practice with the input id" << endl;
	}

	return 0;
}