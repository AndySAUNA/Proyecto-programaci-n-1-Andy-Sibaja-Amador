#pragma once
#include "Gem.h"
class IceGem : public Gem
{
public:
	IceGem();
	IceGem(int row, int column, RenderWindow* window) : Gem(row, column, window) {}
	void draw(int column, int row);
	~IceGem();
};

	