#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/freeglut.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "declarations.h"
#include <GL/glext.h>

#define LONGUEUR 50


//TODO: For resources allocated by the application, see if static textures are only loaded once or if its are loaded each time
//TODO: Lower The FPS and compare the processor allocation.
int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize);

/*-lmingw32
 -lSDLmain
 -lSDL
 -lsdl_mixer*/

//zip et cc fran�ois le floch
//Thierry.SOBANSKI@ICL-LILLE.FR
//Generer volume a partir de courbe de spleen
void ChargerTexture(char *nomfichier, unsigned int *nomtexture, int hauteur,
		int largeur) {
	char chaine1[50] = "Textures/";
	char *nom = strcat(chaine1, nomfichier);
	//Ouverture d'une texture. Syntaxe : fopen(nom_de_fichier, mode) avec r:read, b:write
	OuvrirTexture = fopen(nom, "rb");
	if (OuvrirTexture) {
		/*The first parameter is a pointer to where you want the data stored.
		 The second parameter is the size of each element that you want to read.
		 The third is the number of elements of that size toread. The final parameter a pointer to the stream obtained from fopen.*/
		fread(nomtexture, hauteur * largeur * 3, 1, OuvrirTexture);
		fclose(OuvrirTexture);
	}
}

/* Dessine le rep�re actuel pour faciliter la compr�hension des transformations.
 Utiliser � echelle � pour avoir un rep�re bien orient� et positionn� mais avec une �chelle diff�rente. */

void dessinerRepere(unsigned int echelle) {
	glPushMatrix();
	glScalef(echelle, echelle, echelle);
	glBegin(GL_LINES);
	glColor3ub(0, 0, 255);
	glVertex2i(0, 0);
	glVertex2i(1, 0);
	glColor3ub(0, 255, 0);
	glVertex2i(0, 0);
	glVertex2i(0, 1);
	glEnd();
	glPopMatrix();
}

void Initialize(int Width, int Height) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	Resize(Width, Height);
	ChargerTexture("soucoupe.bmp", TextureGrilleSoucoupe, 32, 32);
	ChargerTexture("icewater.tga", TextureSolEau, 512, 512);
	ChargerTexture("sand03.tga", TextureSolSable, 512, 512);
	ChargerTexture("grass.tga", TextureSolHerbe, 512, 512);
	ChargerTexture("lavarock3.tga", TextureLava, 512, 512);
	ChargerTexture("sandro_facemap.bmp", TextureFace, 512, 256);
	ChargerTexture("pantalon.bmp", TexturePantalon, 80, 128);
	ChargerTexture("ceinture.bmp", TextureCeinture, 240, 32);
	ChargerTexture("caisse.tga", TextureCaisse, 256, 256);
	ChargerTexture("Bassin.bmp", TextureBassin, 400, 64);
	ChargerTexture("chaussures.bmp", TextureChaussures, 140, 28);
	ChargerTexture("wall_dirty.tga", TextureWall_Dirty, 256, 256);
	ChargerTexture("spyglass.bmp", TextureSpyglass, 512, 512);
	ChargerTexture("transparent.bmp", TextureTransparent, 512, 512);
	ChargerTexture("fond.bmp", TextureFond, 512, 512);
	ChargerTexture("black.bmp", TextureBlack, 512, 512);
	ChargerTexture("Red.bmp", TextureRed, 512, 512);
	ChargerTexture("rgb.bmp", TextureRgb, 512, 512);
	//ChargerTexture("halo.bmp",TextureHalo,256,256);
	OuvrirTexture = fopen("Textures/halo.bmp", "rb");
	if (OuvrirTexture) {/*The first parameter is a pointer to where you want the data stored.
	 The second parameter is the size of each element that you want to read.
	 The third is the number of elements of that size toread. The final parameter a pointer to the stream obtained from fopen.*/
		fread(TextureHalo, 256 * 256 * 4, 1, OuvrirTexture);
		fclose(OuvrirTexture);
	}
	//for(dd=0;dd<256;dd++) {printf("%d",TextureSol[dd]);system("PAUSE");}
	//for(dd=0;dd<256;dd++) {printf("%d",TextureHalo[dd]);
	/* system("PAUSE");*///};
}

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

