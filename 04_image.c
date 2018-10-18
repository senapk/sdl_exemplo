#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>


SDL_Window * window; //janela
SDL_Renderer * renderer; //renderizador do buffer
int largura = 800;
int altura = 600;

#define BLACK 0, 0, 0
#define RED 255, 0, 0

void draw_square(int x, int y, int lado){
    for (int l = 0; l < lado; ++l)
        for(int c = 0; c < lado; ++c)
            SDL_RenderDrawPoint(renderer, x + c, y + l); //plota esse pixel
}

int main()
{
    // init SDL
    SDL_Init(SDL_INIT_VIDEO);//inicia o vídeo
    SDL_CreateWindowAndRenderer(largura, altura, 0, &window, &renderer);

    SDL_Texture * ship, *background;
    {
        SDL_Surface * image = SDL_LoadBMP("ship.bmp");
        ship = SDL_CreateTextureFromSurface(renderer, image);
        SDL_FreeSurface(image);
    }
    {
        SDL_Surface * image = SDL_LoadBMP("background.bmp");
        background = SDL_CreateTextureFromSurface(renderer, image);
        SDL_FreeSurface(image);
    }
    
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
            if(event.type == SDL_MOUSEMOTION){
                x = event.motion.x - lado/2;//no meio da posicao do mouse
                y = event.motion.y - lado/2;
            }
        }
 
        SDL_SetRenderDrawColor(renderer, BLACK, 255); //muda cor pra preto
        SDL_RenderClear(renderer); //limpa a tela
        
        SDL_RenderCopy(renderer, background, NULL, NULL);//tela inteira
        draw_square(x, y, lado);
        SDL_RenderCopy(renderer, ship, NULL, &(SDL_Rect){x, y, lado, lado});//posicao tamanho

        SDL_RenderPresent(renderer); //mostra o buffer na tela
    }
 
    // liberando recursos SDL
    SDL_DestroyTexture(ship);
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
 
    return 0;
}