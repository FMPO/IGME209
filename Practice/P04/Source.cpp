#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

// P04_01 array with pointer data type
void P04_01() {
    int** i_array = new int* [10];
    for (int i = 0; i < 10; i++) {
        i_array[i] = new int[i + 1];
        for (int j = 0; j < i + 1; j++)
            i_array[i][j] = j;
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < i + 1; j++)
            printf("%d ", i_array[i][j]);
        printf("\n");
    }
}

// P04-02 Structure
struct MyStructure {
    int i_var;
    float f_var;
    char c_var = 'a';
};

void P04_02() {
    MyStructure node;
    node.i_var = 10;
    node.f_var = 3.14f;

    printf("%d %f %c\n", node.i_var, node.f_var, node.c_var);

    MyStructure* node_ptr = new MyStructure();
    node_ptr->i_var = 12;
    node_ptr->f_var = 1.23f;

    printf("%d %f %c\n", node_ptr->i_var, node_ptr->f_var, node_ptr->c_var);
}

// P04-03 Linked List
struct Node { // node of linked list
    int i_var = 0;      // data
    Node* next = NULL;  // link to the next node
    Node() {
    }
    Node(int value) {
        i_var = value;
    }
};

Node* head_ptr;

void P04_03() {
    // create 3 nodes
    Node node0;
    node0.i_var = 0;
    Node node1 = Node(1);
    Node* node2_ptr = new Node(2);

    // create the link
    node0.next = &node1;
    node1.next = node2_ptr;
    node2_ptr->next = NULL;

    // set the head
    head_ptr = &node0;

    // using an iterator to print
    Node* iterator_ptr = head_ptr;
    while (iterator_ptr != NULL) {
        printf("%d->", iterator_ptr->i_var);
        iterator_ptr = iterator_ptr->next;
    }
    printf("NULL\n");
}

// P04_04 C++ standard library
void P04_04() {
    // iostream
    int i_var;
    float f_var;

    cout << "Input an integer and a float value: " << endl;
    cin >> i_var >> f_var;
    cout << i_var << "," << f_var << endl << endl;;


    // string 
    string str1 = "IGME";
    string str2 = "209";

    cout << "Combine two strings:" << endl;
    string str = str1 + "-" + str2;
    cout << str1 << "+" << str2 << "=" << str << endl << endl;


    // vector: dynamic array
    vector<int> i_array;
    i_array.push_back(1);
    i_array.push_back(2);
    i_array.push_back(3);

    cout << "Print the vector:" << endl;
    for (int i = 0; i < i_array.size(); i++)
        cout << i_array[i] << " ";
    cout << endl;

}

int main() {
    // P04_01();
    // P04_02();
    // P04_03();
     P04_04();
    return 0;
}