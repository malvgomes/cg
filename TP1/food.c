#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <SOIL/SOIL.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include "BIBLIOTECAS/som.h"
#include "BIBLIOTECAS/settings.h"
#include "BIBLIOTECAS/player.h"

GLint padraoFood;
GLint texFOOD[4];

//carrega os sprites da comida
void initComida(){
    texFOOD[0] = SOIL_load_OGL_texture("TEXTURAS/p9.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texFOOD[1] = SOIL_load_OGL_texture("TEXTURAS/p10.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texFOOD[2] = SOIL_load_OGL_texture("TEXTURAS/p11.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texFOOD[3] = SOIL_load_OGL_texture("TEXTURAS/p12.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
}

//cria a display list da comida
void padraoComida(){
	padraoFood = glGenLists(1);
	glNewList(padraoFood, GL_COMPILE);
		glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f(0, 0); glVertex3f(-raioFood, -raioFood,  0);
	        glTexCoord2f(0, 1); glVertex3f(-raioFood,  raioFood,  0);
	        glTexCoord2f(1, 1); glVertex3f( raioFood,  raioFood,  0);
	        glTexCoord2f(1, 0); glVertex3f( raioFood, -raioFood,  0);
		glEnd();
	glEndList();
}

//gera a comida com posição aleatória
config geraFood(){
	config novoFood;
	novoFood.xPos = rand() % (int)LARG_TELA;
	novoFood.yPos = rand() % (int)ALTR_TELA;
	//se a comida surge na parte de baixo da tela, ela é colocada em cima
	if(novoFood.yPos < ALTR_TELA*.2){
		novoFood.yPos + ALTR_TELA*.3;
	}
	novoFood.status = 1;
	novoFood.raio = raioFood;
	return novoFood;
}

void resetFood(){
	food = NULL;
}

//inicializa a lista de comidas
void initFood(){
	food = (node*)malloc(sizeof(node));
	food->anterior = NULL;
	node *temp = food;
	GLint i;
	for(i = 0; i < NUM_FOOD; i++){
		temp->proximo = (node*)malloc(sizeof(node));
		temp->proximo->anterior = temp;
		temp->proximo->settings = geraFood();
		temp = temp->proximo;
	}
	temp->proximo = NULL;
}

//insere comida na lista
void spawnFood(){
	node *temp = food;
	while(temp->proximo != NULL){
		temp = temp->proximo;
	}
	temp->proximo = (node*)malloc(sizeof(node));
	temp->proximo->anterior = temp;
	temp->proximo->proximo = NULL;
	temp->proximo->settings = geraFood();
}

//desenha a comida, com animação
void desenhaFood(){
	glColor3f(1, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	node *temp = food->proximo;
	while(temp != NULL){
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);   
			glBindTexture(GL_TEXTURE_2D, texFOOD[contadorFood / 5]);            
				glTranslatef(temp->settings.xPos, temp->settings.yPos, 0);
					glCallList(padraoFood);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	contadorFood++;
	if(contadorFood == 20){
		contadorFood = 0;
	}
	temp = temp->proximo;
	}
}

void removeFood(){
	node *temp = food->proximo, *tempFree;
	while(temp != NULL){
		if(temp->settings.status == 0){
			player.raio += 2;
			spawnFood();
			PONTUACAO[0]++;
			contadorEat = 1;
			if(PONTUACAO[0] == 10){
				PONTUACAO[1]++;
				PONTUACAO[0] = 0;
			}
			if(PONTUACAO[1] == 10){
				PONTUACAO[2]++;
				PONTUACAO[1] = 0;
			}
			tempFree = temp;
			temp->anterior->proximo = temp->proximo;
			if(temp->proximo != NULL){
				temp->proximo->anterior = temp->anterior;
			}
			free(tempFree);
		}
		temp = temp->proximo;
	}
}

void detectaColisao(){
	node *temp = food->proximo;
	GLfloat dist;

	while(temp != NULL){
		dist = distanciaEntrePontos(temp->settings.xPos, temp->settings.yPos, player.xPos, player.yPos);
			if(dist < (player.raio + temp->settings.raio)){
				temp->settings.status = 0;
				statusTex = 1;
				Mix_PlayChannel(-1, efeitoEat, 0);
			}
		temp = temp->proximo;
	}
}
