#pragma once
#include <vector>
#include "Level.h"
class Object
{
public:
	Object();
	~Object();

	std::vector<Level::Triangle> faces;

	//void draw(double, double, double, GLuint);
};

