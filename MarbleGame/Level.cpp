#include "Level.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SOIL.h>
#include <freeglut.h>

std::vector<Level::Triangle> faces;
std::vector<std::vector<Level::Triangle>> objectFaces(1);
std::vector<std::vector<Level::Triangle>> solidFaces(1);
std::vector<GLuint> textures(1);

int materialCount = 0;

bool gotRes = false;
bool startTex = false;

double Level::getPX(){
	return Level::player->x;
}

double Level::getPY(){
	return Level::player->y;
}

double Level::getPZ(){
	return Level::player->z;
}

std::vector<Level::Triangle>* Level::getFaces(){
	return &faces;
}

std::vector<Level::Triangle>* Level::getObjectFaces(int i){
	return &objectFaces[i];
}

GLuint* Level::getTextures(int i){
	return &textures[i];
}

void Level::resizeObjectFaces(){
	objectFaces.resize(objectFaces.size() + 1);
}

void Level::resizeTextures(){
	textures.resize(textures.size() + 1);
}

void addPoint(std::vector<Level::Point> &vec, Level::Point p){
	vec[vec.size() - 1] = p;
	vec.resize(vec.size() + 1);
}

void addTriangle(std::vector<Level::Triangle> &vec, Level::Triangle p){
	vec[vec.size() - 1] = p;
	vec.resize(vec.size() + 1);
}

void Level::loadObj(std::vector<Level::Triangle> &faces, const char* s){

	using namespace std;

	cout << s << '\n';

	std::vector<Level::Point> points(1);
	std::vector<Level::Point> normals(1);
	std::vector<Level::Point> finalNormals(1);
	std::vector<Level::Triangle> triangles(1);
	std::vector<Level::Point> textures(1);

	string line;
	ifstream myfile(s);
	int count = 0;
	int count2 = 0;
	double x = 0, y = 0, z = 0;
	string delimiter1 = " ";
	string delimiter2 = "/";
	string token;
	string coord;
	Level::Point p;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line[0] == 'v' && line[1] == ' '){

			//	cout << "point: ";

				line = line.substr(2);
				int found = line.find(delimiter1);
				token = line.substr(0, found);
				line.erase(0, found + 1);
				//cout << token << ",";
				p.x = atof(token.c_str());

				found = line.find(delimiter1);
				token = line.substr(0, found);
				line.erase(0, found + 1);
				//cout << token << ",";
				p.y = atof(token.c_str());

				found = line.find(delimiter1);
				token = line.substr(0, found);
				//cout << token << "\n";
				p.z = atof(token.c_str());
				addPoint(points, p);
			}
			else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' '){
				//cout << "normal: ";

				line = line.substr(3);
				int found = line.find(delimiter1);
				token = line.substr(0, found);
				line.erase(0, found + 1);
				//cout << token << ",";
				p.x = atof(token.c_str());

				found = line.find(delimiter1);
				token = line.substr(0, found);
				line.erase(0, found + 1);
				//cout << token << ",";
				p.y = atof(token.c_str());

				found = line.find(delimiter1);
				token = line.substr(0, found);
				//cout << token << "\n";
				p.z = atof(token.c_str());
				addPoint(normals, p);
			}
			else if (line[0] == 'v' && line[1] == 't' && line[2] == ' '){
				//cout << "tex: ";

				line = line.substr(3);
				int found = line.find(delimiter1);
				token = line.substr(0, found);
				line.erase(0, found + 1);
				//cout << token << ",";
				p.x = atof(token.c_str());

				found = line.find(delimiter1);
				token = line.substr(0, found);
				line.erase(0, found + 1);
				//cout << token << ",";
				p.y = atof(token.c_str());

				addPoint(textures, p);

			}
			else if (line[0] == 'f' && line[1] == ' '){
				//cout << "face: ";
				line = line.substr(2);
				Level::Triangle t;
				Level::Point p;

				t.t = materialCount - 1;

				//cout << "\nFACE:" << t.t << "\n";

				int found = line.find(delimiter1);
				token = line.substr(0, found);
				int found2 = token.find(delimiter2);
				string token2 = token.substr(0, found2);
				
				
				t.p1 = points[atoi(token2.c_str()) - 1];

				//cout << points[atoi(token2.c_str()) - 1].x << "\n";

				token.erase(0, found2 + 1);
				found2 = token.find(delimiter2);
				token2 = token.substr(0, found2);

				if (textures.size() > 1){
					t.p1.tx = textures[atoi(token2.c_str()) - 1].x;
					t.p1.ty = textures[atoi(token2.c_str()) - 1].y;
				}

				line.erase(0, found + 1);
				//cout << token2 << ",";

				found = line.find(delimiter1);
				token = line.substr(0, found);
				found2 = token.find(delimiter2);
				token2 = token.substr(0, found2);
				
				
				t.p2 = points[atoi(token2.c_str()) - 1];

				token.erase(0, found2 + 1);
				found2 = token.find(delimiter2);
				token2 = token.substr(0, found2);

				if (textures.size() > 1){
					t.p2.tx = textures[atoi(token2.c_str()) - 1].x;
					t.p2.ty = textures[atoi(token2.c_str()) - 1].y;
				}

				line.erase(0, found + 1);
				//cout << token2 << ",";
				p.y = atoi(token.c_str());

				found = line.find(delimiter1);
				token = line.substr(0, found);
				found2 = token.find(delimiter2);
				token2 = token.substr(0, found2);
				
				
				t.p3 = points[atoi(token2.c_str()) - 1];

				line.erase(0, found2 + 1);
				found2 = line.find(delimiter2);
				token2 = line.substr(0, found2);

				if (textures.size() > 1){
					t.p3.tx = textures[atoi(token2.c_str()) - 1].x;
					t.p3.ty = textures[atoi(token2.c_str()) - 1].y;
				}

				line.erase(0, found2 + 1);

				Level::Point f = normals[atoi(line.c_str()) - 1];

				//cout << token2 << "\n";

				addTriangle(triangles, t);
				addPoint(finalNormals, f);
			}
			else if (line[0] == 'u' && line[1] == 's'){
				if(startTex == true) materialCount++;
				cout << "\nFACE:" << materialCount << "\n";
			}
		}
		myfile.close();

		for (int i = 0; i < finalNormals.size() - 1; i++){
			triangles[i].n = finalNormals[i];
			//cout << "T: " << triangles[i].p1.x << ", " << triangles[i].p1.y << ", " << triangles[i].p1.z << "\n";
			//cout << triangles[i].n.x << ", " << triangles[i].n.y << ", " << triangles[i].n.z << "\n";
		}

		faces = triangles;
	}

	else cout << "Unable to open file";

	startTex = true;
}

