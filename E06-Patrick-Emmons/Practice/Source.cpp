#include <stdio.h>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

// P10 DFS and BFS on graph

#define MAXIMUM_SIZE 100

int adjacentMatrix[MAXIMUM_SIZE][MAXIMUM_SIZE] = { 0 }; // adjacent matrix used to save the graph
int size_node; // the number of nodes

// build the graph
void BuildGraph() {
	size_node = 9; // set the number of nodes

	adjacentMatrix[0][1] = 1;

	adjacentMatrix[1][2] = 1;
	adjacentMatrix[1][3] = 1;
	adjacentMatrix[1][4] = 1;

	adjacentMatrix[2][0] = 1;
	adjacentMatrix[2][6] = 1;

	adjacentMatrix[3][7] = 1;

	adjacentMatrix[4][5] = 1;

	adjacentMatrix[5][7] = 1;

	adjacentMatrix[6][5] = 1;

	adjacentMatrix[7][6] = 1;

	adjacentMatrix[8][5] = 1;
}

// print the path by backwward traverse
void PrintPath(int* path, int source, int destination) {
	if (source != destination)
		PrintPath(path, source, path[destination]);
	cout << destination << " ";
}

// check if exist a path or not by DFS
// if true, print the path
bool PathFindingDFS(int source, int destination) {
	stack<int> m_stack;
	m_stack.push(source); // push the start point into the stack

	bool* visited = new bool[size_node] {false}; // the node has been visited
	visited[source] = true;

	int* path = new int[size_node] {-1}; // array used to save the path

	while (m_stack.empty() == false) {
		int nodeID = m_stack.top(); // get the top node of the stack
		m_stack.pop();

		if (nodeID == destination) { // found the destination
			cout << "Path from " << source << " to " << destination << " :";
			PrintPath(path, source, destination);
			cout << endl;

			delete[] visited;
			delete[] path;

			return true;
		}

		// push all adjacent nodes into the stack if not visited
		for (int i = 0; i < size_node; i++) {
			if (adjacentMatrix[nodeID][i] != 0 && visited[i] == false) {
				m_stack.push(i);
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

// check if exist a path or not by BFS
// if true, print the path
bool PathFindingBFS(int source, int destination) {
	queue<int> m_queue;
	m_queue.push(source); // push the start point into the queue

	bool* visited = new bool[size_node] {false}; // the node has been visited
	visited[source] = true;

	int* path = new int[size_node] {-1};

	while (m_queue.empty() == false) {
		int nodeID = m_queue.front();  // get the first node of the queue
		m_queue.pop();

		if (nodeID == destination) { // found the destination
			cout << "Path from " << source << " to " << destination << " :";
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

int main() {
	BuildGraph();

	PathFindingDFS(0, 7);
	PathFindingBFS(0, 7);

	PathFindingDFS(0, 8);
	PathFindingBFS(0, 8);

	return 0;
}