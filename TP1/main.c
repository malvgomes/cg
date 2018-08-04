//headers
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "BIBLIOTECAS/player.h"
#include "BIBLIOTECAS/settings.h"
#include "BIBLIOTECAS/food.h"
#include "BIBLIOTECAS/projetil.h"
#include "BIBLIOTECAS/som.h"
#include "BIBLIOTECAS/hudfundo.h"
#include "BIBLIOTECAS/telas.h"

#include <SOIL/SOIL.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

GLint play = 1;

//enums para evitar numeros magicos
enum Tela {MENU, JOGO, PAUSE, GAMEOVER};
enum Menu {TITLE, VAZIO, JOGAR, CREDITOS, SAIR, CREDITOSTELA};
enum Pause {VAZIOPAUSE, REINICIAR, SAIRPAUSE};

//incializamos a tela inicial como sendo a de menu, o menu atual somente com o titulo do jogo, sem os menus
//pause atual é a tela de pause vazia, sem nenhuma opcao selecionada
GLint telaAtual = MENU;
GLint menuAtual = TITLE;
GLint pauseAtual = VAZIOPAUSE;

//caso o tamanho do jogador fique muito pequeno, essa funcao termina o jogo, mandando para a tela de gameover, 
//tocando a musica de gameover
void testaGameOver(){
	if(player.raio < 5){
		telaAtual = GAMEOVER;
	Mix_HaltMusic();
	Mix_PlayMusic(gameover, -1);
	}
}

//inicializa as caracteristicas do jogador, das "comidas" e dos projeteis na tela
void inicializaJogo(){
	initPlayer();
	initFood();
	initProjetil();
}

//limpa a lista de projeteis e de comidas, funcao usada quando o jogo e reiniciado, evitando assim uso excessivo de memoria
void resetaJogo(){
	resetProjetil();
	resetFood();
	PONTUACAO[0] = 0;
	PONTUACAO[1] = 0;
	PONTUACAO[2] = 0;
}

//Função desenho, irá desenhar algo diferente de acordo com a tela atual
//nota-se que no menu, pause e gameover passamos o estado atual como parametro, pois
//a tela é selecionada de acordo com o menu que esta prestes a ser selecionado
void desenhaJogo(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if(telaAtual == MENU){
		desenhaTela(menuAtual);
	}else if(telaAtual == JOGO){
		desenhaFundo();
	 	desenhaProjetil();	
		desenhaFood();
		desenhaPlayer();
		desenhaHUD();
	}else if(telaAtual == PAUSE){
		desenhaTela(pauseAtual + 6);
	}else if(telaAtual == GAMEOVER){
		desenhaTela(9);
	}

	glutSwapBuffers();     
}

//funcao que inicializa a resolucao do jogo no inicio da compilacao
//o jogo sera tela inteira em qualquer computador
void initResolution(){
	LARG_TELA = glutGet(GLUT_SCREEN_WIDTH);
	ALTR_TELA = glutGet(GLUT_SCREEN_HEIGHT);
}

//funcao de inicio, que inicializa todas as texturas, os padroes de desenho, usando display lists, e os sons de jogo
//nota-se que a musica de menu comeca a tocar na inicializacao do jogo
void inicio(void){
	glClearColor(0, 0, 0, 0);

	//texturas
	initTelas();
	initComida();
	initDemon();
	initHUDFundo();
	initBullet();
	initPlayer();

	//display lists
	padraoHUD();
	padraoFundo();
	padraoJogador();
	padraoComida();
	padraoProjetil();
	padraoFundo();
	padraoTela();

	//musicas e efeitos sonoros
	sons();
	Mix_PlayMusic(menuSound, -1);
}

//funcao de redimensionamento, que define tambem o tamanho do mundo, que é do tamanho da tela do usuario
void redimensiona(int w, int h){

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, LARG_TELA, 0, ALTR_TELA, -1, 1); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

//funcao que atualiza o jogo 60 vezes por segundo
void atualiza(int idx) {

	if(telaAtual == JOGO){
		if(pressX != 0){
			//acelera o jogador na direcao X, dependendo da direcao que o jogador está movendo
			aceleraPlayerX();
		}else{
			//caso o jogador não esteja mais apertando a tecla de movimento, desacelera o jogador
			desaceleraPlayerX();
		}
		//igual a anterior, mas na direção y
		if(pressY != 0){
			aceleraPlayerY();
		}else{
			desaceleraPlayerY();
		}

		//faz o jogador perder uma quantidade pequena de massa com o tempo, obrigando-o a comer
		perdeMassa();
		//remove os projeteis que saem da tela de jogo
		removeProjetil();
		//move os projeteis na tela
		moveProjetil();
		//move o jogador de acordo com sua velocidade
		movePlayer();
		//bloqueia a saida do jogador da tela de jogo
		impedePlayer();
		//detecta colisao com as comidas
		detectaColisao();
		//detecta colisao com os projeteis
		detectaColisaoProjetil();
		//spawna projeteis com o passar do tempo
	 	spawnProjetil();
	 	//remove as comidas que entram em contato com o jogador
		removeFood();
		//testa se o raio do jogaror é pequeno o suficiente para acabar o jogo
		testaGameOver();
	}
  	

  	glutPostRedisplay();
    glutTimerFunc(17, atualiza, 0);
}

