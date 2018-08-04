#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>

GLfloat LARG_TELA;
GLfloat ALTR_TELA;
GLfloat raioPlayer;
GLfloat raioFood;
GLfloat raioProjetil;
GLint   pressX;
GLint   pressY;
GLint   NUM_FOOD;
GLint   contador;
GLint multiplier;
GLint contadorProjetil;
GLint contadorTela;
GLint contadorBullet;
GLint contadorFood;
GLint statusTex;
GLint PONTUACAO[3];
GLint contadorEat;

typedef struct config{
 	GLfloat xPos;
 	GLfloat yPos;
 	GLfloat raio;
 	GLint status;
 	GLfloat velocidadeX;
 	GLfloat velocidadeY;
}config;


typedef struct node{
	struct config settings;
	struct node *anterior;
	struct node *proximo;
}node;

config mouse;
config player;
node *food;
node *projetil;

GLfloat converteRad(GLfloat theta);
GLfloat distanciaEntrePontos(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
void multipliern();
