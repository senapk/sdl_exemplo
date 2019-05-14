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
    int r = 100, g = 100, b = 100;
    while(is_open){
        while(SDL_PollEvent(&event)){ 
            if(event.type == SDL_QUIT)
                is_open = false;
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_UP)
                    y -= lado; 
                else if(event.key.keysym.sym == SDLK_DOWN)
                    y += lado;
                else if(event.key.keysym.sym == SDLK_LEFT)
                    x -= lado;
                else if(event.key.keysym.sym == SDLK_RIGHT)
                    x += lado;
            }
            if(event.type == SDL_MOUSEMOTION){
                    x = event.motion.x - lado / 2;
                    y = event.motion.y - lado / 2;
            }

            if(event.type == SDL_MOUSEBUTTONDOWN){
                if (event.button.button == SDL_BUTTON_LEFT){
                    r = rand() % 256;
                    g = rand() % 256;
                    b = rand() % 256;
                } else if(event.button.button == SDL_BUTTON_RIGHT){
                    SDL_ShowSimpleMessageBox(0, "Mouse", "Right button was pressed!", window);
                } else{
                    SDL_ShowSimpleMessageBox(0, "Mouse", "Some other button was pressed!", window);
                }
            }
        }
 
        SDL_SetRenderDrawColor(renderer, BLACK, 255); //muda cor pra preto
        SDL_RenderClear(renderer); //limpa a tela
        
        SDL_SetRenderDrawColor(renderer, r, g, b, 255); //muda cor pra vermelho
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