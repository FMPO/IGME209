#include <stdio.h>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

// P10 DFS and BFS on graph

#define MAXIMUM_SIZE 100

int adjacentMatrix[MAXIMUM_SIZE][MAXIMUM_SIZE] = { 0 }; // adjacent matrix used to save the graph
int size_node; // the number of nodes

// a road between two castles. The road is undirected, which means you can go either from castle1 to castle2 or castle2 to castle1
struct Road {
	int castle1;
	int castle2;
};

// build the graph
// n is the number of castles
// m is the number of roads
// roads is the array of Road
void BuildGraph(int n, int m, Road* roads) {
	// write your code below
	size_node = n;

	for (int i = 0; i < m; i++) {
		adjacentMatrix[roads[i].castle1][roads[i].castle2] = 1;
	}
	// write your code above
}

// print the path by backwward traverse
void PrintPath(int* path, int source, int destination) {
	if (source != destination)
		PrintPath(path, source, path[destination]);
	cout << destination << " ";
}

bool SearchBFS(int source, int destination) {
	queue<int> m_queue;
	m_queue.push(source); // push the start point into the queue

	bool* visited = new bool[size_node] {false}; // the node has been visited
	visited[source] = true;

	int* path = new int[size_node] {-1};

	while (m_queue.empty() == false) {
		int nodeID = m_queue.front();  // get the first node of the queue
		m_queue.pop();

		if (nodeID == destination) { // found the destination
			cout << "Path from " << source << " to " << destination << " is ";
			PrintPath(path, source, destination);
			cout << endl;

			delete[] visited;
			delete[] path;

			return true;
		}

		// push all adjacent nodes into the queue if not visited
		for (int i = 0; i < size_node; i++) {
			if (adjacentMatrix[nodeID][i] != 0 && visited[i] == false) {
				m_queue.push(i);
				visited[i] = true;
				path[i] = nodeID;
			}
		}
	}

	// no path found
	delete[] visited;
	delete[] path;

	cout << "No path found from " << source << " to " << destination << endl;
	return false;
}

// n: n castles
// m: m roads between the castles
// roads: the roads between the castles, the size is m
// source: the source castle
// destination: the destination castle, we want to check if there is a path between the source and destination
// k: k possible plans to build the roads
// roads_plan: the possible plans to build the roads, the size is k, each plan is a road between two castles,
// roads_plan: the cost of each plan, the size is k
// you are free to define new functions and call them in Solution() if you need
void Solution(int n, int m, Road* roads, int source, int destination,
	int k, Road* roads_plan, int* cost_array) {

	BuildGraph(n, m, roads);

	// write your code below
	// 1. Check and print if there exists a path between source to destination
	// 2. If it exists, print the path
	// 3. If not, for the k plans, check and print if there exists a path after building the road
	// 4. Print the valid plan with the minimum cost
	int minCost = 100;
	int minIndex = -1;

	if (SearchBFS(source, destination) == true) {
		return;
	}
	else {
		for (int i = 0; i < k; i++) {
			cout << "If build a road between" << roads_plan[i].castle1 << " and " << roads_plan[i].castle2 << " with cost " << cost_array[i] << ": ";
			adjacentMatrix[roads_plan[i].castle1][roads_plan[i].castle2] = 1;
			if (SearchBFS(source, destination) == true && cost_array[i] < minCost) {
				minCost = cost_array[i];
				minIndex = i;
			}
			adjacentMatrix[roads_plan[i].castle1][roads_plan[i].castle2] = 0;
		}
		cout << "To connect " << source << " and " << destination << ", the minimum cost is " << minCost << " by building a road between " << roads_plan[minIndex].castle1 << " and " << roads_plan[minIndex].castle2;
	}
	
	

	// write your code above
}

int main() {
	// test case
	int n = 5; // we have 5 castles
	int m = 3; // we have 3 roads
	Road roads[3] = { {0, 1}, {0, 2}, {3, 4} }; // the 3 roads are (0,1), (0,2), and (3,4)

	int source = 0; // we start from castle 0
	int destination = 4; // the destination is castle 4

	int k = 3; // we have 3 possible plans
	Road roads_plan[3] = { {0, 3}, {1, 2}, {2, 4} }; // the 3 plans are build a new road between (0, 3), (1, 2), and (2, 4)
	int cost_array[3] = { 10, 2, 5 }; // the cost of 3 plans are 10, 2, and 5

	Solution(n, m, roads, source, destination, k, roads_plan, cost_array);

	return 0;
}

