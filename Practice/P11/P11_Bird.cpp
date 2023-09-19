#include <stdio.h>
#include <iostream>

using namespace std;

class Bird {
protected:
	string name;
public:
	// Encapsulation
	void SetName(string _name) { // write-only access
		name = _name;
	}
	string GetName() { // read-only access
		return name;
	}
public:
	Bird() {
	}
	~Bird() {}
	Bird(string _name) {
		name = _name;
	}
	virtual void Sing() {
		cout << "(" << typeid(*this).name() << ") " << name << " sings Cheep Cheep" << endl;
	}
};

class Duck : public Bird { // inheritance
public:
	Duck(string _name) :Bird(_name) {
	}
	void Sing() override {
		cout << "(" << typeid(*this).name() << ") " << name << " sings Quack Quack" << endl;
	}
	void Swim() {
		cout << "(" << typeid(*this).name() << ") " << name << " is swimming" << endl;
	}
};

class Chicken : public Bird { // inheritance
public:
	Chicken(string _name) :Bird(_name) {
	}
	void Sing() override {
		cout << "(" << typeid(*this).name() << ") " << name << " sings Cluck Cluck" << endl;
	}
};

int main() {
	Bird bird1 = Bird("GG");
	bird1.Sing();
	bird1.SetName("A");
	bird1.Sing();

	Duck duck = Duck("B");
	duck.Sing();
	duck.Swim();


	// polymorphism 
	Bird* bird3_ptr = new Duck("C");
	bird3_ptr->Sing();

	Bird* birdArray[4];
	birdArray[0] = &bird1;
	birdArray[1] = &duck;
	birdArray[2] = bird3_ptr;
	birdArray[3] = new Chicken("D");

	for (int i = 0; i < 4; i++) {
		cout << "Bird " << i << ":";
		birdArray[i]->Sing();
	}

	((Duck*)birdArray[1])->Swim();

	return 0;

}