#pragma once
#include "Gem.h"
class BombGem : public Gem
{
public:
	BombGem();
	BombGem(int row, int column, RenderWindow* window);
	void draw(int column, int row);
	int getgemtype() { return 6; }
	~BombGem();
};

