#include <stdio.h>
#include <stdlib.h>

#include "BIBLIOTECAS/settings.h"

//variaveis globais
GLfloat thetaDoor = 0;
GLfloat thetaFan = 0;
GLfloat LARG_TELA;
GLfloat ALTR_TELA;
GLfloat ratio;
GLfloat posX = 100;
GLfloat posY;
GLfloat posZ = 120;
GLfloat lookatX;
GLfloat lookatY = .4;
GLfloat lookatZ;
GLfloat anguloY = 0;
GLfloat anguloSun = 0;
GLfloat anguloMoon = 180;
GLfloat bobbing = 0;
GLint sinal = 1;
GLint openDoor = 0;

tree *arvores;

//funcoes de conversao para calculos aritmeticos
GLfloat converteRad(GLfloat theta){
	return theta * (M_PI / 180);
}

GLfloat distanciaEntrePontos(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2){
	return (sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}

GLfloat norma(GLfloat x, GLfloat y){
	return (sqrt(pow(x, 2) + pow(y, 2)));
}

GLfloat produtoEscalar(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2){
	return (x1 * x2) + (y1 * y2);
}

GLfloat anguloEntreVetores(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2){
	return acos(produtoEscalar(x1, y1, x2, y2)/(norma(x1, y1) * norma(x2, y2)));
}