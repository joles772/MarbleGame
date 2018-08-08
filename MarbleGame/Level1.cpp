#include "Level1.h"
#include <math.h>
#include <bass.h>
#include "Lightning.h"

bool loaded = false;

void doSound();

bool sunder2Trigger = false;
bool bridgeBeginTrigger = false;
bool bridgeEndTrigger = false;

double bridgeZPlus = 0;

HSTREAM streamHandle;

Lightning lightning1;
Lightning lightning2;
Lightning lightning3;

void setLight(){
	// Lighting set up
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Set lighting intensity and color
	GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	GLfloat lightPos2[] = { 40, 10, 0, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos2);
}

Level1::Level1()
{

	loadObj(*Level::getFaces(), "Res/Level1/Meshes/l1Bounds.obj");
	

	printf("gi");
}


Level1::~Level1()
{
	BASS_Free();
}

void Level1::getRes(){
	
	loadObj(*Level::getObjectFaces(0), "Res/Level1/Meshes/lowpolytree.obj");
	*getTextures(0) = loadTex("Res/Level1/Textures/treeTex.jpg");
	resizeTextures();
	*getTextures(1) = loadTex("Res/Level1/Textures/barkTex.jpg");

	printf("\nhie\n");

	resizeTextures();

	resizeObjectFaces();

	loadObj(*Level::getObjectFaces(1), "Res/Level1/Meshes/grass.obj");
	*getTextures(2) = loadTex("Res/Level1/Textures/grassTex.png");

	resizeTextures();

	resizeObjectFaces();

	loadObj(*Level::getObjectFaces(2), "Res/Level1/Meshes/rock.obj");
	*getTextures(3) = loadTex("Res/Level1/Textures/rockTex.jpg");

	resizeTextures();

	resizeObjectFaces();

	loadObj(*Level::getObjectFaces(3), "Res/Level1/Meshes/pillar.obj");
	*getTextures(4) = *getTextures(3);

	resizeTextures();

	resizeObjectFaces();

	loadObj(*Level::getObjectFaces(4), "Res/Level1/Meshes/sword.obj");
	*getTextures(5) = loadTex("Res/Level1/Textures/bladeTex.jpg");

	resizeTextures();

	resizeObjectFaces();

	loadObj(*Level::getObjectFaces(5), "Res/Level1/Meshes/log.obj");
	*getTextures(6) = loadTex("Res/Level1/Textures/logTex.jpg");

	resizeTextures();

	resizeObjectFaces();

	loadObj(*Level::getObjectFaces(6), "Res/Level1/Meshes/drawBridge.obj");
	*getTextures(7) = *getTextures(1);

	resizeTextures();

	resizeObjectFaces();

	loadObj(*Level::getObjectFaces(7), "Res/Level1/Meshes/castle.obj");
	*getTextures(8) = loadTex("Res/Level1/Textures/floorTex.jpg");

	lightning1.myTex = loadTex("Res/Level1/Textures/lightningTex.jpg");
}



void doSound(const char* c){
	int device = -1; 
	int freq = 44100; 


	BASS_Init(device, freq, 0, 0, NULL);


	streamHandle = BASS_StreamCreateFile(FALSE, c, 0, 0, 0);
	BASS_ChannelFlags(streamHandle, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
	BASS_ChannelPlay(streamHandle, TRUE);

}

void Level1::checkListeners(){
	if (!sunder2Trigger && player->z > -4 && player->z < 4 && player->x > 40 && player->x < 51){
		BASS_ChannelStop(streamHandle);
		doSound("Res/Level1/Sound/sundering2.mp3");
		sunder2Trigger = true;
	}

	if (!bridgeBeginTrigger && player->z >= 12 && player->x > 44 && player->x < 48){
		canMove = false;
		BASS_ChannelStop(streamHandle);
		doSound("Res/Level1/Sound/hailAndKill.mp3");
		bridgeBeginTrigger = true;
	}
	if (bridgeBeginTrigger && !bridgeEndTrigger){
		double factor = 0.05;
		bridgeZPlus = bridgeZPlus + factor;
		printf("HIIIII");
	}
	if (bridgeBeginTrigger && !bridgeEndTrigger && bridgeZPlus > 7){
		canMove = true;
		bridgeEndTrigger = true;
	}
}

void doLightning(){

	lightning1.draw();
	lightning2.draw();
	lightning3.draw();
}

void Level1::draw(int num, double x, double y, double z){

	setLight();

	if (loaded == false){

		player->myTex = loadTex("Res/Player/Textures/marbleTex.jpg");

		Level1::getRes();
		loaded = true;
		doSound("Res/Level1/Sound/sundering1.mp3");
	}
	checkListeners();
	for (int i = 0; i < 24; i++){

		if (i % 2 == 0) Level::draw(0, -3 + i, 0, -5.75);

		else Level::draw(0, -3 + i, 0, -5.25);
	}

	for (int i = 0; i < 24; i++){

		if (i % 2 == 0) Level::draw(0, -3 + i, 0, 5.75);

		else Level::draw(0, -3 + i, 0, 5.25);
	}

	for (int i = 0; i < 11; i++){

		if (i % 2 == 0) Level::draw(0, -3.5, 0, -5.25 + i);

		else Level::draw(0, -3, 0, -5.25 + i);
	}

	Level::draw(0, 5, 0, -2.5);
	Level::draw(0, 5, 0, 2.5);

	Level::draw(0, 13, 0, -2.5);
	Level::draw(0, 13, 0, 3);

	Level::draw(0, 9, 0, 0);
	Level::draw(0, 16, 0, 0);
	Level::draw(1, 0, 0, 0);
	Level::draw(2, 0, 0, 0);
	Level::draw(3, 48, 3, -2);
	Level::draw(3, 45, 0, -1);
	Level::draw(3, 47, 1, 2);

	Level::draw(4, 47, 5, 0);
	Level::draw(5, 0, 0, 0);

	Level::draw(6, 46.5,3, 8 + bridgeZPlus);

	Level::draw(7, 0, 0, 0);

	doLightning();
	
}
