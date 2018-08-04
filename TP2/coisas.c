#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SOIL/SOIL.h>

#include "BIBLIOTECAS/settings.h"
#include "BIBLIOTECAS/coisas.h"

//configurações dos materiais, e especularidade dos diversos objetos
GLfloat no_shininess 		= 0.0f;
GLfloat low_shininess 		= 5.0f;
GLfloat high_shininess 		= 100.0f;
GLfloat trunk_diffuse[] 	= {.55, .27, .075};
GLfloat trunk_specular[] 	= {.2, .2, .2};
GLfloat trunk_ambient[] 	= {.055, .027, .0075};

GLfloat ground_diffuse[]  	= {0, .8, 0};
GLfloat ground_specular[] 	= {0.2, 0.2, 0.2};
GLfloat ground_ambient[]  	= {.2, .2, .2};

GLfloat floor_diffuse[]  	= {1, 1, 1};
GLfloat floor_specular[] 	= {.2, .2, .2};
GLfloat floor_ambient[]  	= {.2, .2, .2};

GLfloat tree_diffuse[] 		= {0.0, 1, 0.0};
GLfloat tree_specular[] 	= {.8, .8, .8};	 
GLfloat tree_ambient[]    	= {0.0, 0.4, 0.0};

GLfloat door_diffuse[] 		= {0.396, 0.263, 0.129};
GLfloat door_specular[] 	= {.8, .8, .8};	 
GLfloat door_ambient[]    	= {0.0396, 0.0263, 0.0129};

GLfloat wall_diffuse[] 		= {1, 1, 1};
GLfloat wall_specular[] 	= {.2, .2, .2};	 
GLfloat wall_ambient[]    	= {.2, .2, .2};

GLfloat movel_diffuse[]  	= {0, 0, 0};
GLfloat movel_specular[] 	= {1, 1, .1};	 
GLfloat movel_ambient[]  	= {0, 0, 0};

//variáveis de textura
GLint texGrass;
GLint texFloor;
GLint texWall;
GLint texInsideWall;
GLint texDoor;
GLint texRoof;

//inicialização de texturas
void initRoof(){	
	texRoof = SOIL_load_OGL_texture("TEXTURAS/roof.png",SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, texRoof);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void initGrass(){	
	texGrass = SOIL_load_OGL_texture("TEXTURAS/grass.png",SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, texGrass);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void initFloor(){
	texFloor = SOIL_load_OGL_texture("TEXTURAS/wood.png",SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, texFloor);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	
}

void initWall(){
	texWall = SOIL_load_OGL_texture("TEXTURAS/wall.png",SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, texWall);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	
}

void initInsideWall(){
	texInsideWall = SOIL_load_OGL_texture("TEXTURAS/insideWall.jpg",SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, texInsideWall);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	
}

void initDoor(){
	texDoor = SOIL_load_OGL_texture("TEXTURAS/door.png",SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, texDoor);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	
}

//variáveis para as display lists
GLint padraoArvore;
GLint padraoTroncoDePiramide;

//inicialização da posição das árvores no mundo
void initTree(){
	arvores = (tree*)malloc(sizeof(tree));
	tree *temp = arvores;
	for(int i = 0; i < 300; i++){
		temp->next = (tree*)malloc(sizeof(tree));
		int x = rand() % 200;
		int z = rand() % 200;
		while(x > 95 && x < 105){
			x += 10;
		}
		while(z > 95 && z < 105){
			z = rand() % 200;
		}
		temp->next->posX = (double)x;
		temp->next->posZ = -(double)z;
		temp->next->posY = 0;
		temp = temp->next;
	}
	temp->next = NULL;
}

//padrao de desenho da árvore, utilizando a composição de um cubo e um cone
void padraoTree(){
	padraoArvore = glGenLists(1);
		glNewList(padraoArvore, GL_COMPILE);
			glPushMatrix();
		        glMaterialfv(GL_FRONT, GL_AMBIENT, trunk_ambient);
		        glMaterialfv(GL_FRONT, GL_DIFFUSE, trunk_diffuse);
		        glMaterialfv(GL_FRONT, GL_SPECULAR, trunk_specular);
		        glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);
				glutSolidCube(.6);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0, .2, 0);
				glRotatef(-90, 1, 0, 0);
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tree_ambient);
		        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tree_diffuse);
		        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tree_specular);
		        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
		        glutSolidCone(1, 2, 60, 60);
			glPopMatrix();
		glEndList();
}