int main(int argc, char **argv) {

	int continuer = 1;
	int angle1 = -15;
	int angle2 = -50;
	int longueur = 15;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("OpenGL", NULL);
	SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);

	SDL_EnableKeyRepeat(10,10);

	SDL_Event event;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)
			== -1) //Initialisation de l'API Mixer
			{
		printf("%s", Mix_GetError());
	}
	Mix_Music *musique; //Cr�ation du pointeur de type Mix_Music
	musique = Mix_LoadMUS("Sound/Sugar feat. Milie oops (do di do di dam).mp3"); //Chargement de la musique
	Mix_PlayMusic(musique, -1); //Jouer infiniment la musique-----------

	while (continuer) {
		SDL_WaitEvent(&event);

		switch (event.type) {
		case SDL_QUIT:
			continuer = 0;
			Mix_FreeMusic(musique); //Lib�ration de la musique
			Mix_CloseAudio(); //Fermeture de l'API
			SDL_Quit(); //TODO: Bug when closing application
			return EXIT_SUCCESS;

			break;

		case SDL_KEYDOWN:

			switch (event.key.keysym.sym)

			{

			case SDLK_UP:
				longueur--;
				if (longueur < 10)
				longueur = 10;
				break;
			case SDLK_DOWN:
				longueur++;
				if (longueur > 100)
				longueur = 100;
				break;
			case SDLK_LEFT:
				if ((event.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT)
				{
					angle1++;
					if (angle1 > 90)
					angle1 = 90;
				}
				else
				{
					angle2++;
					if (angle2 > 90)
					angle2 = 90;
				}
				break;
			case SDLK_RIGHT:
				if ((event.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT)
				{
					angle1--;
					if (angle1 < 10)
					angle1 = 10;
				}
				else
				{
					angle2--;
					if (angle2 < -90)
					angle2 = -90;
				}
				break;
			}
			break;
		}

			glClear(GL_COLOR_BUFFER_BIT);
			glMatrixMode( GL_MODELVIEW);
			glLoadIdentity();
			gluOrtho2D(-10, 40, -10, 40);

			//MAIN VIDEO GAME DRAWING**********************************************

//		        glBegin(GL_TRIANGLES);
//		            glColor3ub(255,0,0);    glVertex2d(-0.75,-0.75);
//		            glColor3ub(0,255,0);    glVertex2d(0,0.75);
//		            glColor3ub(0,0,255);    glVertex2d(0.75,-0.75);
//		        glEnd();

			glBegin(GL_QUADS);
			glColor3ub(255, 127, 39);
			glVertex2d(-3.00, 0);
			glVertex2d(0, 0);
			glVertex2d(0, 1);
			glVertex2d(-3, 1);
			glEnd();

			glTranslatef(-1.5, 1, 0);
			glRotated(angle1, 0, 0, 1);
			glBegin(GL_QUADS);
			glColor3ub(255, 255, 0);
			glVertex2d(-0.5, 0);
			glVertex2d(0.5, 0);
			glVertex2d(0.5, longueur);
			glVertex2d(-0.5, longueur);
			glEnd();

			glTranslatef(0, longueur, 0);
			glRotated(angle2, 0, 0, 1);
			glBegin(GL_QUADS);
			glColor3ub(0, 255, 0);
			glVertex2d(-0.3, 0);
			glVertex2d(0.3, 0);
			glVertex2d(0.3, 4);
			glVertex2d(-0.3, 4);
			glEnd();

			glTranslatef(0, 4, 0);
			glRotated(-angle1-angle2, 0, 0, 1);
			glBegin(GL_LINES);
			glColor3ub(255, 255, 255);
			glVertex2d(0, 0);
			glVertex2d(0, -5);
			glEnd();

			glTranslatef(0, -5, 0);
			glBegin(GL_QUADS);
			glColor3ub(150, 255, 27);
			glVertex2d(-0.5, 0);
			glVertex2d(0.5, 0);
			glVertex2d(0.5, -1);
			glVertex2d(-0.5, -1);
			glEnd();

			glLoadIdentity();
			gluOrtho2D(-10, 40, -10, 40);

			dessinerRepere(10);

			//MAIN VIDEO GAME DRAWING END******************************************

			glFlush();
			SDL_GL_SwapBuffers();
		}

		return 0;
	}
