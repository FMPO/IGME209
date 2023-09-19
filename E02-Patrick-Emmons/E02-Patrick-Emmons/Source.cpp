#include <stdio.h>
#include <iostream>

void generateArray() {
    int arr[100] = { 0 };
    //Write your code below
    //1. Array

    for (int i = 0; i < 100; i++) {
        arr[i] = i;
    }

    //Write your code above

    for (int i = 0; i < 100; i++) {
        printf("%d ", arr[i]);
    }

    return;
}

void printAlphabet() {
    //Write your code below
    //2. Alphabet
    for (int i = 65; i <= 90; i++) {
        printf("%c ", i);
    }

    //Write your code above
}

void findNumber() {
    //Write your code below
    //3. Modulus
    for (int i = 1; i <= 100; i++) {
        if (i % 7 == 0) {
            printf("%d ", i);
        }
    }
    //Write your code above
}


int main()
{
    printf("1. Array: \n");
    generateArray();
    printf("\n");
    printf("2. Alphabet: \n");
    printAlphabet();
    printf("\n");
    printf("3. Modulus: \n");
    findNumber();
    printf("\n");

    system("pause");
    return 0;
}