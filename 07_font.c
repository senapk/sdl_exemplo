//http://gigi.nullneuron.net/gigilabs/displaying-text-in-sdl2-with-sdl_ttf/

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h> //para sons
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <stdio.h>

SDL_Window * window; //janela
SDL_Renderer * renderer; //renderizador do buffer
TTF_Font * font;
int largura = 800;
int altura = 600;

void drawText(const char * text, int r, int g, int b, int x, int y);

int main()
{
    // init SDL
    SDL_Init(SDL_INIT_VIDEO);//inicia o vídeo
    TTF_Init();//inicia o motor de texto
    font = TTF_OpenFont("script12.ttf", 25);

    SDL_CreateWindowAndRenderer(largura, altura, 0, &window, &renderer);

    // gerenciar eventos
    bool is_open = true;
    SDL_Event event;
    while(is_open){
        while(SDL_PollEvent(&event)){ 
            if(event.type == SDL_QUIT)
                is_open = false;
        }
 
        SDL_RenderClear(renderer); //limpa a tela
        drawText("Eu sei escrever meu povo lindo", 255, 255, 255, 200, 300);
        SDL_RenderPresent(renderer); //mostra o buffer na tela
    }
 
    // liberando recursos SDL
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
 
    return 0;
}

void drawText(const char * text, int r, int g, int b, int x, int y){
    SDL_Color color = {r, g, b, 255};
    SDL_Surface * surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { x, y, texW, texH};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}