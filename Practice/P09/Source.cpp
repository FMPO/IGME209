#include <stdio.h>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

struct Node {
	int value;
	Node* left;
	Node* right;

	Node(int v) {
		value = v;
		left = NULL;
		right = NULL;
	}
};

void Tree_Traversal_Recursion(Node* node) { // Depth first search
	if (node == NULL)
		return;
	cout << node->value << " ";
	Tree_Traversal_Recursion(node->left);
	Tree_Traversal_Recursion(node->right);
}

void Tree_Traversal_Stack(Node* root) { // Depth first search
	stack<Node*> m_stack;
	m_stack.push(root);
	while (m_stack.empty() == false) {
		Node* node = m_stack.top();
		m_stack.pop();
		if (node != NULL) {
			cout << node->value << " ";
			m_stack.push(node->right);
			m_stack.push(node->left);

			// how about change the order?
		}
	}
}

void Tree_Traversal_Queue(Node* root) { // Breadth first search
	queue<Node*> m_queue;
	m_queue.push(root);

	// get the first element: m_queue.front()
	// check if is empty: m_queue.empty()
	// remove the first element: m_queue.pop()


}

int main() {
	Node* root = new Node(0);
	Node* node1 = new Node(1);
	Node* node2 = new Node(2);
	Node* node3 = new Node(3);
	Node* node4 = new Node(4);
	Node* node5 = new Node(5);

	root->left = node1;
	root->right = node2;

	node1->left = node3;
	node1->right = node4;

	node4->right = node5;

	cout << "Tree traversal by recursion: ";
	Tree_Traversal_Recursion(root);
	cout << endl;

	cout << "Tree traversal by stack: ";
	Tree_Traversal_Stack(root);
	cout << endl;


	cout << "Tree traversal by queue: ";
	Tree_Traversal_Queue(root);
	cout << endl;

	return 0;
}