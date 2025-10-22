#pragma once
#include "Gem.h"
class BombGem : public Gem
{
public:
	BombGem();
	void draw(int column, int row);
	~BombGem();
};

