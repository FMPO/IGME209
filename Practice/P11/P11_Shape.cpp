#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

#define PI 3.1415926

class Shape {
public:
	virtual float Area() = 0; // pure virtual function
};

class Circle : public Shape {
private:
	float radius = 0.0f;
public:
	Circle(float _radius) {
		radius = _radius;
	}
	float Area() override {
		return PI * radius * radius;
	}
};

class Square : public Shape {
private:
	float side_length = 0.0f;
public:
	Square(float _side_length) {
		side_length = _side_length;
	}
	float Area() override {
		return pow(side_length, 2);
	}
};

//delete the number on the method name you want to run, and add one to the main methods you dont want to run
int main3() {
	Shape* shape1 = new Circle(1.0f);
	Shape* shape2 = new Square(2.0f);

	// Shape* shape3 = new Shape(); // this is not allowed, because Shape is an abstract class

	cout << shape1->Area() << endl;
	cout << shape2->Area() << endl;
	return 0;
}