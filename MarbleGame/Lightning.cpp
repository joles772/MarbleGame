#include "Lightning.h"
#include <string>
#include <vector>
#include <SOIL.h>
#include <freeglut.h>

int part = 0;
int count = 0;
int factor = 2;

double myRand(double min, double max)
{
	double f = (double)rand() / RAND_MAX;
	return min + f * (max - min);
}

void Lightning::makeBolt(){

	double lfactor = 0.5;

	double x, y, z;

	std::vector<Level::Point> temp(4);
	
	double length = 20;
	
	bolt.resize(6);

	Level::Point p;

	//Bolt part 1

	p.x = myRand(44.0, 51.0);
	p.y = 15.0;
	p.z = myRand(-3, 3);

	temp[0] = p;

	for (int i = 1; i <= 3; i++){
		p.x = myRand(p.x - lfactor, p.x + lfactor);
		p.y = myRand(13, p.y);
		p.z = myRand(p.z - lfactor, p.z + lfactor);
		temp[i] = p;
	}

	bolt[0] = temp;

	//Bolt part 2

	p.x = myRand(p.x - lfactor, p.x + lfactor);
	p.y = 13;
	p.z = myRand(p.z - lfactor, p.z + lfactor);

	temp[0] = p;

	for (int i = 1; i <= 3; i++){
		p.x = myRand(p.x - lfactor, p.x + lfactor);
		p.y = myRand(11, p.y);
		p.z = myRand(p.z - lfactor, p.z + lfactor);
		temp[i] = p;
	}

	bolt[1] = temp;

	//Bolt part 3 -this part hits the sword and stops

	p.x = myRand(p.x - lfactor, p.x + lfactor);
	p.y = 11;
	p.z = myRand(p.z - lfactor, p.z + lfactor);

	temp[0] = p;

	for (int i = 1; i <= 3; i++){
		p.x = myRand(p.x - lfactor, p.x + lfactor);
		p.y = myRand(9, p.y);
		p.z = myRand(p.z - lfactor, p.z + lfactor);
		temp[i] = p;
	}

	bolt[2] = temp;

	//Bolt part 3 - Branch - this one branches again

	p.x = myRand(p.x - lfactor, p.x + lfactor);
	p.y = 11;
	p.z = myRand(p.z - lfactor, p.z + lfactor);

	temp[2] = p;

	for (int i = 1; i <= 3; i++){
		p.x = myRand(p.x - lfactor, p.x + lfactor);
		p.y = myRand(9, p.y);
		p.z = myRand(p.z - lfactor, p.z + lfactor);
		temp[i] = p;
	}

	bolt[3] = temp;

	//Bolt part 4 - Branch off of bolt part 3 - branch

	p.x = myRand(p.x - lfactor, p.x + lfactor);
	p.y = 9;
	p.z = myRand(p.z - lfactor, p.z + lfactor);

	temp[2] = p;

	for (int i = 1; i <= 3; i++){
		p.x = myRand(p.x - lfactor, p.x + lfactor);
		p.y = myRand(6, p.y);
		p.z = myRand(p.z - lfactor, p.z + lfactor);
		temp[i] = p;
	}

	p.x = myRand(p.x - lfactor, p.x + lfactor);
	p.y = myRand(5, p.y);
	p.z = myRand(p.z - lfactor, p.z + lfactor);
	temp[3] = p;

	bolt[4] = temp;

	// Bolt part 4 - Branch - Branch off of bolt part 3 - branch

	p.x = myRand(p.x - lfactor, p.x + lfactor);
	p.y = 11;
	p.z = myRand(p.z - lfactor, p.z + lfactor);

	temp[2] = p;

	for (int i = 1; i <= 3; i++){
		p.x = myRand(p.x - lfactor, p.x + lfactor);
		p.y = myRand(8, p.y);
		p.z = myRand(p.z - lfactor, p.z + lfactor);
		temp[i] = p;
	}

	p.x = myRand(p.x - lfactor, p.x + lfactor);
	p.y = myRand(5, p.y);
	p.z = myRand(p.z - lfactor, p.z + lfactor);
	temp[3] = p;

	bolt[5] = temp;

}

