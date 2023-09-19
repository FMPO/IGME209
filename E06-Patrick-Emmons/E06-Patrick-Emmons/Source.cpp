#include <stdio.h>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

#define MAXIMUM_SIZE 100

int adjacentMatrix[MAXIMUM_SIZE][MAXIMUM_SIZE] = { 0 }; // adjacent matrix used to save the graph
int size_node; // the number of nodes
int cardsPlayed = 0;

struct PlaySequence {
	int prerequisite;
	int card;
};
//The player needs to play prerequisite to play card.

// print the path by backwward traverse
void PrintPath(int* path, int initialCard, int targetCard) {
	cardsPlayed++;
	if (initialCard != targetCard)
		PrintPath(path, initialCard, path[targetCard]);
	cout << targetCard << " ";
	
}

// build the graph
void BuildGraph(int cardCount, int sequenceCount, PlaySequence* sequences) {
	size_node = cardCount;

	for (int i = 0; i < sequenceCount; i++) {
		adjacentMatrix[sequences[i].prerequisite][sequences[i].card] = 1;
	}
}

//Finialize this method. You may define new methods that are called by this method.
bool PlayCard(int initialCard, int targetCard) {

	queue<int> m_queue;
	m_queue.push(initialCard); // push the start point into the queue

	bool* visited = new bool[size_node] {false}; // the node has been visited
	visited[initialCard] = true;

	int* path = new int[size_node] {-1};

	cout << "Initial Card: " << initialCard << ". Target Card: " << targetCard << ". ";

	while (m_queue.empty() == false) {
		int nodeID = m_queue.front();  // get the first node of the queue
		m_queue.pop();

		if (nodeID == targetCard) { // found the targetCard
			cout << "Play Sequence: ";
			PrintPath(path, initialCard, targetCard);
			cout << endl;
			cout << "# of played card: " << cardsPlayed;

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

	cout << "Can't play target card" << endl;
	return false;

}


int main() {
	PlaySequence sequences[] = {
		{0, 2}, {6, 2}, {6, 8}, {0, 3}, {1, 0}, {2, 1},
		{5, 6}, {8, 5}, {8, 7}, {1, 3}, {1, 5}, {5, 9},
		{3, 4}, {4, 9}, {4, 1}, {5, 4}, {9, 0}, {7, 9}
	};
	int cardCount = 10;
	int sequenceCount = 18;

	BuildGraph(cardCount, sequenceCount, sequences);

	PlayCard(0, 9);

	return 0;
}