#pragma once
#include "Level.h"
class Lightning
{
public:
	Lightning();
	~Lightning();

	void draw();
	void makeBolt();

	std::vector<std::vector<Level::Point>> bolt;
	int myTex;
};

