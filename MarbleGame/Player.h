#pragma once
#include <vector>

class Player
{
public:

	double x = 0, y = 3, z = 0, g = 0.2, s = 0.05, dx = 0, dy = 0, dz = 0, a = 0, f = 0.5; //x, y, z, gravity, speed, r;

	double accX = 0, accZ = 0;

	Player();
	~Player();

	void draw();
	void move(double, double, double, bool);
	void gravity(double, double, double, bool);
	void decelerate();
	//std::vector<std::vector<Level::Triangle>> animFaces;
	int myTex;
	double xAngle = 0;
	double zAngle = 0;
	double rotMatrix[3];
};

