#include <stdio.h>
#include <iostream>

using namespace std;

// example code P07
// dynamic programming algorithm

int values[5] = { 1, 20, 3, 5, 10 };
int weights[5] = { 2, 3, 4, 5, 6 };
const int item_n = 5;
const int maximum_w = 100;

// P07-01 01-knapsack recursion solution
int Knapsack_recursion(int i, int w) {
	if (i <= 0)
		return 0;
	else if (w < weights[i - 1])
		return Knapsack_recursion(i - 1, w);
	else
		return max(Knapsack_recursion(i - 1, w), Knapsack_recursion(i - 1, w - weights[i - 1]) + values[i - 1]);
}

// P07-02 01-knapsack dynamic programming solution
int Knapsack_dp(int W) {
	int dp[item_n + 1][maximum_w + 1] = { 0 };

	for (int i = 1; i <= item_n; i++) {
		for (int w = 0; w <= W; w++) {
			if (w - weights[i - 1] < 0) {
				dp[i][w] = dp[i - 1][w];
			}
			else
				dp[i][w] = max(dp[i - 1][w - weights[i - 1]] + values[i - 1], dp[i - 1][w]);
		}
	}
	return dp[item_n][W];
}

// P07-03 fibonnacci dynamic programming solution
int Fibonacci_dp(int n) {
	int* fib = new int[n + 1];
	fib[0] = 0;
	fib[1] = 1;
	for (int i = 2; i <= n; i++) {
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	return fib[n];
}

int main() {
	cout << "The 10th element of fibonacci is " << Fibonacci_dp(10) << endl;

	cout << "The maximum value in a knapsack of capacity 15 calculated by recursion is " << Knapsack_recursion(item_n, 15) << endl;
	cout << "The maximum value in a knapsack of capacity 15 calculated by dynamic programming is " << Knapsack_dp(15) << endl;

	return 0;
}