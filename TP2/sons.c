#include <GL/glew.h>
#include <GL/freeglut.h>

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include "BIBLIOTECAS/sons.h"

//inicializa os sons de jogo
void sons(){
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	backgroundSound = Mix_LoadMUS("SONS/home.mp3");
	efeitoOpen = Mix_LoadWAV("SONS/door-1-open.wav");
	efeitoClose = Mix_LoadWAV("SONS/door-1-close.wav");
}