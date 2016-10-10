#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/freeglut.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "declarations.h"
#include <GL/glext.h>
#include "Landmark/landmark.h"
#include "Field/field.h"
#include "Textures/sdlglutils.h"
#include <math.h>

//TODO: For resources allocated by the application, see if static textures are only loaded once or if its are loaded each time
//int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize);

/*-lmingw32
 -lSDLmain
 -lSDL
 -lSDL_mixer
 -lSDL_image */

//zip et cc fran�ois le floch
//Thierry.SOBANSKI@ICL-LILLE.FR
//Generer volume a partir de courbe de spleen

int main(int argc, char **argv) {

	int continuer = 1;
	double angleCubeX = 0;
	double angleCubeY = 0;
	GLdouble xcam = -20;
	GLdouble ycam = 4;
	GLdouble zcam = -10;
	GLdouble tetaCam= 0;
	GLdouble rayon= 15;
	Uint32 last_time = SDL_GetTicks();
	Uint32 current_time, ellapsed_time;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("OpenGL", NULL);
	SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);

	SDL_EnableKeyRepeat(10,10);

	glEnable(GL_TEXTURE_2D);

	textureCaisse = loadTexture("Textures/caisse.tga", 0 );
	textureGroundDust = loadTexture("Textures/sand03.tga", 0 );

	SDL_Event event;

//	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)
//			== -1) //Initialisation de l'API Mixer
//			{
//		printf("%s", Mix_GetError());
//	}
//	Mix_Music *musique; //Cr�ation du pointeur de type Mix_Music
	//musique = Mix_LoadMUS("Sound/Sugar feat. Milie oops (do di do di dam).mp3"); //Chargement de la musique
	//Mix_PlayMusic(musique, -1); //Jouer infiniment la musique-----------

	while (continuer) {
		SDL_PollEvent(&event);
		current_time = SDL_GetTicks();
		ellapsed_time = current_time - last_time;
		last_time = current_time;

		switch (event.type) {
		case SDL_QUIT:
			continuer = 0;
//			Mix_FreeMusic(musique); //Lib�ration de la musique
//			Mix_CloseAudio(); //Fermeture de l'API
			SDL_Quit(); //TODO: Bug when closing application
			return EXIT_SUCCESS;

			break;

		case SDL_KEYDOWN:

			switch (event.key.keysym.sym)

			{

			case SDLK_UP:
				angleCubeX++;
				if (angleCubeX == 360) angleCubeX = 0;

					break;
			case SDLK_DOWN:
				angleCubeX--;
				if (angleCubeX < 0) angleCubeX = 360;
				break;
			case SDLK_LEFT:
				//if ((event.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT)
//				{
//					angle1++;
//					if (angle1 > 90)
//					angle1 = 90;
//				}
//				else
//				{
//					angle2++;
//					if (angle2 > 90)
//					angle2 = 90;
//				}
				angleCubeY++;
				if (angleCubeY == 360) angleCubeY = 0;
				break;

			case SDLK_RIGHT:
				angleCubeY--;
				if (angleCubeY < 0) angleCubeY = 360;
				break;

			default:
			break;
			}
			break;
		}

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(70,(double)640/480,1,1000);
			glEnable(GL_DEPTH_TEST);

			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			glMatrixMode( GL_MODELVIEW );
			glLoadIdentity( );

			tetaCam += 0.05 * ellapsed_time;
			if (tetaCam > 360) tetaCam = 0;
			printf("%d \n",tetaCam);
			printf( "hello world\n" );
			gluLookAt(rayon*cos(tetaCam * 2 * pi / 360), ycam, rayon*sin(tetaCam * 2 * pi / 360) , 0,2,0,0,1,0);

//*************//MAIN VIDEO GAME DRAWING**********************************************

			//Create Ground
			groundDust(-20, 20, 0, -10, 10);

			//Create rotating cube
			angleCubeY += 0.05 * ellapsed_time;
			angleCubeX += 0.05 * ellapsed_time;

			glTranslated(0,2,0);
			glRotated(angleCubeY,0,1,0);
			glRotated(angleCubeX,1,0,0);
			cube(0,0,0);

			ellapsed_time = SDL_GetTicks() - current_time;
			if (ellapsed_time < 10)   SDL_Delay(10 - ellapsed_time);

			//glColor3f(1.0, 1.0, 0.0);
			//glutSolidCone(0.3, 0.5, 50, 50);
			//DrawAxes(0.0,0.0,0.0);
			//dessinerRepere(2);

//****************MAIN VIDEO GAME DRAWING END******************************************

			glFlush();
			SDL_GL_SwapBuffers();
		}

		return 0;
	}




/* Dessine le rep�re actuel pour faciliter la compr�hension des transformations.
 Utiliser � echelle � pour avoir un rep�re bien orient� et positionn� mais avec une �chelle diff�rente. */

void Resize(int Width, int Height) {
	GLdouble Aspect;
	glViewport(0, 0, (GLsizei) Width, (GLsizei) Height);
	Aspect = (GLdouble) Width / (GLdouble) Height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, Aspect, 0.01, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void Keyfunc(unsigned char Key, int X, int Y) {
	switch (Key) {
	case 'z':
		touchez = 1;
		//if(c=0)
		//while(anglebras<180.0) anglebras=anglebras+1.0;

		//else anglebras=90.0;
		break;
	case 'q':
		toucheq = 1;
		break;
	case 'd':
		touched = 1;
		break;
	case 's':
		touches = 1;
		break;
	case 'f':
		printf("f\n");
		break;
	case 32:
		spacebar = 1;
		break;
	}
}

void KeyfuncUp(unsigned char Key, int X, int Y) {
	switch (Key) {
	case 'z':
		touchez = 0;
		break;
	case 'q':
		toucheq = 0;
		break;
	case 'd':
		touched = 0;
		break;
	case 's':
		touches = 0;
		break;
	case 'f':
		printf("f\n");
		break;
	case 32:
		spacebar = 0;
		break;
	}
}

void Menu(int Value) {
	perspectiveChoice = Value;
}

