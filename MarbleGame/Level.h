#pragma once

#include "Player.h"
#include <vector>
#include <freeglut.h>
//#include <freeglut.h>

class Level
{
private:
	//void loadObj(std::vector<Triangle>,const char*);

public:

	typedef struct{
		double x, y, z, tx, ty;
	} Point;

	typedef struct{
		Point p1, p2, p3, n;
		int t;
	} Triangle;

	Player *player;

	enum dir
	{
		LEFT, RIGHT, UP, DOWN, GRAVITY
	};

	Level();
	~Level();
	virtual void draw(int, double, double, double);
	void collision(double, double, double);
	void setPlayer(Player &);
	void move(double, double, double);
	//GLuint loadTex(const char*);
	void drawStuff();
	void getRes();
	void loadObj(std::vector<Level::Triangle> &, const char*);
	GLuint loadTex(const char*);

	std::vector<Level::Triangle>* Level::getFaces();

	std::vector<Level::Triangle>* Level::getObjectFaces(int i);

	GLuint* getTextures(int);

	int getMaterialCount();
	void resizeObjectFaces();

	void resizeTextures();
	double getPX();
	double getPY();
	double getPZ();

	void gravity();

	void addSolid(Point, Point, Point, Point);
	void removeSolid(int i);
	void removeSolid();

	bool canMove = true;
};

