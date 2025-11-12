#pragma once
#include "Gem.h"
class NormalGem : public Gem
{
public:
	NormalGem();
	NormalGem(int row, int column, RenderWindow* window);
	void draw(int row, int column);
	int getgemtype() { return gemtype; }
};

