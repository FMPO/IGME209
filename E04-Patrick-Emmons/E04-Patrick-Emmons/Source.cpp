#include <stdio.h>
#include <iostream>

using namespace std;

int FrogJump(int n) {
	//Write your code below
	//1. Frog Jump
	if (n == 1) {
		return 1;
	}
	if (n == 2) {
		return 2;
	}
	if (n == 3) {
		return 4;
	}
	return FrogJump(n - 3) + FrogJump(n - 2) + FrogJump(n - 1);

	//Write your code above
}

int CalculateArray(int* arr, int n) {
	//Write your code below
	//2. Calculate Array
	if (n < 0) {
		cout << "Error message" << endl;
		return -1;
	}
	else if (n == 0) 
	{
		return arr[n]*2;
	}
	else if ((n % 2) == 0)
	{
		return CalculateArray(arr, n - 1) + (arr[n]*2);
	}
	else 
	{
		return CalculateArray(arr, n - 1) + (arr[n] + 3);
	}
		
	//Write your code above
}

int SumDigits(int n) {
	//Write your code below
	//3. Sum Digits
	if (n == 0) {
		return 0;
	}
	else {
		return (n % 10 + SumDigits(n / 10));
	}

	//Write your code above
}


int main() {
	//1. Frog Jump
	int stair = 11;
	cout << "Frog jump up " << stair << " stairs = " << FrogJump(stair) << endl;

	//2. Calculate Array
	int* arr = new int[50] { 69, 132, 197, 25, 87, 48, 187, 130, 183, 80, 2, 190, 26, 79, 101, 132, 110, 10, 64, 92, 182, 153, 71, 37, 147, 73, 87, 57, 170, 181, 165, 176, 199, 183, 138, 20, 193, 98, 175, 176, 77, 34, 134, 19, 17, 87, 3, 3, 160, 21 };
	cout << "Calculate array = " << CalculateArray(arr, 49) << endl;

	//3. Sum Digits
	int number = 51523907;
	cout << "Sum digits of " << number << " = " << SumDigits(number) << endl;

	return 0;
}