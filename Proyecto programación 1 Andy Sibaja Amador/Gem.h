#pragma once
#include <string>
#include <iostream>
using namespace std;

class Gem {
private:
	int postionx, postiony;
	int gemtype;
public:
	Gem(int positionx, int positiony) {
		this->postionx = positionx;
		this->postiony = positiony;
		gemtype = rand() % 5;
	}
	int setpositionx();
};