//headers
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SOIL/SOIL.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include "BIBLIOTECAS/coisas.h"
#include "BIBLIOTECAS/settings.h"
#include "BIBLIOTECAS/sons.h"

//configurações dos valores das fontes de luz, e dos materiais do sol e da lua
GLfloat lightAmb0[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat lightDif0[] = { 1, 1, 1, 1.0 };
GLfloat lightSpec0[] = { 1, 1, 1, 0.0 };
GLfloat lightPos0[4];

GLfloat lightAmb1[] = { .2, .2, .2, 1.0 };
GLfloat lightDif1[] = { .6, .6, .6, 1.0 };
GLfloat lightSpec1[] = { .8, .8, .8, 0.0 };
GLfloat lightPos1[4];

GLfloat lightAmb3[] = { .4, .4, .4, 1.0 };
GLfloat lightDif3[] = { .8, .8, .8, 1.0 };
GLfloat lightSpec3[] = { .5, .5, .5, 0.0 };
GLfloat lightPos3[4] = {100, 1.7, 100, 0};

GLfloat globAmb[] = { .2, .2, .2, 1.0 };
GLint localViewer = 1;

GLfloat sun_diffuse[]	= {1, 1, 0.0};
GLfloat sun_specular[] = {1, 1, 1};	 
GLfloat sun_ambient[] = {1, 1, 0.0};
GLfloat sun_emissive[] = {.05, .05, 0, 0};

GLfloat moon_diffuse[] = {1, 1,  1};
GLfloat moon_specular[] = {1, 1, 1};
GLfloat moon_ambient[] = {1, 1, 1};
GLfloat moon_emissive[] = {0, 0, .05};

//configurações das fontes de luz
void lightSpecs(){
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec0);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 1);

    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDif1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpec1);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 1);

    glLightfv(GL_LIGHT3, GL_AMBIENT, lightAmb3);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, lightDif3);
    glLightfv(GL_LIGHT3, GL_SPECULAR, lightSpec3);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 1);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);        
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, localViewer);
    glShadeModel(GL_SMOOTH);
}

//funcao que desenha o jogo, sol, lua, luzes, casa e objetos
void desenhaJogo(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	if(100*sin(converteRad(anguloSun)) > 0){
		glEnable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, sun_ambient);
	    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, sun_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sun_specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10000);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sun_emissive);
	}
	if(100*sin(converteRad(anguloSun)) < 0){
		glEnable(GL_LIGHT1);
		glDisable(GL_LIGHT0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, moon_ambient);
	 	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, moon_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, moon_specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10000);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, moon_emissive);
	}
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();
		glTranslatef(100 + 100*cos(converteRad(anguloSun)),  -30 + 100*sin(converteRad(anguloSun)), -50 );
			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(0, 0, -1);
				for(int i =0; i <= 300; i++){
					double angle = 2 * M_PI * i / 300;
					double x = 10*cos(angle);
					double y = 10*sin(angle);
					glVertex3f(x, y, 0);
				}
	 	  glEnd();
	glPopMatrix();
	

	glPushMatrix();
	 	glTranslatef((100 + 100*cos(converteRad(anguloMoon))), - 30 + 100*sin(converteRad(anguloMoon)), -50 );
			glBegin(GL_TRIANGLE_FAN);
				glNormal3f(0, 0, -1);
				for(int i =0; i <= 300; i++){
					double angle = 2 * M_PI * i / 300;
					double x = 10*cos(angle);
					double y = 10*sin(angle);
					glVertex3f(x, y, 0);
				}
	 	  	glEnd();
	glPopMatrix();
	
	glPolygonMode(GL_FRONT, GL_FILL);
	glLoadIdentity();
	gluLookAt(posX, posY, posZ, lookatX, lookatY, lookatZ , 0, 1, 0);	
	glPushMatrix();
		desenhaTree();
	glPopMatrix();		
	desenhaChao();
	glEnable(GL_LIGHT3);
		desenhaCasa();
		desenhaMoveis();
		ventilador();
		cadeiras();
		bancada();
	glDisable(GL_LIGHT3);


		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);
		if(100*sin(converteRad(anguloSun)) > 0){
			glColor3f(0, .8, .8);
		}else{
			glColor3f(0, 0, .1);
		}
		glPushMatrix();
			glTranslatef(100, 0, 100);
			glutSolidCube(305);
		glPopMatrix();
		glEnable(GL_LIGHTING);
		glEnable(GL_CULL_FACE);

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glutSwapBuffers();     
}

//funcao que inicializa a resolucao do jogo no inicio da compilacao
//o jogo será tela inteira em qualquer computador
void initResolution(){
	LARG_TELA = glutGet(GLUT_SCREEN_WIDTH);
	ALTR_TELA = glutGet(GLUT_SCREEN_HEIGHT);
	ratio = LARG_TELA / ALTR_TELA;
}