//função de desenho de árvores, que chama a display list de árvores
void desenhaTree(){
	tree *temp = arvores->next;
	while(temp != NULL){
		glPushMatrix();
				glTranslated(temp->posX, 0, -temp->posZ);
				glCallList(padraoArvore);
		glPopMatrix();
		temp = temp->next;
	}
}

//Função que desenha o chão do mundo, a grama
void desenhaChao(){
		glPushMatrix();
		    glMaterialfv(GL_FRONT, GL_AMBIENT, ground_ambient);
		    glMaterialfv(GL_FRONT, GL_DIFFUSE, ground_diffuse);
		    glMaterialfv(GL_FRONT, GL_SPECULAR, ground_specular);
		    glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);

   			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texGrass);

			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(0, 1, 0);
				glTexCoord2f(0, 0); glVertex3f(0, -.25, 0);
				glTexCoord2f(0, 200); glVertex3f(0, -.25, 200);
				glTexCoord2f(200, 200); glVertex3f(200, -.25, 200);
				glTexCoord2f(200, 0); glVertex3f(200, -.25, 0);
			glEnd();

			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
}

//função que desenha a casa, as paredes, o teto e a janela
void desenhaCasa(){
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, floor_ambient);
		    glMaterialfv(GL_FRONT, GL_DIFFUSE, floor_diffuse);
		    glMaterialfv(GL_FRONT, GL_SPECULAR, floor_specular);
		    glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);

   			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texFloor);

			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(0, 1, 0);
				glTexCoord2f(0, 0); glVertex3f(98, -.24, 98);
				glTexCoord2f(0, 4); glVertex3f(98, -.24, 102);
				glTexCoord2f(4, 4); glVertex3f(102, -.24, 102);
				glTexCoord2f(4, 0); glVertex3f(102, -.24, 98);
			glEnd();

			glDisable(GL_TEXTURE_2D);

			glMaterialfv(GL_FRONT, GL_AMBIENT, wall_ambient);
		    glMaterialfv(GL_FRONT, GL_DIFFUSE, wall_diffuse);
		    glMaterialfv(GL_FRONT, GL_SPECULAR, wall_specular);
		    glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);

  		    //p1fora
			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texWall);

			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(-1, 0, 0);
			 	glTexCoord2f(0, 0); glVertex3f(98, 2, 102);
			 	glTexCoord2f(0, 10); glVertex3f(98, 2, 98);
			 	glTexCoord2f(10, 10); glVertex3f(98, -.24, 98);
			 	glTexCoord2f(10, 0); glVertex3f(98, -.24, 102);
			glEnd();

			glDisable(GL_TEXTURE_2D);

			//p1dentro
			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texInsideWall);
			
			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(1, 0, 0);
			 	glTexCoord2f(0, 0); glVertex3f(98, -.24, 98);
			 	glTexCoord2f(0, 1); glVertex3f(98, 2, 98);
			 	glTexCoord2f(1, 1); glVertex3f(98, 2, 102);
			 	glTexCoord2f(1, 0); glVertex3f(98, -.24, 102);
			glEnd();

			glDisable(GL_TEXTURE_2D);

			//p2fora
			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texWall);

			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(1, 0, 0);
			 	glTexCoord2f(0, 0); glVertex3f(102, -.24, 102);
			 	glTexCoord2f(0, 10); glVertex3f(102, -.24, 98);
			 	glTexCoord2f(10, 10); glVertex3f(102, 2, 98);
			 	glTexCoord2f(10, 0); glVertex3f(102, 2, 102);
			glEnd();

			glDisable(GL_TEXTURE_2D);

			//p2dentro
			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texInsideWall);

			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(-1, 0, 0);
			 	glTexCoord2f(0, 0); glVertex3f(102, 2, 102);
			 	glTexCoord2f(0, 1); glVertex3f(102, 2, 98);
			 	glTexCoord2f(1, 1); glVertex3f(102	, -.24, 98);
			 	glTexCoord2f(1, 0); glVertex3f(102, -.24, 102);
			glEnd();

			glDisable(GL_TEXTURE_2D);

			//p3dentro
			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texInsideWall);

			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(0, 0, -1);
			 	glTexCoord2f(0, 0); glVertex3f(98, 2, 98);
			 	glTexCoord2f(0, 1); glVertex3f(99, 1.7, 98);
			 	glTexCoord2f(1, 1); glVertex3f(101, 1.7, 98);
			 	glTexCoord2f(1, 0); glVertex3f(102, 2, 98);
			glEnd();

			glDisable(GL_TEXTURE_2D);

			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texInsideWall);

			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(0, 0, -1);
			 	glTexCoord2f(1, 1); glVertex3f(98, 2, 98);
			 	glTexCoord2f(1, 0); glVertex3f(98, -.24, 98);
			 	glTexCoord2f(0, 0); glVertex3f(99, .06, 98);
			 	glTexCoord2f(0, 1); glVertex3f(99, 1.7, 98);
			glEnd();

			glDisable(GL_TEXTURE_2D);

			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texInsideWall);

			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(0, 0, -1);
			 	glTexCoord2f(1, 0); glVertex3f(98, -.24, 98);
			 	glTexCoord2f(0, 0); glVertex3f(102, -.24, 98);
			 	glTexCoord2f(0, 1); glVertex3f(101, .06, 98);
			 	glTexCoord2f(1, 1); glVertex3f(99, .06, 98);
			glEnd();

			glDisable(GL_TEXTURE_2D);

			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texInsideWall);

			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(0, 0, -1);
			 	glTexCoord2f(0, 1); glVertex3f(102, 2, 98);
			 	glTexCoord2f(0, 0); glVertex3f(101, 1.7, 98);
			 	glTexCoord2f(1, 1); glVertex3f(101, .06, 98);
			 	glTexCoord2f(1, 0); glVertex3f(102, -.24, 98);
			glEnd();

			glDisable(GL_TEXTURE_2D);

			//p3fora
			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texWall);

			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(0, 0, -1);
			 	glTexCoord2f(0, 10); glVertex3f(98, 2, 98);
			 	glTexCoord2f(10, 10); glVertex3f(102, 2, 98);
			 	glTexCoord2f(10, 0); glVertex3f(101, 1.7, 98);
			 	glTexCoord2f(0, 0); glVertex3f(99, 1.7, 98);
			glEnd();

			glDisable(GL_TEXTURE_2D);

			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texWall);

			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(0, 0, -1);
			 	glTexCoord2f(0, 10); glVertex3f(98, 2, 98);
			 	glTexCoord2f(10, 10); glVertex3f(99, 1.7, 98);
			 	glTexCoord2f(10, 0); glVertex3f(99, .06, 98);
			 	glTexCoord2f(0, 0); glVertex3f(98, -.24, 98);
			glEnd();

			glDisable(GL_TEXTURE_2D);

			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texWall);

			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(0, 0, -1);
			 	glTexCoord2f(0, 0); glVertex3f(98, -.24, 98);
			 	glTexCoord2f(0, 10); glVertex3f(99, .06, 98);
			 	glTexCoord2f(10, 10); glVertex3f(101, .06, 98);
			 	glTexCoord2f(10, 0); glVertex3f(102, -.24, 98);
			glEnd();

			glDisable(GL_TEXTURE_2D);

			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texWall);

			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(0, 0, -1);
			 	glTexCoord2f(0, 10); glVertex3f(101, 1.7, 98);
			 	glTexCoord2f(10, 10); glVertex3f(102, 2, 98);
			 	glTexCoord2f(10, 0); glVertex3f(102, -.24, 98);
			 	glTexCoord2f(0, 0); glVertex3f(101, .06, 98);
			glEnd();

			glDisable(GL_TEXTURE_2D);

			//tetofora
			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texWall);

			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(0, 1, 0);
			 	glTexCoord2f(0, 0); glVertex3f(102, 2, 98);
			 	glTexCoord2f(0, 5); glVertex3f(98,  2, 98);
			 	glTexCoord2f(5, 5); glVertex3f(98,  2, 102);
			 	glTexCoord2f(5, 0); glVertex3f(102, 2, 102);
			glEnd();

			glDisable(GL_TEXTURE_2D);

			//tetodentro
			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texInsideWall);

			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(0, -1, 0);
			 	glTexCoord2f(0, 0); glVertex3f(98,  2, 102);
			 	glTexCoord2f(0, 1); glVertex3f(98,  2, 98);
			 	glTexCoord2f(1, 1); glVertex3f(102, 2, 98);
			 	glTexCoord2f(1, 0); glVertex3f(102, 2, 102);
			glEnd();

			glDisable(GL_TEXTURE_2D);

			//frenteforacima
			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texWall);

			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(0, 1, 0);
			 	glTexCoord2f(40, 3); glVertex3f(102,  2, 102);
			 	glTexCoord2f(0, 3); glVertex3f(98,  2, 102);
			 	glTexCoord2f(0, 0);  glVertex3f(98, 1.5, 102);
			 	glTexCoord2f(40, 0);  glVertex3f(102, 1.5, 102);
			glEnd();

			glDisable(GL_TEXTURE_2D);

			//frentedentrocima
			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texInsideWall);

			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(0, -1, 0);
			 	glTexCoord2f(1, 1); glVertex3f(98,  2, 102);
			 	glTexCoord2f(0, 1); glVertex3f(102,  2, 102);
			 	glTexCoord2f(0, 0); glVertex3f(102, 1.5, 102);
			 	glTexCoord2f(1, 0); glVertex3f(98, 1.5, 102);
			 glEnd();
			 
			 glDisable(GL_TEXTURE_2D);

			//frenteforaesq
			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texWall);

			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(0, 1, 0);
			 	glTexCoord2f(10,10); glVertex3f(99.5,  1.5, 102);
			 	glTexCoord2f(0, 10); glVertex3f(98,  1.5, 102);
			 	glTexCoord2f(0, 0); glVertex3f(98, -.24, 102);
			 	glTexCoord2f(10, 0); glVertex3f(99.5, -.24, 102);
			glEnd();

			glDisable(GL_TEXTURE_2D);

			//frentedentroesq
			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texInsideWall);

			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(0, -1, 0);
			 	glTexCoord2f(1, 1); glVertex3f(98,  1.5, 102);
			 	glTexCoord2f(0, 1); glVertex3f(99.5,  1.5, 102);
			 	glTexCoord2f(0, 0); glVertex3f(99.5, -.24, 102);			 
			 	glTexCoord2f(1, 0); glVertex3f(98, -.24, 102);
			 glEnd();
			 
			 glDisable(GL_TEXTURE_2D);

			//frenteforadir
			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texWall);

			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(0, 1, 0);
			 	glTexCoord2f(10, 10); glVertex3f(102,  1.5, 102);
			 	glTexCoord2f(0, 10); glVertex3f(100.5,  1.5, 102);
			 	glTexCoord2f(0, 0); glVertex3f(100.5, -.24, 102);
			 	glTexCoord2f(10, 0); glVertex3f(102, -.24, 102);
			glEnd();

			glDisable(GL_TEXTURE_2D);

			//frentedentrodir
			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texInsideWall);

			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(0, -1, 0);
			 	glTexCoord2f(1, 1); glVertex3f(100.5,  1.5, 102);
			 	glTexCoord2f(0, 1); glVertex3f(102,  1.5, 102);
			 	glTexCoord2f(0, 0); glVertex3f(102, -.24, 102);
			 	glTexCoord2f(1, 0); glVertex3f(100.5, -.24, 102);
			 glEnd();

			 glDisable(GL_TEXTURE_2D);

			//porta
			glPushMatrix();
				glTranslatef(99.5, 0, 102);
				glRotatef(thetaDoor, 0, 1, 0);

				glEnable(GL_TEXTURE_2D);                
				glBindTexture(GL_TEXTURE_2D, texDoor);
				glMaterialfv(GL_FRONT, GL_AMBIENT, door_ambient);
			    glMaterialfv(GL_FRONT, GL_DIFFUSE, door_diffuse);
			    glMaterialfv(GL_FRONT, GL_SPECULAR, door_specular);
			    glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
				
				glBegin(GL_TRIANGLE_FAN);
					glNormal3f(0, 0, -1);
				 	glTexCoord2f(1, 1); glVertex3f(1,  1.5, 0);
				 	glTexCoord2f(0, 1); glVertex3f(0,  1.5, 0);
				 	glTexCoord2f(0, 0); glVertex3f(0, -.24, 0);
				 	glTexCoord2f(1, 0); glVertex3f(1, -.24, 0);
				glEnd();

				glBegin(GL_TRIANGLE_FAN);
					glNormal3f(0, 0, 1);
				 	glTexCoord2f(0, 1); glVertex3f(0,  1.5, 0);
				 	glTexCoord2f(1, 1); glVertex3f(1,  1.5, 0);
				 	glTexCoord2f(1, 0); glVertex3f(1, -.24, 0);
				 	glTexCoord2f(0, 0); glVertex3f(0, -.24, 0);
				glEnd();
			 	glDisable(GL_TEXTURE_2D);
			glPopMatrix();

			//janela
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
			glDisable(GL_LIGHTING);
			glEnable(GL_BLEND);
				glColor4f(1, 1, 1, .2);				
				glBegin(GL_TRIANGLE_FAN);
					glVertex3f(99, 1.7, 98);
					glVertex3f(99, .06, 98);
					glVertex3f(101,.06, 98);
					glVertex3f(101,1.7, 98);
				glEnd();

				glBegin(GL_TRIANGLE_FAN);
					glVertex3f(99, 1.7, 98);
					glVertex3f(101,1.7, 98);
					glVertex3f(101,.06, 98);
					glVertex3f(99, .06, 98);
				glEnd();
			glDisable(GL_BLEND);
			glEnable(GL_LIGHTING);

			//telhado
			glEnable(GL_TEXTURE_2D);                
			glBindTexture(GL_TEXTURE_2D, texRoof);

			glBegin(GL_TRIANGLE_FAN);
				glTexCoord2f(.5, 1); glVertex3f(100, 3, 100);
				glTexCoord2f(0, 0);  glVertex3f(98,  2, 102);
				glTexCoord2f(1, 0);  glVertex3f(102, 2, 102);
			glEnd();
			
			glBegin(GL_TRIANGLE_FAN);
				glTexCoord2f(.5, 1); glVertex3f(100, 3, 100);
				glTexCoord2f(0, 0);  glVertex3f(102, 2, 102);
				glTexCoord2f(1, 0);  glVertex3f(102, 2, 98);
			glEnd();

			glBegin(GL_TRIANGLE_FAN);
				glTexCoord2f(.5, 1); glVertex3f(100, 3, 100);
				glTexCoord2f(0, 0);  glVertex3f(102, 2, 98);
				glTexCoord2f(1, 0);  glVertex3f(98, 2, 98);
			glEnd();

			glBegin(GL_TRIANGLE_FAN);
				glTexCoord2f(.5, 1); glVertex3f(100, 3, 100);
				glTexCoord2f(0, 0);  glVertex3f(98, 2, 98);
				glTexCoord2f(1, 0);  glVertex3f(98, 2, 102);
			glEnd();

			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
}