void Lightning::draw(){

	glColor3f(1, 1, 1);
	glLineWidth(4);
	glBindTexture(GL_TEXTURE_2D, myTex);

	if (count >= 1 * factor){
		glBegin(GL_LINES);
		glTexCoord2f(0.5, 0.0);
		glVertex3f(bolt[0][0].x, bolt[0][0].y, bolt[0][0].z);
		glTexCoord2f(0.0, 0.5);
		glVertex3f(bolt[0][1].x, bolt[0][1].y, bolt[0][1].z);

		glTexCoord2f(0.5, 0.0);
		glVertex3f(bolt[0][1].x, bolt[0][1].y, bolt[0][1].z);
		glTexCoord2f(0.0, 0.5);
		glVertex3f(bolt[0][2].x, bolt[0][2].y, bolt[0][2].z);

		glTexCoord2f(0.5, 0.0);
		glVertex3f(bolt[0][2].x, bolt[0][2].y, bolt[0][2].z);
		glTexCoord2f(0.0, 0.5);
		glVertex3f(bolt[0][3].x, bolt[0][3].y, bolt[0][3].z);
		glEnd();
	}
	//part 2
	if (count >= 2 * factor){
		glBegin(GL_LINES);

		glTexCoord2f(0.5, 0.0);
		glVertex3f(bolt[0][3].x, bolt[0][3].y, bolt[0][3].z);
		glTexCoord2f(0.0, 0.5);
		glVertex3f(bolt[1][0].x, bolt[1][0].y, bolt[1][0].z);

		glTexCoord2f(0.5, 0.0);
		glVertex3f(bolt[1][0].x, bolt[1][0].y, bolt[1][0].z);
		glTexCoord2f(0.0, 0.5);
		glVertex3f(bolt[1][1].x, bolt[1][1].y, bolt[1][1].z);

		glTexCoord2f(0.5, 0.0);
		glVertex3f(bolt[1][1].x, bolt[1][1].y, bolt[1][1].z);
		glTexCoord2f(0.0, 0.5);
		glVertex3f(bolt[1][2].x, bolt[1][2].y, bolt[1][2].z);

		glTexCoord2f(0.5, 0.0);
		glVertex3f(bolt[1][2].x, bolt[1][2].y, bolt[1][2].z);
		glTexCoord2f(0.0, 0.5);
		glVertex3f(bolt[1][3].x, bolt[1][3].y, bolt[1][3].z);
		glEnd();
	}
	//part 3
	if (count >= 3 * factor){
		glBegin(GL_LINES);

		/*glVertex3f(bolt[1][3].x, bolt[1][3].y, bolt[1][3].z);
		glVertex3f(bolt[2][0].x, bolt[2][0].y, bolt[2][0].z);

		glVertex3f(bolt[2][0].x, bolt[2][0].y, bolt[2][0].z);
		glVertex3f(bolt[2][1].x, bolt[2][1].y, bolt[2][1].z);

		glVertex3f(bolt[2][1].x, bolt[2][1].y, bolt[2][1].z);
		glVertex3f(bolt[2][2].x, bolt[2][2].y, bolt[2][2].z);

		glVertex3f(bolt[2][2].x, bolt[2][2].y, bolt[2][2].z);
		glVertex3f(bolt[2][3].x, bolt[2][3].y, bolt[2][3].z);*/

		//part 3 branch
		glTexCoord2f(0.5, 0.0);
		glVertex3f(bolt[1][3].x, bolt[1][3].y, bolt[1][3].z);
		glTexCoord2f(0.0, 0.5);
		glVertex3f(bolt[3][0].x, bolt[3][0].y, bolt[3][0].z);

		glTexCoord2f(0.5, 0.0);
		glVertex3f(bolt[3][0].x, bolt[3][0].y, bolt[3][0].z);
		glTexCoord2f(0.0, 0.5);
		glVertex3f(bolt[3][1].x, bolt[3][1].y, bolt[3][1].z);

		glTexCoord2f(0.5, 0.0);
		glVertex3f(bolt[3][1].x, bolt[3][1].y, bolt[3][1].z);
		glTexCoord2f(0.0, 0.5);
		glVertex3f(bolt[3][2].x, bolt[3][2].y, bolt[3][2].z);

		glTexCoord2f(0.5, 0.0);
		glVertex3f(bolt[3][2].x, bolt[3][2].y, bolt[3][2].z);
		glTexCoord2f(0.0, 0.5);
		glVertex3f(bolt[3][3].x, bolt[3][3].y, bolt[3][3].z);
		glEnd();
	}

	if (count >= 4* factor){
		//part 4
		glBegin(GL_LINES);

		/*glVertex3f(bolt[3][3].x, bolt[3][3].y, bolt[3][3].z);
		glVertex3f(bolt[4][0].x, bolt[4][0].y, bolt[4][0].z);

		glVertex3f(bolt[4][0].x, bolt[4][0].y, bolt[4][0].z);
		glVertex3f(bolt[4][1].x, bolt[4][1].y, bolt[4][1].z);

		glVertex3f(bolt[4][1].x, bolt[4][1].y, bolt[4][1].z);
		glVertex3f(bolt[4][2].x, bolt[4][2].y, bolt[4][2].z);

		glVertex3f(bolt[4][2].x, bolt[4][2].y, bolt[4][2].z);
		glVertex3f(bolt[4][3].x, bolt[4][3].y, bolt[4][3].z);

		glVertex3f(bolt[4][2].x, bolt[4][2].y, bolt[4][2].z);
		glVertex3f(myRand(46.5, 49.5), 5, myRand(-1.5, 1.5));*/

		//part 4 branch
		glTexCoord2f(0.5, 0.0);
		glVertex3f(bolt[3][3].x, bolt[3][3].y, bolt[3][3].z);
		glTexCoord2f(0.0, 0.5);
		glVertex3f(bolt[5][0].x, bolt[5][0].y, bolt[5][0].z);

		glTexCoord2f(0.5, 0.0);
		glVertex3f(bolt[5][0].x, bolt[5][0].y, bolt[5][0].z);
		glTexCoord2f(0.0, 0.5);
		glVertex3f(bolt[5][1].x, bolt[5][1].y, bolt[5][1].z);

		glTexCoord2f(0.5, 0.0);
		glVertex3f(bolt[5][1].x, bolt[5][1].y, bolt[5][1].z);
		glTexCoord2f(0.0, 0.5);
		glVertex3f(bolt[5][2].x, bolt[5][2].y, bolt[5][2].z);

		glTexCoord2f(0.5, 0.0);
		glVertex3f(bolt[5][2].x, bolt[5][2].y, bolt[5][2].z);
		glTexCoord2f(0.0, 0.5);
		glVertex3f(bolt[5][3].x, bolt[5][3].y, bolt[5][3].z);

		glTexCoord2f(0.5, 0.0);
		glVertex3f(bolt[5][3].x, bolt[5][3].y, bolt[5][3].z);
		glTexCoord2f(0.0, 0.5);
		glVertex3f(myRand(46.5, 49.5), 5, myRand(-1.5, 1.5));
		glEnd();
	}

	count++;
	if (count == 5*factor + 10){
		count = 0;
		makeBolt();
	}
}

Lightning::Lightning()
{
	makeBolt();
}


Lightning::~Lightning()
{
}