//funcao de inicio, que inicializa todas as texturas, os padroes de desenho que utilizam display lists
//inicializamos também a posição das luzes(sol e lua), que irão variar de acordo com a posição do sol e da lua
void inicio(void){
	glClearColor(1, 1, 1, 0);
	initTree();
	initRoof();
	initGrass();
	initFloor();
	initWall();
	initInsideWall();
	initDoor();
	padraoTree();
	lightSpecs();
	sons();

	glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    posY = 	.4 * (cos(converteRad(bobbing)) + sin(converteRad(bobbing)));
	lookatX = posX;  
	lookatZ = -cos(converteRad(anguloY)) + posZ;
	lightPos0[0] = 100 + 100*cos(converteRad(anguloSun));
	lightPos0[1] = 100*sin(converteRad(anguloSun));
	lightPos0[2] = -100;
	lightPos0[3] = 0;

	lightPos1[0] = 100 + 100*cos(converteRad(anguloMoon));
	lightPos1[1] = 100*sin(converteRad(anguloMoon));
	lightPos1[2] = -100;
	lightPos1[3] = 0;

	Mix_PlayMusic(backgroundSound, -1);
}


//funcao de redimensionamento
void redimensiona(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, ratio, 1, 300);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//funcao que atualiza o jogo 60 vezes por segundo, mudando a posição dos objetos animados e abrindo a porta
void atualiza(int idx) {
	lightPos0[0] = 100 + 100*cos(converteRad(anguloSun));
	lightPos0[1] = 100*sin(converteRad(anguloSun));
	lightPos0[2] = -100;
	lightPos0[3] = 0;

	lightPos1[0] = 100 + 100*cos(converteRad(anguloMoon));
	lightPos1[1] = 100*sin(converteRad(anguloMoon));
	lightPos1[2] = -100;
	lightPos1[3] = 0;

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	anguloSun += .1;
 	anguloMoon+= .1;
 	thetaFan++;
 	if(thetaFan == 360){
 		thetaFan = 0;
 	}
 	if(openDoor == 1 && thetaDoor >= -140){
 		thetaDoor -= 4;
 	}else if(openDoor == -1 && thetaDoor <= -1){
 		thetaDoor += 4;
 	}

 	if(thetaDoor == 0 || thetaDoor == -140){
 		openDoor = 0;
 	}
  	glutPostRedisplay();
    glutTimerFunc(17, atualiza, 0);
}

//funcao que é responsável pela movimentação da câmera
void pressionaSeta(int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP: lookatY += .1;
		break;
		case GLUT_KEY_DOWN: lookatY -= .1;
		break;
		case GLUT_KEY_LEFT: anguloY -= 5.5;
							lookatX =  sin(converteRad(anguloY)) + posX;
							lookatZ = -cos(converteRad(anguloY)) + posZ;
		break;
		case GLUT_KEY_RIGHT: anguloY += 5.5;
							lookatX =  sin(converteRad(anguloY)) + posX;
							lookatZ = -cos(converteRad(anguloY)) + posZ;
		break;
	}
}

//funcao que é responsável pela movimentação do "personagem", e da abertura/fechamento da porta
void entra(unsigned char key, int x, int y){
	switch(key){
		case 27:
			exit(0);
		break;
		case 'w':
		case 'W':
			posZ    -= 	.1 * cos(converteRad(anguloY));
			lookatZ -=  .1 * cos(converteRad(anguloY));
			bobbing += sinal * 1;
			if(bobbing > 15 || bobbing < 0){
				sinal *= -1;
			}
			posY =  .4 * (cos(converteRad(bobbing)) + sin(converteRad(bobbing)));
			posX    += 	.1 * sin(converteRad(anguloY));
			lookatX += 	.1 * sin(converteRad(anguloY));
		break;

		case 's':
		case 'S':
			posZ    += 	.1 * cos(converteRad(anguloY));
			lookatZ +=  .1 * cos(converteRad(anguloY));
			bobbing += sinal * 1;
			if(bobbing > 15 || bobbing < 0){
				sinal *= -1;
			}
			posY =  .4 * (cos(converteRad(bobbing)) + sin(converteRad(bobbing)));
			posX    -= 	.1 * sin(converteRad(anguloY));
			lookatX -= 	.1 * sin(converteRad(anguloY));
		break;
		case 'm':
		case 'M':
			openDoor = 1;
			Mix_PlayChannel(-1, efeitoOpen, 0);
			break;
		case 'n':
		case 'N':
			openDoor = -1;
			Mix_PlayChannel(-1, efeitoClose, 0);
			break;

	}
}

//main
int main(int argc, char **argv){
	srand(time(0));
	glutInit(&argc, argv);
	initResolution();
    
	glutInitContextVersion(1,1);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(LARG_TELA, ALTR_TELA); 
	glutInitWindowPosition(0, 0);
	glutCreateWindow("House");
	inicio();
		
	glutTimerFunc(0, atualiza, 0);
	glutDisplayFunc(desenhaJogo);
	glutReshapeFunc(redimensiona);
	glutKeyboardFunc(entra);
	glutSpecialFunc(pressionaSeta);
	

	glutMainLoop();
	return 0;
}
