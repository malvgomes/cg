#include <stdio.h>
#include <stdlib.h>

#include "BIBLIOTECAS/settings.h"

//variaveis globais
GLfloat raioPlayer = 15.0;
GLfloat raioFood = 15.0;
GLfloat raioProjetil = 25; 
GLfloat LARG_TELA;
GLfloat ALTR_TELA;
GLint pressX = 0;
GLint pressY = 0;
GLint NUM_FOOD = 1;
GLint contador = 0;
GLint multiplier = 1;
GLint contadorProjetil = 0;
GLint texHeart;
GLint contadorTela = 0;
GLint contadorBullet = 0;
GLint contadorFood = 0;
GLint statusTex = 0;
GLint PONTUACAO[3] = {0, 0, 0};
GLint contadorEat = 0;


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