//funçao de desenho dos móveis, feitos por composição de funções da glut
void desenhaMoveis(){
	        glMaterialfv(GL_FRONT, GL_AMBIENT, movel_ambient);
	        glMaterialfv(GL_FRONT, GL_DIFFUSE, movel_diffuse);
	        glMaterialfv(GL_FRONT, GL_SPECULAR, movel_specular);
	        glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);
			glPushMatrix();
				glPushMatrix();
					glTranslatef(100.35, 0, 100.35);
						glScalef(.1, 1, .1);
						glEnable(GL_NORMALIZE);
							glutSolidCube(.5);
						glDisable(GL_NORMALIZE);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(99.65, 0, 100.35);
						glScalef(.1, 1, .1);
						glEnable(GL_NORMALIZE);
							glutSolidCube(.5);
						glDisable(GL_NORMALIZE);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(100.35, 0, 99.65);
						glScalef(.1, 1, .1);
						glEnable(GL_NORMALIZE);
							glutSolidCube(.5);
						glDisable(GL_NORMALIZE);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(99.65, 0, 99.65);
						glScalef(.1, 1, .1);
						glEnable(GL_NORMALIZE);
							glutSolidCube(.5);
						glDisable(GL_NORMALIZE);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(100, 0.25, 100);
						glScalef(1.5, .1, 1.5);
						glEnable(GL_NORMALIZE);
							glutSolidCube(.5);
						glDisable(GL_NORMALIZE);
				glPopMatrix();
			glPopMatrix();
}