//funcao que, alem de ser responsavel pelo movimento do jogador, é responsavel pela navegação dos menus
void pressionaSeta(int key, int x, int y){
	switch(key){
			//move o jogador para cima, se estiver em jogo
			//e move os menus para cima, se nos menus, ou pause
			case GLUT_KEY_UP:	pressY = 1;
				if(telaAtual == MENU && menuAtual > VAZIO && menuAtual != CREDITOSTELA){
					menuAtual--;
					Mix_PlayChannel(-1, efeitoMenu, 0);
				}else if(telaAtual == PAUSE && pauseAtual > VAZIOPAUSE){
					pauseAtual--;
					Mix_PlayChannel(-1, efeitoMenu, 0);
				}
				break;
				//move o jogador para os lados e não altera os menus, pois não há menus laterais
			case GLUT_KEY_LEFT: 	pressX = -1;
				break;
			case GLUT_KEY_RIGHT:	pressX = 1;
				break;
				//move o jogador para baixo, se em jogo
				//e move menus para baixo
			case GLUT_KEY_DOWN:		pressY = -1;
				if(telaAtual == MENU && menuAtual < SAIR && menuAtual != CREDITOSTELA){
					menuAtual++;
					Mix_PlayChannel(-1, efeitoMenu, 0);
				}else if(telaAtual == PAUSE && pauseAtual < SAIRPAUSE){
					pauseAtual++;
					Mix_PlayChannel(-1, efeitoMenu, 0);
				}
				break;		
	}
}

//desabilita os estados de pressionamento, quando o jogador solta a seta direcional
void soltaSeta(int key, int x, int y){
	switch(key){
			case GLUT_KEY_UP: pressY = 0;
				break;
			case GLUT_KEY_LEFT: pressX = 0;
				break;
			case GLUT_KEY_RIGHT: pressX = 0;
				break;
			case GLUT_KEY_DOWN: pressY = 0;
				break;
	}
}

//funcao que permite a seleção nos menus
void entra(unsigned char key, int x, int y){
	switch(key){
		//caso enter
		case 13:
			//caso o menu seja sair, sai do jogo
			if((telaAtual == MENU) && (menuAtual == SAIR)){
				Mix_PlayChannel(-1, efeitoEnter, 0);
				exit(0);
			//se o menu estiver em jogar, entra na tela de jogo e toca a musica de jogo
			}else if((telaAtual == MENU) && (menuAtual == JOGAR)){
				Mix_HaltMusic();
				Mix_PlayChannel(-1, efeitoEnter, 0);
				Mix_PlayMusic(backgroundSound, -1);
				inicializaJogo();
				telaAtual = JOGO;
			//se o menu atual for o de creditos, vai para a tela de creditos
			}else if((telaAtual == MENU) && (menuAtual == CREDITOS)){
				Mix_PlayChannel(-1, efeitoEnter, 0);
				menuAtual = CREDITOSTELA;
			//se a tela atual for de pause, e a selecao estiver em reiniciar, renicia o jogo
			}else if ((telaAtual == PAUSE) && (pauseAtual == REINICIAR)){
				Mix_PlayChannel(-1, efeitoEnter, 0);
				pauseAtual = VAZIOPAUSE;
				telaAtual = JOGO;
				resetaJogo();
				inicializaJogo();
			//se estiver em pause, e na opcao sair, volta para o menu inicial
			}else if((telaAtual == PAUSE) && (pauseAtual == SAIRPAUSE)){
				Mix_HaltMusic();
				Mix_PlayMusic(menuSound, -1);
				Mix_PlayChannel(-1, efeitoEnter, 0);
				pauseAtual = VAZIOPAUSE;
				menuAtual = TITLE;
				telaAtual = MENU;
				resetaJogo();
			//se a tela for gameover, volta para o menu inicial
			}else if(telaAtual == GAMEOVER){
				resetaJogo();
				Mix_HaltMusic();
				Mix_PlayMusic(menuSound, -1);
				Mix_PlayChannel(-1, efeitoEnter, 0);
				telaAtual = MENU;
				menuAtual = VAZIO;
			}
		break;
		//caso p, vai para a tela de pause, ou sai da tela de pause
		case 'p':
		case 'P':
			if(telaAtual == JOGO){
				telaAtual = PAUSE;
			}else if(telaAtual == PAUSE){
				telaAtual = JOGO;
			}
		break;
		//caso esc na tela de creditos, volta para o menu principal
		case 27:
			if(menuAtual == CREDITOSTELA){
				menuAtual = TITLE;
			}
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
	glutCreateWindow("AGARDOOM");
	inicio();
		
	glutTimerFunc(0, atualiza, 0);
	glutDisplayFunc(desenhaJogo);
	glutReshapeFunc(redimensiona);
	glutKeyboardFunc(entra);
	glutSpecialFunc(pressionaSeta);
	glutSpecialUpFunc(soltaSeta);
	

	glutMainLoop();
	return 0;
}
