#include <stdio.h>
#include <iostream>
#include <queue>

using namespace std;

int map[10][10] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 0, 0, 1, 0, 0 },
		{ 0, 0, 1, 0, 1, 1, 1, 1, 0, 0 },
		{ 0, 1, 1, 0, 0, 0, 0, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 0, 1, 0, 0 },
		{ 0, 0, 1, 0, 1, 0, 0, 1, 0, 0 },
		{ 0, 0, 1, 0, 1, 0, 0, 1, 0, 0 },
		{ 0, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 }
};

struct Vector2
{
	int x;
	int y;

	Vector2(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

void printDistance(Vector2 source) {
	if (source.x < 0 || source.x >= 10 || source.y < 0 || source.y >= 10) {
		cout << "Index out of range!" << endl;
		return;
	}
	if (map[source.x][source.y] == 1) {
		cout << "Source is blocked" << endl;
		return;
	}
	cout << "Source: " << source.x << ", " << source.y << endl;

	int const offset_x[4] = { -1, 1, 0, 0 }; // up down left right
	int const offset_y[4] = { 0, 0, -1, 1 }; // up down left right

	int result[10][10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			result[i][j] = -1; // set all the initial distance as -1, which means the location is not walkable
		}
	}
	result[source.x][source.y] = 0; // set the distance from source to itself = 0

	// write your code below
	queue<Vector2> q;
	q.push(source);

	while (!q.empty()) {
		Vector2 current = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int new_x = current.x + offset_x[i];
			int new_y = current.y + offset_y[i];

			if (new_x >= 0 && new_x < 10 && new_y >= 0 && new_y < 10 && map[new_x][new_y] == 0 && result[new_x][new_y] == -1) {
				result[new_x][new_y] = result[current.x][current.y] + 1;
				q.push(Vector2(new_x, new_y));
			}
		}
	}
	// write your code above

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (result[i][j] >= 0) {
				if (result[i][j] >= 10) {
					cout << result[i][j] << " ";
				}
				else {
					cout << " " << result[i][j] << " ";
				}
			}
			else {
				cout << "++ ";
			}
		}
		cout << endl;
	}
}

int main()
{
	Vector2 source1 = Vector2(0, 0);
	printDistance(source1);
	cout << endl;
	Vector2 source2 = Vector2(9, 9);
	printDistance(source2);
	cout << endl;
	Vector2 source3 = Vector2(4, 5);
	printDistance(source3);
	// Thanks for playing! Don't forget to Roman Cancel out of this maze!
	return 0;
}