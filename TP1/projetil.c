#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SOIL/SOIL.h>

#include "BIBLIOTECAS/som.h"
#include "BIBLIOTECAS/player.h"
#include "BIBLIOTECAS/settings.h"
#include "BIBLIOTECAS/projetil.h"

GLint padraoBullet;
GLint texBulletLEFT[7];
GLint texBulletRIGHT[7];

//carrega os frames dos projeteis, tanto para a esquerda quando para a direita
void initBullet(){
	texBulletLEFT[0]  = SOIL_load_OGL_texture("TEXTURAS/Fishman-Fireball-v2-copy-1.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texBulletLEFT[1]  = SOIL_load_OGL_texture("TEXTURAS/Fishman-Fireball-v2-copy-2.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texBulletLEFT[2]  = SOIL_load_OGL_texture("TEXTURAS/Fishman-Fireball-v2-copy-3.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texBulletLEFT[3]  = SOIL_load_OGL_texture("TEXTURAS/Fishman-Fireball-v2-copy-4.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texBulletLEFT[4]  = SOIL_load_OGL_texture("TEXTURAS/Fishman-Fireball-v2-copy-5.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texBulletLEFT[5]  = SOIL_load_OGL_texture("TEXTURAS/Fishman-Fireball-v2-copy-6.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texBulletLEFT[6]  = SOIL_load_OGL_texture("TEXTURAS/Fishman-Fireball-v2-copy-7.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texBulletRIGHT[0] = SOIL_load_OGL_texture("TEXTURAS/Fishman-Fireball-v2-copy-8.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texBulletRIGHT[1] = SOIL_load_OGL_texture("TEXTURAS/Fishman-Fireball-v2-copy-10.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texBulletRIGHT[2] = SOIL_load_OGL_texture("TEXTURAS/Fishman-Fireball-v2-copy-11.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texBulletRIGHT[3] = SOIL_load_OGL_texture("TEXTURAS/Fishman-Fireball-v2-copy-12.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texBulletRIGHT[4] = SOIL_load_OGL_texture("TEXTURAS/Fishman-Fireball-v2-copy-13.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texBulletRIGHT[5] = SOIL_load_OGL_texture("TEXTURAS/Fishman-Fireball-v2-copy-14.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texBulletRIGHT[6] = SOIL_load_OGL_texture("TEXTURAS/Fishman-Fireball-v2-copy-14.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

//cria a display list dos projeteis
void padraoProjetil(){
	padraoBullet = glGenLists(1);
	glNewList(padraoBullet, GL_COMPILE);
		glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f(0, 0); glVertex3f(-raioProjetil, -raioProjetil,  0);
	        glTexCoord2f(0, 1); glVertex3f(-raioProjetil,  raioProjetil,  0);
	        glTexCoord2f(1, 1); glVertex3f( raioProjetil,  raioProjetil,  0);
	        glTexCoord2f(1, 0); glVertex3f( raioProjetil, -raioProjetil,  0);
		glEnd();
	glEndList();
}

//gera um projetil com velocidade aleatoria, direção x aleatoria, velocidade x aleatória e posição y aleatoria
config geraProjetil(){
	int randomico = rand() % 2;
	config novoProjetil;
	novoProjetil.status = 1;
	novoProjetil.raio = raioProjetil;
	int velRandX = rand() % 600;
	int mult = 1;
	if(randomico == 1){
		mult *= -1;
		novoProjetil.xPos = LARG_TELA;
		novoProjetil.yPos = rand() % (int)ALTR_TELA;
	}else{
		novoProjetil.xPos = 0;
		novoProjetil.yPos = rand() % (int)ALTR_TELA;
	}
	novoProjetil.velocidadeX = mult * (float)velRandX / 100; 
	novoProjetil.velocidadeY = 0;
	return novoProjetil;
}


void resetProjetil(){
	projetil = NULL;
}

//inicializa a lista de projeteis
void initProjetil(){
	projetil = (node*)malloc(sizeof(node));
	projetil->anterior = NULL;
	node *temp = projetil;
	temp->proximo = NULL;
}

//adiciona um projétil à lista
void spawnProjetil(){
	contador++;
	if(contador == 30){
		node *temp = projetil;
		while(temp->proximo != NULL){
			temp = temp->proximo;
		}
		temp->proximo = (node*)malloc(sizeof(node));
		temp->proximo->anterior = temp;
		temp->proximo->proximo = NULL;
		temp->proximo->settings = geraProjetil();		
		contador = 0;
	}
}

//desenha o projetil, usando a velocidade 
void desenhaProjetil(){
		glColor3f(1, 1, 1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		node *temp = projetil->proximo;
		while(temp != NULL){
		glPushMatrix();     
			glEnable(GL_TEXTURE_2D);
				if(temp->settings.velocidadeX > 0){
					glBindTexture(GL_TEXTURE_2D, texBulletLEFT[contadorBullet / 30]);           
				}else{
					glBindTexture(GL_TEXTURE_2D, texBulletRIGHT[contadorBullet / 30]);           
				}
					glTranslatef(temp->settings.xPos, temp->settings.yPos, 0);
						glCallList(padraoBullet);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		contadorBullet++;
		if(contadorBullet == 210){
			contadorBullet = 0;
		}
		temp = temp->proximo;
	}
}

//percorre a lista de projeteis, alterando a velocidade de cada um
void moveProjetil(){
	node *temp = projetil->proximo;
	while(temp != NULL){
		temp->settings.xPos += temp->settings.velocidadeX;
	    temp->settings.yPos += temp->settings.velocidadeY;
		temp = temp->proximo;
	}
}

//remove os projeteis quando eles saem da tela de jogo
void removeProjetil(){
	node *temp = projetil->proximo;
	node *tempFree;
	while(temp != NULL){
		if(abs(temp->settings.xPos) > LARG_TELA){
			tempFree = temp;
			temp->anterior->proximo = temp->proximo;
			if(temp->proximo != NULL){
				temp->proximo->anterior = temp->anterior;
			}
			free(tempFree);
		}
		if(abs(temp->settings.xPos) < 0){
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

//detecta colisao entre projetil e jogador
void detectaColisaoProjetil(){
	node *temp = projetil->proximo;
	GLfloat dist;

	while(temp != NULL){
		dist = distanciaEntrePontos(temp->settings.xPos, temp->settings.yPos, player.xPos, player.yPos);
			if(dist < (player.raio + temp->settings.raio)){
				Mix_PlayChannel(-1, efeitoDor, 0);
				player.raio -= .2;
				statusTex = 2;
			}
		temp = temp->proximo;
	}
}