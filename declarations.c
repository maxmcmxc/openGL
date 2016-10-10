/*
 * declarations.c
 *
 *  Created on: 22 mai 2013
 *      Author: Maxence Fromentin
 */

#include <GL/freeglut.h>
#include <SDL/SDL_mixer.h>

// Textures declarations

	GLuint textureCaisse;
	GLuint textureGroundDust;


//Application Parameters Main Declarations

	//Window Size

		float WindowWidth = 1024.0;
		float WindowHeight = 768.0;

	//Mouse Moves

		GLboolean Move_Flag = GL_FALSE;
		GLboolean Zoom_Flag = GL_FALSE;
		GLdouble Radius = 1.0;
		GLdouble Twist = 0.0;
		GLdouble Longitude = 0.0;
		GLdouble Latitude = 0.0;

		int X_Start_Move;
		int Y_Start_Move;

		int Y_Start_Zoom;//vas is das ? deprecated ?

		int Xvalue;
		int Yvalue;

//Game Scenario

	//Saucer

		float anglesoucoupe = 0.0;
		float anglesuivresoucoupe = -20.0;
		int aurevoirsoucoupe = 0, bougersoucoupe = 0;
		char *step = "kinematicSaucerArrives"; // Warning: Difference between " " and ' '
		float tt = -200.0; // TODO: Change name

	//Main Character

		float xbonhomme;
		float ybonhomme;
		float zbonhomme = 0.0;

		float armAngle;

		int makeCharacter = 0;

		//Character Moves
		int touchez,toucheq,touched,touches,toucher;
		float zzx, zzy, qqx, qqy, ddx, ddy, ssx, ssy, zzddx, zzddy, zzqqx, zzqqy, ssqqx,
						ssqqy, ssddx, ssddy;
		float jack = 0.3; // TODO: Change Name
		int moveMan = 1;

		float jumpHeight = 1.0;
		float jumpMaxHeight = 29.0; //Nombre Impair
		int sautencours;


//Camera Perspective

	int perspectiveChoice = 1;
	float teta = 0.0;
	float zeta = 0.0;

	//Spyglass Mod

		float xCenterSpyglass = 0.0, yCenterSpyglass = 0.0, zCenterSpyglass = 0.0;

// Axis

	char nomaxex = 'x';
	char nomaxey = 'y';
	char nomaxez = 'z';

// Field

	// Lock areas

		float chunck[100][6];
		int nbchuncksdeclares = 0;

//General variables

	float i, j;
	int spacebar = 0;
	float pi = 3.14159265358979323846;


//	void Mousemotionmove ( int X, int Y);
//	void Mousemotionzoom ( int X, int Y);
//	void MouvementBonhomme(int X);
//	void RotateBonhomme(void);

