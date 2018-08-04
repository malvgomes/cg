#include <GL/glew.h>
#include <GL/freeglut.h>

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include "BIBLIOTECAS/som.h"

//inicializa os sons de jogo
void sons(){
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	backgroundSound = Mix_LoadMUS("SONS/d_e1m1.mp3");
	menuSound = Mix_LoadMUS("SONS/d_inter.mp3");
	efeitoDor = Mix_LoadWAV("SONS/dsdmpain.wav");
	efeitoEat = Mix_LoadWAV("SONS/dsgetpow.wav");
	efeitoMenu = Mix_LoadWAV("SONS/dswpnup.wav");
	efeitoEnter = Mix_LoadWAV("SONS/dspistol.wav");
	gameover = Mix_LoadMUS("SONS/gameover.mp3");
}