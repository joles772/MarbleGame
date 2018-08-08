#pragma once
#include "Level.h"

class Level1 :
	public Level
{
public:
	Level1();
	~Level1();

	void getRes();
	void draw(int, double, double, double);
	void checkListeners();
};

