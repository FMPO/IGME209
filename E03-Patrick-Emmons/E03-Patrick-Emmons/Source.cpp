#include <iostream>
#include <vector>

using namespace std;

void swapValues(int* a, int* b) {
    //Write your code below
    //1. Swap Values
    int temp = 0;
    *a = temp;
    *a = *b;
    *b = temp;

    //Write your code above
}

int* removeElements(int* arr, int* size) {
    int* newArr; // The new array contains non-zero elements
    int newSize; // The size of the new array
    //Write your code below
    //2. Remove Elements

    newSize = 0;
    for (int i = 0; i < *size; i++) {
        if (*(arr + i) != 0) {
            newSize++;
        }
        
    }
    newArr = new int[newSize];
    int newI = 0;
    for (int i = 0; i < *size; i++) {
        if (*(arr + i) != 0) {
            newArr[newI] = arr[i];
            newI++;
            
        }

    }
    //Write your code above
    *size = newSize;
    return newArr;
}

vector<int> generateVector() {
    //Write your code below
    //3. Generate Vector
    vector<int> vectorArr;
    for (int i = 0; i < 100; i++) {
        vectorArr.push_back(i);

    }
    return vectorArr;
    //Write your code above
}

int main()
{
    int* a = new int(2);
    int* b = new int(4);
    cout << "1. Swap Values " << endl;
    cout << "Before Swapping: a = " << *a << ", b = " << *b << endl;
    swapValues(a, b);
    cout << "After Swapping: a = " << *a << ", b = " << *b << endl;
    delete a;
    delete b;

    int arr[] = { 0, 2, 0, 3, 3, 1, 2, 1, 2, 2, 2, 3, 1, 2, 2, 0, 2, 3, 0, 1, 1, 3, 1, 1, 2, 3, 3, 3, 0, 2, 3, 2, 2, 0, 3, 3, 1, 3, 2, 2, 0, 2, 3, 0, 0, 3, 1, 2, 2, 0, 1, 3, 3, 0, 1, 2, 3, 1, 0, 1, 0, 3, 1, 3, 3, 1, 0, 3, 3, 0, 3, 1, 3, 1, 2, 3, 0, 1, 2, 1, 2, 1, 1, 1, 0, 2, 3, 1, 1, 1, 3, 2, 3, 2, 2, 1, 1, 3, 2, 2 };
    int* size = new int(100);
    cout << "2. Remove Elements " << endl;
    cout << "Origin Array: ";
    for (int i = 0; i < *size; i++) {
        cout << *(arr + i) << " ";
    }
    cout << endl;
    int* newArr;
    newArr = removeElements(arr, size);
    cout << "New Array: ";
    for (int i = 0; i < *size; i++) {
        cout << *(newArr + i) << " ";
    }
    cout << endl;
    delete[] newArr;
    delete size;

    cout << "3. Generate Vector " << endl;
    vector<int> vec = generateVector();
    cout << "Vector: ";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    return 0;
}