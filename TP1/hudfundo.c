#include <stdio.h>
#include <stdlib.h>
#include <SOIL/SOIL.h>

#include "BIBLIOTECAS/hudfundo.h"
#include "BIBLIOTECAS/settings.h"

GLint texFundo[8];
GLint texHUD[10];

//carrega os frames do fundo animado, e e as fontes da pontuação
void initHUDFundo(){
    texFundo[0] = SOIL_load_OGL_texture("TEXTURAS/final_by_pukahuna-d71mea6-1.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texFundo[1] = SOIL_load_OGL_texture("TEXTURAS/final_by_pukahuna-d71mea6-2.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texFundo[2] = SOIL_load_OGL_texture("TEXTURAS/final_by_pukahuna-d71mea6-3.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texFundo[3] = SOIL_load_OGL_texture("TEXTURAS/final_by_pukahuna-d71mea6-4.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texFundo[4] = SOIL_load_OGL_texture("TEXTURAS/final_by_pukahuna-d71mea6-5.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texFundo[5] = SOIL_load_OGL_texture("TEXTURAS/final_by_pukahuna-d71mea6-6.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texFundo[6] = SOIL_load_OGL_texture("TEXTURAS/final_by_pukahuna-d71mea6-7.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texFundo[7] = SOIL_load_OGL_texture("TEXTURAS/final_by_pukahuna-d71mea6-8.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texHUD[0] = SOIL_load_OGL_texture("TEXTURAS/font/0.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texHUD[1] = SOIL_load_OGL_texture("TEXTURAS/font/1.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texHUD[2] = SOIL_load_OGL_texture("TEXTURAS/font/2.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texHUD[3] = SOIL_load_OGL_texture("TEXTURAS/font/3.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texHUD[4] = SOIL_load_OGL_texture("TEXTURAS/font/4.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texHUD[5] = SOIL_load_OGL_texture("TEXTURAS/font/5.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texHUD[6] = SOIL_load_OGL_texture("TEXTURAS/font/6.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texHUD[7] = SOIL_load_OGL_texture("TEXTURAS/font/7.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texHUD[8] = SOIL_load_OGL_texture("TEXTURAS/font/8.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texHUD[9] = SOIL_load_OGL_texture("TEXTURAS/font/9.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

}

//cria a display list da tela de fundo
GLint Fundo;
void padraoFundo(){
	Fundo = glGenLists(1);
	glNewList(Fundo, GL_COMPILE);
		glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f(0, 0); glVertex3f(0, 0,  0);
			glTexCoord2f(0, 1); glVertex3f(0,  ALTR_TELA,  0);
			glTexCoord2f(1, 1); glVertex3f(LARG_TELA,  ALTR_TELA,  0);
			glTexCoord2f(1, 0); glVertex3f(LARG_TELA, 0,  0);
			glEnd();  			
	glEndList();
}

//cria a display list da pontuação
GLint HUD;
void padraoHUD(){
	HUD = glGenLists(1);
	glNewList(HUD, GL_COMPILE);
		glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f(0, 0); glVertex3f(-20, -20,  0);
			glTexCoord2f(0, 1); glVertex3f(-20,  20,  0);
			glTexCoord2f(1, 1); glVertex3f( 20,  20,  0);
			glTexCoord2f(1, 0); glVertex3f( 20, -20,  0);
			glEnd();  			
	glEndList();
}

//desenha a pontuação na tela, sendo a pontuação máxima 999
void desenhaHUD(){
		glColor3f(1, 1, 1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glPushMatrix();     
			glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texHUD[PONTUACAO[2]]);           
					glTranslatef(30, 30, 0);
						glCallList(HUD);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		glPushMatrix();     
			glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texHUD[PONTUACAO[1]]);           
					glTranslatef(70, 30, 0);
						glCallList(HUD);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		glPushMatrix();     
			glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texHUD[PONTUACAO[0]]);           
					glTranslatef(110, 30, 0);
						glCallList(HUD);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
}

//desenha o fundo animado, com um frame a cada 1/4 de segundo
void desenhaFundo(){
	glColor3f(1,1,1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
  				glBindTexture(GL_TEXTURE_2D, texFundo[contadorTela / 4]);
				glCallList(Fundo);
  		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		contadorTela++;
		if(contadorTela == 32){
			contadorTela = 0;
		}
}