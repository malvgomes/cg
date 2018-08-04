#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>

GLfloat thetaDoor;
GLfloat thetaFan;
GLfloat LARG_TELA;
GLfloat ALTR_TELA;
GLfloat ratio;
GLfloat posX;
GLfloat posY;
GLfloat posZ;
GLfloat lookatX;
GLfloat lookatY;
GLfloat lookatZ;
GLfloat anguloY;
GLfloat anguloSun;
GLfloat anguloMoon;
GLfloat bobbing;
GLint sinal;
GLint openDoor;

//lista encadeada de árvores
typedef struct tree{
	GLdouble posX;
	GLdouble posY;
	GLdouble posZ;
	struct tree *next;
}tree;

tree *arvores;

GLfloat converteRad(GLfloat theta);
GLfloat distanciaEntrePontos(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
GLfloat norma(GLfloat x, GLfloat y);
GLfloat produtoEscalar(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
GLfloat anguloEntreVetores(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
