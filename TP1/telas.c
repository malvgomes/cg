#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <SOIL/SOIL.h>

#include "BIBLIOTECAS/telas.h"
#include "BIBLIOTECAS/settings.h"


GLint texTelas[10];
GLint padraoScreen;
GLint padraoPAUSE;

//carrega as telas de menu, creditos, pause e gameover
void initTelas(){
    texTelas[0] = SOIL_load_OGL_texture("TEXTURAS/back.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texTelas[1] = SOIL_load_OGL_texture("TEXTURAS/back2.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texTelas[2] = SOIL_load_OGL_texture("TEXTURAS/back3.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texTelas[3] = SOIL_load_OGL_texture("TEXTURAS/back4.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texTelas[4] = SOIL_load_OGL_texture("TEXTURAS/back5.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texTelas[5] = SOIL_load_OGL_texture("TEXTURAS/creditos.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texTelas[6] = SOIL_load_OGL_texture("TEXTURAS/pause1.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texTelas[7] = SOIL_load_OGL_texture("TEXTURAS/pause2.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texTelas[8] = SOIL_load_OGL_texture("TEXTURAS/pause3.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    texTelas[9] = SOIL_load_OGL_texture("TEXTURAS/gover.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

}

//cria a display list das telas de jogo
void padraoTela(){
	padraoScreen = glGenLists(1);
	glNewList(padraoScreen, GL_COMPILE);
		glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f(0, 0); glVertex3f(0, 0,  0);
			glTexCoord2f(0, 1); glVertex3f(0,  ALTR_TELA,  0);
			glTexCoord2f(1, 1); glVertex3f(LARG_TELA,  ALTR_TELA,  0);
			glTexCoord2f(1, 0); glVertex3f(LARG_TELA, 0,  0);
		glEnd();  			
	glEndList();
}

//desenha as telas de jogo de acordo com o valor passado como parametro
void desenhaTela(int telaAtual){
	glColor3f(1,1,1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
  				glBindTexture(GL_TEXTURE_2D, texTelas[telaAtual]);
					glCallList(padraoScreen);
  			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
}