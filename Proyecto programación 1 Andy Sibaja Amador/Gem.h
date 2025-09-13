#pragma once
#include <string>
#include <iostream>
using namespace std;

class Gem {
private:
	int positionx, positiony;
	int gemtype;
public:
	Gem(int positionx, int positiony) {
		this->positionx = positionx;
		this->positiony = positiony;
		gemtype = rand() % 5;
	}
	int setpositionx(int positionx) { this->positionx = positionx; }
	int setpositiony(int positiony) { this->positiony = positiony; }

};