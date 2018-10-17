//http://lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h> //para sons

#include <stdbool.h>
#include <stdio.h>

SDL_Window * window; //janela
SDL_Renderer * renderer; //renderizador do buffer
int largura = 800;
int altura = 600;



int main()
{
    // init SDL
    SDL_Init(SDL_INIT_VIDEO);//inicia o vídeo
    SDL_CreateWindowAndRenderer(largura, altura, 0, &window, &renderer);

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) { //inicializando som
        printf( "Erro no som: %s\n", Mix_GetError()); 
        return 0;
    }

    Mix_Music *gMusic = NULL;
    Mix_Chunk *gRing = NULL;

    gMusic = Mix_LoadMUS( "hollow.wav" ); //if gMusic == NULL deu erro
    if( gMusic == NULL )
        printf( "Error: %s\n", Mix_GetError());

    gRing = Mix_LoadWAV( "sonic.wav" ); 
    if( gRing == NULL )
        printf( "Error: %s\n", Mix_GetError() );

    

    // gerenciar eventos
    bool is_open = true;
    SDL_Event event;

    SDL_ShowSimpleMessageBox(0, "Readme", "tecle SPACE(ring) ou ENTER(Music/play/pause)", window);

    while(is_open){
        while(SDL_PollEvent(&event)){ 
            if(event.type == SDL_QUIT)
                is_open = false;
            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case(SDLK_SPACE):
                        Mix_PlayChannel( -1, gRing, 0 );
                        break;
                    case(SDLK_RETURN):
                        if( Mix_PlayingMusic() == 0 )//musica ainda nao esta tocando 
                            Mix_PlayMusic( gMusic, -1 ); //coloque pra tocar
                        else { //musica ja iniciou
                            if( Mix_PausedMusic() == 1 ) //se esta pausada 
                                Mix_ResumeMusic();  //continue
                            else
                                Mix_PauseMusic(); //pause
                        }
                        break;
                }
            }
        }
 
        SDL_RenderClear(renderer); //limpa a tela
        SDL_RenderPresent(renderer); //mostra o buffer na tela
    }
 
    // liberando recursos SDL
    Mix_FreeMusic(gMusic);
    Mix_FreeChunk(gRing);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
 
    return 0;
}