//desenha o ventilador, composto de dois cubos "escalados", e um cilindro
void ventilador(){
	glMaterialfv(GL_FRONT, GL_AMBIENT, movel_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, movel_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, movel_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);
	glPushMatrix();
	glTranslatef(100, 1.8, 100);
	glRotatef(thetaFan, 0, 1, 0);
		glPushMatrix();
			glScalef(.2, .05, 1.5);
			glEnable(GL_NORMALIZE);
				glutSolidCube(.5);
			glDisable(GL_NORMALIZE);
		glPopMatrix();

		glPushMatrix();
			glScalef(1.5, .05, .2);
			glEnable(GL_NORMALIZE);
				glutSolidCube(.5);
			glDisable(GL_NORMALIZE);
		glPopMatrix();

		GLUquadric* cil = gluNewQuadric();
		glPushMatrix();
			glTranslatef(0, .2, 0);
			glRotatef(90, 1, 0, 0);
			glEnable(GL_NORMALIZE);
				gluCylinder(cil, .02, .02, .2, 50, 50);
			glDisable(GL_NORMALIZE);
		glPopMatrix();
	glPopMatrix();

}

//desenha uma cadeira, composta por cubos "escalados"
void cadeira(){
	    glMaterialfv(GL_FRONT, GL_AMBIENT, movel_ambient);
	    glMaterialfv(GL_FRONT, GL_DIFFUSE, movel_diffuse);
	    glMaterialfv(GL_FRONT, GL_SPECULAR, movel_specular);
	    glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);

		glPushMatrix();
			glTranslatef(0, .1, 0);
			glScalef(.5, .05, .5);
			glEnable(GL_NORMALIZE);
				glutSolidCube(.5);
			glDisable(GL_NORMALIZE);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(.105, -.24, .105);
			glScalef(.08, 1.4, .08);
			glEnable(GL_NORMALIZE);
				glutSolidCube(.5);
			glDisable(GL_NORMALIZE);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-.105, -.24, .105);
			glScalef(.08, 1.4, .08);
			glEnable(GL_NORMALIZE);
				glutSolidCube(.5);
			glDisable(GL_NORMALIZE);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-.105, -.24, -.105);
			glScalef(.08, 1.4, .08);
			glEnable(GL_NORMALIZE);
				glutSolidCube(.5);
			glDisable(GL_NORMALIZE);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(.105, -.24, -.105);
			glScalef(.08, 1.4, .08);
			glEnable(GL_NORMALIZE);
				glutSolidCube(.5);
			glDisable(GL_NORMALIZE);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-.105, .2, 0);
			glScalef(.08, 1, .5);
			glEnable(GL_NORMALIZE);
				glutSolidCube(.5);
			glDisable(GL_NORMALIZE);
		glPopMatrix();
}

