#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <SOIL/SOIL.h>

#include "BIBLIOTECAS/player.h"
#include "BIBLIOTECAS/settings.h"

GLint texPlayer[5];
GLint padraoPlayer;
enum Status{ZERO, EAT, PAIN};

//carrega os sprites do jogador
void initDemon(){
    texPlayer[0] = SOIL_load_OGL_texture("TEXTURAS/caco_idle.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texPlayer[1] = SOIL_load_OGL_texture("TEXTURAS/caco_left.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texPlayer[2] = SOIL_load_OGL_texture("TEXTURAS/caco_right.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texPlayer[3] = SOIL_load_OGL_texture("TEXTURAS/caco_eat.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texPlayer[4] = SOIL_load_OGL_texture("TEXTURAS/caco_pain.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

}

//inicializa as caracteristicas do jogador, colocando-o no meio da tela
void initPlayer(){
	player.xPos = (LARG_TELA / 2);
	player.yPos = (ALTR_TELA / 2);
	player.velocidadeX = 0;
	player.velocidadeY = 0;
	player.raio = raioPlayer;
	player.status = 1;
}

//cria a display list do jogador
void padraoJogador(){
	padraoPlayer = glGenLists(1);
	glNewList(padraoPlayer, GL_COMPILE);
		glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f(0, 0); glVertex3f(-player.raio, -player.raio,  0);
			glTexCoord2f(0, 1); glVertex3f(-player.raio,  player.raio,  0);
			glTexCoord2f(1, 1); glVertex3f( player.raio,  player.raio,  0);
			glTexCoord2f(1, 0); glVertex3f(	player.raio, -player.raio,  0);
		glEnd();  
	glEndList();
}

//funcao que move o jogador, de acordo com sua velocidade
void movePlayer(){
	player.xPos += player.velocidadeX;
	player.yPos += player.velocidadeY;
}

//desenha o jogador
void desenhaPlayer(){
	//contador para a animacao de "comer", pois um frame seria quase imperceptível	
	if(contadorEat != 0){
		contadorEat++;
	}
	glColor3f(1,1,1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);                
				glTranslatef(player.xPos, player.yPos, 0);
				//se o jogador estiver pressionando a seta da direita, usa-se a textura caco_right
				if(pressX == 1){
					glBindTexture(GL_TEXTURE_2D, texPlayer[2]);
				//para a esquerda, caco_left
				}else if(pressX == -1){
					glBindTexture(GL_TEXTURE_2D, texPlayer[1]);
				//caso contrario, usa-se caco_idle que é quando não está ocorrendo ação alguma
				}else{
					glBindTexture(GL_TEXTURE_2D, texPlayer[0]);
				}
				//se o jogador estiver comendo, ou sendo atingido por um projetil, statusTex != 0
				if(statusTex != ZERO){
					//sprite "comendo"
					if(statusTex == EAT && contadorEat != 0){
						glBindTexture(GL_TEXTURE_2D, texPlayer[3]);
					//sprite "dor"
					}else if(statusTex == PAIN){
						glBindTexture(GL_TEXTURE_2D, texPlayer[4]);
					}
				}
				glScalef(player.raio / 10, player.raio / 10, 0);
					glCallList(padraoPlayer);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		//se o contador de comida for zero, usa-se as outras texturas 
		if(contadorEat == 0){
			statusTex = ZERO;
		}
		//quando o contador chega a 1/6 de segundo, ele é zerado
		if(contadorEat == 10){
			contadorEat = 0;
		}
}

//acelera o jogador na direção x
void aceleraPlayerX(){
	if(abs(player.velocidadeX) < 3){
		if(pressX == 1){
			player.velocidadeX += .1;
		}else if(pressX == -1){
			player.velocidadeX -= .1;
		}else{
			player.velocidadeY += 0;
		}
	}
}

//acelera o jogador na direção y
void aceleraPlayerY(){
	if(abs(player.velocidadeY) < 3){
		if(pressY == 1){
			player.velocidadeY += .1;
		}else if(pressY == -1){
			player.velocidadeY -= .1;
		}else{
			player.velocidadeY += 0;
		}
	}
}

//desacelera o jogador na direcao x
void desaceleraPlayerX(){
	if(player.velocidadeX > 0){
		player.velocidadeX -= .05;
	}else if(player.velocidadeX < 0){
		player.velocidadeX += .05;
	}
}

//desacelera o jogador na direcao y
void desaceleraPlayerY(){
	if(player.velocidadeY > 0){
		player.velocidadeY -= .05;
	}else if(player.velocidadeY < 0){
		player.velocidadeY += .05;
	}
}

//limita o mundo para o jogador
void impedePlayer(){
	if(player.xPos > LARG_TELA){ 
		player.xPos = LARG_TELA - 10;
	}
	if(player.xPos < 0){
		player.xPos = 10;
	}
	if(player.yPos > ALTR_TELA){
		player.yPos = ALTR_TELA - 10;
	}
	if(player.yPos < 0){
		player.yPos = 10;
	}
}

//diminui a massa do jogador com o passar do tempo
void perdeMassa(){
	if(player.raio > 0){
		player.raio -= .005;
	}
}