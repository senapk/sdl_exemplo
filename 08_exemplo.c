#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h> //para sons
#include <stdbool.h>
#include <math.h>

typedef struct{
    float x;
    float y;
    float vx;
    float vy;
    int r; //red
    int g; //green
    int b; //blue
} Ponto;

SDL_Window * window; //janela
SDL_Renderer * renderer; //renderizador do buffer
int largura = 800;
int altura = 600;

//atalhos
#define SET_COLOR(r, g, b) SDL_SetRenderDrawColor(renderer, r, g, b, 255);
#define PLOT(x, y)         SDL_RenderDrawPoint(renderer, x, y)


void show_square(Ponto alien, int lado){
    SET_COLOR(alien.r, alien.g, alien.b);

    for (int l = 0; l < lado; ++l)
        for(int c = 0; c < lado; ++c)
            PLOT(alien.x + c, alien.y + l);
    
    SET_COLOR(255, 255, 255);

    for(int l = 0; l < lado; ++l){
        PLOT(alien.x, alien.y + l);
        PLOT(alien.x + lado, alien.y + l);
    }

    for(int c = 0; c < lado; ++c){
        PLOT(alien.x + c, alien.y);
        PLOT(alien.x + c, alien.y + lado);
    }
}


void quicar_dentro(Ponto * alien, int lado){
    if(alien->y + lado > altura){
        alien->y = altura - lado - 1;
        alien->vy *= -1;
    }
    if(alien->x < 0){
        alien->x = 0;
        alien->vx *= -1;
    }
    if(alien->y < 0){
        alien->y = 0;
        alien->vy *= -1;
    }
    if(alien->x + lado > largura){
        alien->x = largura - lado;
        alien->vx *= -1;        
    }
}

int main(void) {
    srand(time(NULL));
    bool is_open = true;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(largura, altura, 0, &window, &renderer);

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) { //inicializando som
        printf( "Erro no som: %s\n", Mix_GetError()); 
        return 0;
    }

    Mix_Chunk *gRing = NULL;

    gRing = Mix_LoadWAV( "sonic.wav" ); 
    if( gRing == NULL )
        printf( "Error: %s\n", Mix_GetError() );


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


    int qtd = 10;
    int lado = 50;
    float grav = 0.1;
    long int timer = 0;

    Ponto aliens[qtd];

    for(int i = 0; i < qtd; i++){
        aliens[i].x = rand() % (largura - lado);
        aliens[i].y = rand() % (altura - lado);
        aliens[i].vx = (rand() % 11) - 5;
        aliens[i].vy = (rand() % 11) - 5;
        aliens[i].r = rand() % 256;
        aliens[i].g = rand() % 256;
        aliens[i].b = rand() % 256;
    }

    SDL_Event evento;
    int x = 0;
    int y = 0;
    while (is_open) {
        SET_COLOR(50, 50, 50);
        SDL_RenderClear(renderer);
        SET_COLOR(255, 0, 0);
        
        while(SDL_PollEvent(&evento)){
            if(evento.type == SDL_QUIT)
                is_open = false;
            if(evento.type == SDL_KEYDOWN){
                if(evento.key.keysym.sym == SDLK_UP)
                    grav -= 0.1; 
                else if(evento.key.keysym.sym == SDLK_DOWN)
                    grav += 0.1; 
            }
            if(evento.type == SDL_MOUSEMOTION){
                    x = evento.motion.x - lado / 2;
                    y = evento.motion.y - lado / 2;
            }           
        }

        if(SDL_GetTicks() - timer > 10){
            timer = SDL_GetTicks();

            for(int i = 0 ; i < qtd; i++){
                aliens[i].vy += grav;
                
                aliens[i].x += aliens[i].vx;
                aliens[i].y += aliens[i].vy;
            }
        }
        
        for(int i = 0 ; i < qtd; i++)
            quicar_dentro(&aliens[i], lado);

        for(int i = 0 ; i < qtd; i++){
            float dist = sqrt((aliens[i].x - x) * (aliens[i].x - x) + (aliens[i].y - y) * (aliens[i].y - y));
            if(dist < lado)
                Mix_PlayChannel( -1, gRing, 0 );
        }
        
    
        SDL_RenderCopy(renderer, background, NULL, NULL);//tela inteira

        for(int i = 0 ; i < qtd; i++)
            show_square(aliens[i], lado);       

        SDL_RenderCopy(renderer, ship, NULL, &(SDL_Rect){x, y, lado, lado});//posicao tamanho

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
