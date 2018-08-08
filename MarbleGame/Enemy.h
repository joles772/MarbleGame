#pragma once
#include "Level.h"
class Enemy
{
public:
	Enemy();
	~Enemy();
	void move();
	void attack();
	void draw();

	Level::Point b;
	Level::Point b2;

	std::vector<std::vector<Level::Triangle>> animFaces;
};

