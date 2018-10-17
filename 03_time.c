#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>


SDL_Window * window; //janela
SDL_Renderer * renderer; //renderizador do buffer
int largura = 800;
int altura = 600;

void draw_square(int x, int y, int lado);

#define BLACK 0, 0, 0
#define RED 255, 0, 0

int main()
{
    int timer = SDL_GetTicks();
    // init SDL
    SDL_Init(SDL_INIT_VIDEO);//inicia o vídeo
    SDL_CreateWindowAndRenderer(largura, altura, 0, &window, &renderer);

    //variaveis do quadrado
    int x = 200;
    int y = 200;
    int lado = 100;

    // gerenciar eventos
    bool is_open = true;
    SDL_Event event;
    while(is_open){
        while(SDL_PollEvent(&event)){ 
            if(event.type == SDL_QUIT)
                is_open = false;
        }

        if(SDL_GetTicks() - timer > 500){ //passou meio segundo
            timer = SDL_GetTicks(); //reseta tempo
            x -= lado;
            if(x < 0)
                x += largura; //dar a volta
        }
 
        SDL_SetRenderDrawColor(renderer, BLACK, 255); //muda cor pra preto
        SDL_RenderClear(renderer); //limpa a tela
        
        SDL_SetRenderDrawColor(renderer, RED, 255); //muda cor pra vermelho
        draw_square(x, y, lado); //desenha um quadrado
        
        SDL_RenderPresent(renderer); //mostra o buffer na tela
    }
 
    // liberando recursos SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
 
    return 0;
}

void draw_square(int x, int y, int lado){
    for (int l = 0; l < lado; ++l)
        for(int c = 0; c < lado; ++c)
            SDL_RenderDrawPoint(renderer, x + c, y + l); //plota esse pixel
}