//função que desenha quatro cadeiras posicionadas na casa
void cadeiras(){
	glMaterialfv(GL_FRONT, GL_AMBIENT, movel_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, movel_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, movel_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);

	glPushMatrix();
		glTranslatef(100, 0, 99.5);
		glRotatef(-90, 0, 1, 0);
			cadeira();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(100, 0, 100.5);
		glRotatef(90, 0, 1, 0);
			cadeira();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(99.5, 0, 100);
		cadeira();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(100.5, 0, 100);
		glRotatef(180, 0, 1, 0);
		cadeira();
	glPopMatrix();
}

//funcao que desenha a bancada
void bancada(){
	glMaterialfv(GL_FRONT, GL_AMBIENT, movel_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, movel_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, movel_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);
	glPushMatrix();
		glTranslatef(101, .1, 99);
		glScalef(1.2, .5, .8);
		glEnable(GL_NORMALIZE);
			glutSolidCube(.5);
		glDisable(GL_NORMALIZE);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(101.25, 0, 99.15);
		glScalef(.1, .5, .1);
		glEnable(GL_NORMALIZE);
			glutSolidCube(.5);
		glDisable(GL_NORMALIZE);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(101.25, 0, 98.85);
		glScalef(.1, .5, .1);
		glEnable(GL_NORMALIZE);
			glutSolidCube(.5);
		glDisable(GL_NORMALIZE);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(100.75, 0, 99.15);
		glScalef(.1, .5, .1);
		glEnable(GL_NORMALIZE);
			glutSolidCube(.5);
		glDisable(GL_NORMALIZE);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(100.75, 0, 98.85);
		glScalef(.1, .5, .1);
		glEnable(GL_NORMALIZE);
			glutSolidCube(.5);
		glDisable(GL_NORMALIZE);
	glPopMatrix();
}