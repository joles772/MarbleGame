#include "player.h"
#include <freeglut.h>
#include <SOIL.h>
#include <math.h>

GLUquadricObj *sphere = NULL;

bool myTexGot = false;

Player::Player()
{
	rotMatrix[0] = 0;
	rotMatrix[1] = 0;
	rotMatrix[2] = 0;
	sphere = gluNewQuadric();

	gluQuadricDrawStyle(sphere, GLU_FILL);

	gluQuadricTexture(sphere, GL_TRUE);

	gluQuadricNormals(sphere, GLU_SMOOTH);
}


Player::~Player()
{
}

void Player::draw(){

	if (xAngle > 360) xAngle = 0;
	else if (xAngle < 0) xAngle = 360;
	if (zAngle > 360) xAngle = 0;
	else if (zAngle < 0) xAngle = 360;

	glBindTexture(GL_TEXTURE_2D, myTex);

	if (myTexGot == true);
	glColor3f(1, 1, 1);
	glTranslatef(Player::x, Player::y, Player::z);

	double rotateX = rotMatrix[0];
	double rotateZ = rotMatrix[2];
	double myAngle = xAngle;


	glRotatef(myAngle, rotateX, 0, rotateZ);

	gluSphere(sphere, 1.0, 100, 100);

	glRotatef(myAngle, -rotateX, 0, -rotateZ);

	glTranslatef(-Player::x, -Player::y, -Player::z);
}

void Player::decelerate(){
	/*double factor = 0.5;

	if(accX > 0) accX -= factor;
	else if (accX < 0) accX += factor;
	if(accZ > 0) accZ -= factor;
	else if(accZ < 0) accZ += factor;

	if (accX > -1 && accX < 1) accX = 0;
	if (accZ> -1 && accZ < 1) accZ = 0;*/

	if (a > 0) a = a - 0.001;
}

void Player::move(double inX, double inY, double inZ, bool freeRoll){

	dx = x;
	dz = z;

	x = x + inX*(s + a);
	z = z + inZ*(s + a);


	if(a < 0.1) a = a + 0.0005;
}

void Player::gravity(double inX, double inY, double inZ, bool freeRoll){

	dx = x;
	dy = y;
	dz = z;

	x = x + inX* (g);
	y = y + inY*(g);
	z = z + inZ*(g);

	//if (a < 0.2) a = a + 0.005;
}

