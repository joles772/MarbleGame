#include "Enemy.h"
#include <math.h>


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::draw(){
	double m[3][3];

	//velocity vector. Column 2
	double normal = sqrt((b2.x - b.x)*(b2.x - b.x) + (b2.y - b.y)*(b2.y - b.y) + (b2.z - b.z)*(b2.z - b.z));
	m[0][2] = (b2.x - b.x) / normal;
	m[1][2] = (b2.y - b.y) / normal;
	m[2][2] = (b2.z - b.z) / normal;

	//orthogonal vector to the velocity vector. The vector is chosen so that it is never the zero vector. Column 1
	if (m[1][2] != 0 && m[0][2] != 0){
		normal = sqrt(m[1][2] * m[1][2] + m[0][2] * m[0][2]);
		m[0][1] = m[1][2] / normal;
		m[1][1] = -m[0][2] / normal;
		m[2][1] = 0;
	}
	else{
		normal = m[2][2] * m[2][2] + m[0][2] * m[0][2];
		m[0][1] = m[2][2] / normal;
		m[1][1] = 0;
		m[2][1] = -m[0][2] / normal;
	}

	//cross product of the other two. Column 0
	m[0][0] = m[1][1] * m[2][2] - m[2][1] * m[1][2];
	m[1][0] = m[2][1] * m[0][2] - m[0][1] * m[2][2];
	m[2][0] = m[0][1] * m[1][2] - m[1][1] * m[0][2];

	normal = sqrt(m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0]);

	m[0][0] = m[0][0] / normal;
	m[1][0] = m[1][0] / normal;
	m[2][0] = m[2][0] / normal;

	double newx;
	double newy;
	double newz;


}