float dotProd(Level::Point p1, Level::Point p2){
	float f = p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
	return f;
}

//adapted from Christer Ericson's "Real-Time Collision Detection"
void barycentric(Level::Point p, Level::Point a, Level::Point b, Level::Point c, float &u, float &v, float &w)
{
	Level::Point v0;
	v0.x = b.x - a.x;
	v0.y = b.y - a.y;
	v0.z = b.z - a.z;

	Level::Point v1;
	v1.x = c.x - a.x;
	v1.y = c.y - a.y;
	v1.z = c.z - a.z;

	Level::Point v2;
	v2.x = p.x - a.x;
	v2.y = p.y - a.y;
	v2.z = p.z - a.z;

	float d00 = dotProd(v0, v0);
	float d01 = dotProd(v0, v1);
	float d11 = dotProd(v1, v1);
	float d20 = dotProd(v2, v0);
	float d21 = dotProd(v2, v1);

	float denom = d00 * d11 - d01 * d01;
	v = (d11 * d20 - d01 * d21) / denom;
	w = (d00 * d21 - d01 * d20) / denom;
	u = 1.0f - v - w;
}

void Level::setPlayer(Player &p){
	Level::player = &p;
}

void Level::collision(double inX, double inY, double inZ){

	float u, v, w;
	Point p;
	p.x = (double)player->x;
	p.y = (double)player->y;
	p.z = (double)player->z;

	double norm;

	for (int i = 0; i < faces.size(); i++){
		Triangle t = faces[i];
		barycentric(p, t.p1, t.p2, t.p3, u, v, w);

		float d = (p.x - t.p1.x)*t.n.x + (p.y - t.p1.y)*t.n.y + (p.z - t.p1.z)*t.n.z;
		if (d < 0.0f) d = d*(-1);

		if (u >= 0.0f && v >= 0.0f && w >= 0.0f && d <= 1.1){
			norm = sqrt((t.n.x)*(t.n.x) + (t.n.z)*(t.n.z));

			player->move((t.n.x), 0, (t.n.z), false);
		}
	}

	player->move((inX), 0, (inZ), false);

}

