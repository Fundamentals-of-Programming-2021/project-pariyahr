#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#include <string.h>

#define FPS 60
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900
#define length 100 
#include "map.h"

void shownumber(SDL_Renderer *sdlRenderer, double x, double y, double w, double h, int fontsize, int R, int G, int B, int A, const char *n){
    TTF_Font *font = TTF_OpenFont("..//fonts//LiberationSerif-Regular.ttf", fontsize);
    SDL_Color textcolor = {R, G, B, A};
    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(font, n, textcolor);
    SDL_Texture *Message = SDL_CreateTextureFromSurface(sdlRenderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.x = x;
    Message_rect.y = y;
    Message_rect.w = w;
    Message_rect.h = h;
    SDL_RenderCopy(sdlRenderer, Message, NULL, &Message_rect);
    SDL_DestroyTexture(Message);
    TTF_CloseFont(font);
}

void showimage(SDL_Renderer *sdlRenderer, char *image_path, int x, int y, int w, int h){
    SDL_Surface *image = SDL_LoadBMP(image_path);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(sdlRenderer, image);
    SDL_FreeSurface(image);
    image = NULL;
    SDL_Rect texture_rect = {.x = x, .y = y, .w = w, .h = h};
    SDL_RenderCopy(sdlRenderer, texture, NULL, &texture_rect);
    SDL_DestroyTexture(texture);
}

int showmenu(SDL_Renderer *sdlRenderer){
    SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(sdlRenderer);
    Uint32 time;
    int x, y;
    int nummenu=3;
    char labels[nummenu][10];
    labels[0][0]='n';labels[0][1]='e';labels[0][2]='w';labels[0][3]=' ';labels[0][4]='g';labels[0][5]='a';labels[0][6]='m';labels[0][7]='e';labels[0][8]='\0';
    labels[1][0]='s';labels[1][1]='t';labels[1][2]='a';labels[1][3]='t';labels[1][4]='e';labels[1][5]='.';labels[1][6]='i';labels[1][7]='o';labels[1][8]='\0';
    labels[2][0]='r';labels[2][1]='a';labels[2][2]='n';labels[2][3]='k';labels[2][4]='s';labels[2][5]='\0';
    bool selected[nummenu];
    for (int i=0; i<nummenu; i++){
        selected[i]=0;
    }
    int pos[nummenu][4];
    pos[0][0]=350; pos[0][1]=400; pos[0][2]=200; pos[0][3]=30;
    pos[1][0]=255; pos[1][1]=100; pos[1][2]=400; pos[1][3]=80;
    pos[2][0]=370; pos[2][1]=450; pos[2][2]=170; pos[2][3]=40;
    showimage(sdlRenderer,"..//images//7.bmp", 0, 0, 900, 900);
    for (int i=0; i<nummenu; i++)
        shownumber(sdlRenderer, pos[i][0], pos[i][1], pos[i][2], pos[i][3], 50, 0, 0, 0, 255, labels[i]);
    SDL_RenderPresent(sdlRenderer);
    
    SDL_Event event;
    while (1){
       // time=SDL_GetTicks();
        while(SDL_PollEvent(&event)){
            switch (event.type){
            case SDL_QUIT:
                return 5;
                break;
            case SDL_MOUSEBUTTONDOWN:
                for (int i=0; i<nummenu; i++){
                    if (event.button.x>=pos[i][0] && event.button.x<=pos[i][0]+pos[i][2] &&  event.button.y>=pos[i][1] && event.button.y<=pos[i][1]+pos[i][3]){
                        return i;
                    }
                }
                break;
            }
        }
        SDL_Delay(1000/FPS);
    }
}

int showmaps(SDL_Renderer *sdlRenderer){
    int nummenu=5;
    char labels[nummenu][12];
    labels[4][0]='s';labels[4][1]='t';labels[4][2]='a';labels[4][3]='t';labels[4][4]='e';labels[4][5]='.';labels[4][6]='i';labels[4][7]='o';labels[4][8]='\0';
    labels[0][0]='r';labels[0][1]='a';labels[0][2]='n';labels[0][3]='d';labels[0][4]='o';labels[0][5]='m';labels[0][6]=' ';labels[0][7]='m';labels[0][8]='a';labels[0][9]='p';labels[0][10]='\0';
    labels[1][0]='m';labels[1][1]='a';labels[1][2]='p';labels[1][3]='1';labels[1][4]='\0';
    labels[2][0]='m';labels[2][1]='a';labels[2][2]='p';labels[2][3]='2';labels[2][4]='\0';
    labels[3][0]='m';labels[3][1]='a';labels[3][2]='p';labels[3][3]='3';labels[3][4]='\0';
    int pos[nummenu][4];
    pos[4][0]=255; pos[4][1]=100; pos[4][2]=400; pos[4][3]=80;
    pos[0][0]=300; pos[0][1]=300; pos[0][2]=300; pos[0][3]=50;
    pos[1][0]=400; pos[1][1]=350; pos[1][2]=100; pos[1][3]=40;
    pos[2][0]=400; pos[2][1]=400; pos[2][2]=100; pos[2][3]=40;
    pos[3][0]=400; pos[3][1]=450; pos[3][2]=100; pos[3][3]=40;
    SDL_bool shallExit = SDL_FALSE;
    while (shallExit==SDL_FALSE){
        SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(sdlRenderer);
        showimage(sdlRenderer,"..//images//7.bmp", 0, 0, 900, 900);
        for (int i=0; i<nummenu; i++)
            shownumber(sdlRenderer, pos[i][0], pos[i][1], pos[i][2], pos[i][3], 50, 0, 0, 0, 255, labels[i]);
        SDL_RenderPresent(sdlRenderer);
        SDL_Event newevent;
        while (SDL_PollEvent(&newevent)){
            switch (newevent.type){
            case SDL_QUIT:
                shallExit=SDL_TRUE;
                break;
            case SDL_MOUSEBUTTONDOWN:
                for (int i=0; i<nummenu; i++){
                    if (newevent.button.x>=pos[i][0] && newevent.button.x<=pos[i][0]+pos[i][2] &&  newevent.button.y>=pos[i][1] && newevent.button.y<=pos[i][1]+pos[i][3]){
                        return i;
                    }
                }
                break;
            }
        }
    }
}

void showranks(SDL_Renderer *sdlRenderer, char *ranks[5], int points[5], int index){
    SDL_bool shallExit = SDL_FALSE;
    int poss[4];
    char labels[1][9];
    labels[0][0]='s';labels[0][1]='t';labels[0][2]='a';labels[0][3]='t';labels[0][4]='e';labels[0][5]='.';labels[0][6]='i';labels[0][7]='o';labels[0][8]='\0';
    poss[0]=255; poss[1]=100; poss[2]=400; poss[3]=80;
    while (shallExit==SDL_FALSE){
        SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(sdlRenderer);
        showimage(sdlRenderer,"..//images//7.bmp", 0, 0, 900, 900);
        int pos[10][4];
        pos[0][0]=350; pos[0][1]=300; pos[0][2]=100; pos[0][3]=40;
        pos[1][0]=350; pos[1][1]=350; pos[1][2]=100; pos[1][3]=40;
        pos[2][0]=350; pos[2][1]=400; pos[2][2]=100; pos[2][3]=40;
        pos[3][0]=350; pos[3][1]=450; pos[3][2]=100; pos[3][3]=40;
        pos[4][0]=350; pos[4][1]=500; pos[4][2]=100; pos[4][3]=40;
        pos[5][0]=500; pos[5][1]=300; pos[5][2]=15; pos[5][3]=30;
        pos[6][0]=500; pos[6][1]=350; pos[6][2]=15; pos[6][3]=30;
        pos[7][0]=500; pos[7][1]=400; pos[7][2]=15; pos[7][3]=30;
        pos[8][0]=500; pos[8][1]=450; pos[8][2]=15; pos[8][3]=30;
        pos[9][0]=500; pos[9][1]=500; pos[9][2]=15; pos[9][3]=30;
        for (int i=0; i<index; i++){
            char *n=malloc(sizeof(char)*5);
            sprintf(n, "%d", points[i]);
            shownumber(sdlRenderer, pos[i][0], pos[i][1], pos[i][2], pos[i][3], 50, 0, 0, 0, 255, ranks[i]);
            shownumber(sdlRenderer, pos[i+5][0], pos[i+5][1], pos[i+5][2], pos[i+5][3], 30, 0, 0, 0, 255, n);
        }
        shownumber(sdlRenderer, poss[0], poss[1], poss[2], poss[3], 50, 0, 0, 0, 255, labels[0]);
        SDL_RenderPresent(sdlRenderer);
        SDL_Event newevent;
        while (SDL_PollEvent(&newevent)){
            switch (newevent.type){
            case SDL_QUIT:
                shallExit=SDL_TRUE;
                break;
            }
        }
    }
}

void draw(SDL_Renderer *sdlRenderer,int j, int i, Uint32 color){
    Sint16 vx[] = {i, i+length/2, i+length+length/2, i+2*length, i+length+length/2, i+length/2};
    Sint16 vy[] = {j, j-(length/2*sqrt(3)), j-(length/2*sqrt(3)), j, j+(length/2*sqrt(3)), j+(length/2*sqrt(3))};
    filledPolygonColor(sdlRenderer, vx, vy, 6, color);
    aapolygonColor(sdlRenderer, vx, vy, 6, 0xFF000000);
    if (color==0xcca48187 || color==0xcca48100 || color==0xcc718b3c || color==0xcc787878){
        filledCircleColor(sdlRenderer, i+length, j, length/4, color+0x33000000);
    }
}

void drawsolds(SDL_Renderer *sdlRenderer, int x, int y, Uint32 color){
    filledCircleColor(sdlRenderer, x, y, length/10, color+0x33000000);
}

int findhex(Sint32 x, Sint32 y, int counter2, struct map map[32]){
    int min=(y-map[0].y)*(y-map[0].y) + (x-map[0].x-length)*(x-map[0].x-length);
    int numb=0;
    for (int i=1; i<counter2; i++){
        if (((y-map[i].y)*(y-map[i].y) + (x-map[i].x-length)*(x-map[i].x-length)) < min){
            min = (y-map[i].y)*(y-map[i].y) + (x-map[i].x-length)*(x-map[i].x-length);
            numb=i;
        }
    }
    return numb;
}

void attack(SDL_Renderer *sdlRenderer, int number, int start, int stop, int counter2, double dx, double dy, struct map map[32], int dspeed, double solds[counter2*3][1000][3], int counter5, int attackstate[counter2][counter2][5]){
    double speed=dspeed;
    for (int i=0; i<number; i++){
        if (solds[counter5][i][0]>0){
            if (solds[counter5][i][0]==1){
                map[start].num--;
            }
            solds[counter5][i][1]+=(dx/speed);
            solds[counter5][i][2]+=(dy/speed);
            drawsolds(sdlRenderer, solds[counter5][i][1], solds[counter5][i][2], map[start].color); 
            if (solds[counter5][i][1]-map[stop].x-length<50 && solds[counter5][i][2]-map[stop].y<50 && solds[counter5][i][1]-map[stop].x-length>-50 && solds[counter5][i][2]-map[stop].y>-50){
                solds[counter5][i][0]=-10000;
                if (map[start].color!=map[stop].color && map[stop].num>0){
                    map[stop].num--;
                }
                else {
                    map[stop].color=map[start].color;
                    map[stop].num++;
                }
            }
        }
    }
    int counter6 = 0;
    for (int j=0; j<number; j++){
        if (solds[counter5][j][0]==-10000){
            counter6++;
        }
    }
    if (counter6==number){
        attackstate[start][stop][0]=0;
    }
    for (int j=0; j<number; j++){
        if (solds[counter5][j][0]!=-10000)
            solds[counter5][j][0]++;
    }
}

char* name(SDL_Renderer *sdlRenderer){
    char *inname=malloc(sizeof(char)*11);
    char labels[2][11];
    int pos[2][4];
    pos[0][0]=255; pos[0][1]=100; pos[0][2]=400; pos[0][3]=80;
    pos[1][0]=255; pos[1][1]=200; pos[1][2]=400; pos[1][3]=80;
    labels[0][0]='s';labels[0][1]='t';labels[0][2]='a';labels[0][3]='t';labels[0][4]='e';labels[0][5]='.';labels[0][6]='i';labels[0][7]='o';labels[0][8]='\0';
    labels[1][0]='e';labels[1][1]='n';labels[1][2]='t';labels[1][3]='e';labels[1][4]='r';labels[1][5]=' ';labels[1][6]='n';labels[1][7]='a';labels[1][8]='m';labels[1][9]='e';labels[1][10]=':';labels[1][11]='\0';
    SDL_bool shallExit = SDL_FALSE;
    inname[0]='\0';
    char ch;
    while (shallExit==SDL_FALSE){
        SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(sdlRenderer);
        showimage(sdlRenderer,"..//images//7.bmp", 0, 0, 900, 900);
        int len=strlen(inname);
        shownumber(sdlRenderer, pos[0][0], pos[0][1], pos[0][2], pos[0][3], 50, 0, 0, 0, 255, labels[0]);
        shownumber(sdlRenderer, pos[1][0], pos[1][1], pos[1][2], pos[1][3], 50, 0, 0, 0, 255, labels[1]);
        shownumber(sdlRenderer, 410-len*10, 450, len*30, 30, 30, 0, 0, 0, 255, inname);
        SDL_RenderPresent(sdlRenderer);
        SDL_Event newevent;
        while (SDL_PollEvent(&newevent)){
            len=strlen(inname);
            switch (newevent.type){
            case SDL_QUIT:
                return NULL;
                break;
            case SDL_KEYUP:
                switch(newevent.key.keysym.sym){
                case SDLK_RETURN:
                    if (strlen(inname)>0){
                    return inname;
                    }
                    break;
                case SDLK_SPACE:
                    ch = ' ';
                    break;
                case SDLK_BACKSPACE:
                    ch = ' ';
                        if (len>0){
                        inname[len-1]='\0';
                        }
                    break;
                default:
                    if (newevent.key.keysym.sym != SDLK_UP && newevent.key.keysym.sym != SDLK_DOWN && newevent.key.keysym.sym != SDLK_LEFT && newevent.key.keysym.sym != SDLK_RIGHT){
                        ch = newevent.key.keysym.sym;
                    }
                        break;
                }
                if (strlen(inname)<=10){
                    if ((ch>='a' && ch<='z') || (ch>='A' && ch<='Z')){
                        inname[len]=ch;
                        inname[len+1]='\0';
                    }
                }
                break;
            }
        }
    }
}