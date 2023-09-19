#include <stdio.h>
#include <iostream>

using namespace std;

// example code P08
// stack, queue, and binary tree

// P08-03 binary tree
struct Node {
	int value = 0;
	Node* left = NULL;
	Node* right = NULL;

	Node() {

	}

	Node(int v) {
		value = v;
	}
};

//delete the number on the method name you want to run, and add one to the main methods you dont want to run
int main3() {
	Node* root = new Node(0);
	Node* node1 = new Node(1);
	Node* node2 = new Node(2);//0
	root->left = node1;//      / \ 
	root->right = node2;//    1   2  | 1 and 2 are the children of 0

	Node* node3 = new Node(3);
	Node* node4 = new Node(4);//1
	node1->left = node3;//     / \ 
	node1->right = node4;//   3   4  | 3 and 4 are the children of 1

	Node* node5 = new Node(5);
	Node* node6 = new Node(6);//2
	node2->left = node5;//     / \ 
	node2->right = node6;//   5   6  | 5 and 6 are the children of 2

	//Visualize: 
	//           0
	//         /   \ 
	//        1     2
	//       / \   / \
	//      3   4 5   6

	// how to print (traverse) a tree? We will learn the method in next lecture. 

	return 0;
}