double lastYN = 1;

void Level::gravity(){
	float u, v, w;

	bool collision = false;

	Point p;
	p.x = (double)player->x;
	p.y = (double)player->y;
	p.z = (double)player->z;

	for (int i = 0; i < faces.size(); i++){
		Triangle t = faces[i];
		barycentric(p, t.p1, t.p2, t.p3, u, v, w);

		float d = (p.x - t.p1.x)*t.n.x + (p.y - t.p1.y)*t.n.y + (p.z - t.p1.z)*t.n.z;
		if (d < 0.0f) d = d*(-1);

		if (u >= 0.0f && v >= 0.0f && w >= 0.0f && d <= 1.1 && t.n.y > 0.5){
			collision = true;

			lastYN = t.n.y;
			player->gravity(t.n.x, 1 - t.n.y, t.n.z, false);
			break;
		}
	}

	if(collision == false) player->gravity(0, -lastYN, 0, false);
}

GLuint Level::loadTex(const char* c) {
	GLuint temp = SOIL_load_OGL_texture(
		c,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	if (0 == temp)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		//return 0;
	}

	//glGenTextures(1, &temp);

	glBindTexture(GL_TEXTURE_2D, temp);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return temp;
}

void drawObject(std::vector<Level::Triangle> faces, double x, double y, double z ){
	glColor3f(1, 1, 1);


	glTranslatef(x, y, z);


	GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, black);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0);
	
	for (int i = 0; i < faces.size(); i++){
		Level::Triangle t = faces[i];

		glBindTexture(GL_TEXTURE_2D, textures[t.t]);
		glBegin(GL_TRIANGLES);

		glNormal3f(t.n.x, t.n.y, t.n.z);

		glTexCoord2f(t.p1.tx, t.p1.ty);

		glVertex3f(t.p1.x, t.p1.y, t.p1.z);

		glTexCoord2f(t.p2.tx, t.p2.ty);

		glVertex3f(t.p2.x, t.p2.y, t.p2.z);

		glTexCoord2f(t.p3.tx, t.p3.ty);

		glVertex3f(t.p3.x, t.p3.y, t.p3.z);
		glEnd();
	}
	
	glTranslatef(-x, -y, -z);
}

void Level::draw(int num, double x, double y, double z){

	if (gotRes == false){
		getRes();
		gotRes = true;
	}


	/*glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	for (int i = 0; i < faces.size(); i++){
		Triangle t = faces[i];

		glVertex3f(t.p1.x, t.p1.y, t.p1.z);
		glVertex3f(t.p2.x, t.p2.y, t.p2.z);

		glVertex3f(t.p2.x, t.p2.y, t.p2.z);
		glVertex3f(t.p3.x, t.p3.y, t.p3.z);

		glVertex3f(t.p3.x, t.p3.y, t.p3.z);
		glVertex3f(t.p1.x, t.p1.y, t.p1.z);
	}
	glEnd();*/

	if(player->y > -4) drawObject(objectFaces[num], x, y, z);
	else{
		std::string s = "GAME OVER";
		glColor3f(1, 0, 0);
		glRasterPos3f(player->x - 2, player->y-2, player->z - 2);
		for (int i = 0; i < s.length(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
		}
	}
}

void Level::getRes(){
}

void Level::drawStuff(){

}

Level::Level()
{
	//loadObj(faces, "Res/Level1/Meshes/l1Bounds.obj");
	Triangle t;
	for (int i = 0; i < faces.size(); i++){
		t = faces[i];
		std::cout << "Triangle" << i << "\nP1: " << t.p1.x << ", " << t.p1.y << ", " << t.p1.z << "\n";
		std::cout << "\nP2: " << t.p2.x << ", " << t.p2.y << ", " << t.p2.z << "\n";
		std::cout << "\nP1: " << t.p3.x << ", " << t.p3.y << ", " << t.p3.z << "\n";
		std::cout << "\nN: " << t.n.x << ", " << t.n.y << ", " << t.n.z << "\n";
	}
}


Level::~Level()
{
}
