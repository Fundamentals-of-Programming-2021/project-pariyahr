#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#include <string.h>

const int FPS = 60;
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 900;
const int length = 100;
char* inname[5];
int count=0;
int scores[5]={0,0,0,0,0};

struct map{
    int x;
    int y;
    Uint32 color;
    int num;
    int avpo;
};

void shownumber(SDL_Renderer *sdlRenderer, double x, double y, double w, double h, int fontsize, int R, int G, int B, int A, const char *n){
    TTF_Font *font = TTF_OpenFont("//home//paria//Desktop//state.io//fonts//LiberationSerif-Regular.ttf", fontsize);
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

void showimage(SDL_Renderer *renderer, char *image_path, int x0, int y0, int w0, int h0){
    SDL_Surface *image = SDL_LoadBMP(image_path);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = NULL;
    SDL_Rect texture_rect = {.x = x0, .y = y0, .w = w0, .h = h0};
    SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
    SDL_DestroyTexture(texture);
}

int showmenu(SDL_Renderer *sdlRenderer){
    //showimage(sdlRenderer,"//home//paria//Desktop//state.io//images//6.bmp", 450, 450, 900, 900);
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
    pos[2][0]=370; pos[2][1]=500; pos[2][2]=170; pos[2][3]=40;
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

void showranks(SDL_Renderer *sdlRenderer){
    SDL_bool shallExit = SDL_FALSE;
    while (shallExit==SDL_FALSE){
        SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(sdlRenderer);
        int pos[10][4];
        pos[0][0]=200; pos[0][1]=300; pos[0][2]=100; pos[0][3]=40;
        pos[1][0]=200; pos[1][1]=350; pos[1][2]=100; pos[1][3]=40;
        pos[2][0]=200; pos[2][1]=400; pos[2][2]=100; pos[2][3]=40;
        pos[3][0]=200; pos[3][1]=450; pos[3][2]=100; pos[3][3]=40;
        pos[4][0]=200; pos[4][1]=500; pos[4][2]=100; pos[4][3]=40;
        pos[4][0]=400; pos[4][1]=300; pos[4][2]=50; pos[4][3]=20;
        pos[4][0]=400; pos[4][1]=350; pos[4][2]=50; pos[4][3]=20;
        pos[4][0]=400; pos[4][1]=400; pos[4][2]=50; pos[4][3]=20;
        pos[4][0]=400; pos[4][1]=450; pos[4][2]=50; pos[4][3]=20;
        pos[4][0]=400; pos[4][1]=500; pos[4][2]=50; pos[4][3]=20;
        for (int i=0; i<count; i++){
            char n[3];
            n[0]=scores[i]/10+48;
            n[1]=scores[i]%10+48;
            n[2]='\0';
            while (n[0]=='0'){
                for (int j=0; j<5; j++){
                    n[j]=n[j+1];
                }
            }
            if (n[0]=='\0')
                n[0]='0';
            shownumber(sdlRenderer, pos[i][0], pos[i][1], pos[i][2], pos[i][3], 50, 0, 0, 0, 255, inname[i]);
            shownumber(sdlRenderer, pos[i+5][0], pos[i+5][1], pos[i+5][2], pos[i+5][3], 50, 0, 0, 0, 255, n);
        }
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
            if (solds[counter5][i][1]-map[stop].x-length<20 && solds[counter5][i][2]-map[stop].y<20 && solds[counter5][i][1]-map[stop].x-length>-20 && solds[counter5][i][2]-map[stop].y>-20){
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
        if (solds[counter6][j][0]==-10000){
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

void drawpo(SDL_Renderer *sdlRenderer, int x, int y, Uint32 color){
    boxColor(sdlRenderer, x-15, y-15, x+15, y+15, color);
}

char* name(SDL_Renderer *sdlRenderer){
    char inname[10];
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
            }
            break;
        }
    }

}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Window *sdlWindow = SDL_CreateWindow("state.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
    SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    if ( TTF_Init() < 0 ) {
	printf("Error initializing SDL_ttf: %s\n", TTF_GetError());
    }

    
//int sel=0;
    srand(time(0));
    int randpo[40][2];
    int pospo[40][2];
    for (int i=0; i<40; i++){
        randpo[i][0] = rand()%4;
        randpo[i][1] = 1;
        pospo[i][0] = rand()%400+200;
        pospo[i][1] = rand()%400+200;
    }
    struct map map1[32];
    struct map map2[10];
    map2[0].x=50+(3*length);map2[1].x=50+(6*length);map2[2].x=50+(length/2+length);map2[3].x=50+(4*length+length/2);map2[4].x=50;map2[5].x=50+(6*length);map2[6].x=50;map2[7].x=50+(6*length);map2[8].x=50+(length/2+length);map2[9].x=50+(4*length+length/2);
    map2[0].y=100+(length/2)*sqrt(3);map2[1].y=100+(length/2)*sqrt(3);map2[2].y=100+(length)*sqrt(3);map2[3].y=100+(length)*sqrt(3);map2[4].y=100+(length/2+length)*sqrt(3);map2[5].y=100+(length/2+length)*sqrt(3);map2[6].y=100+(length/2+length*2)*sqrt(3);map2[7].y=100+(length/2+length*2)*sqrt(3);map2[8].y=100+(3*length)*sqrt(3);map2[9].y=100+(3*length)*sqrt(3);
    map2[3].color=0xff3c3c3c;map2[2].color=0xcca48100;map2[6].color=0xcca48187;map2[7].color=0xcc718b3c;map2[0].color=0xcc787878;map2[1].color=0xcc787878;map2[4].color=0xcc787878;map2[5].color=0xcc787878;map2[8].color=0xcc787878;map2[9].color=0xcc787878;
    struct map map3[13];
    map3[0].x=50;map3[1].x=50+(3*length);map3[2].x=50+(length/2+length);map3[3].x=50+(4*length+length/2);map3[4].x=50+(length*3);map3[5].x=50+(6*length);map3[6].x=50+(length/2+length);map3[7].x=50;map3[8].x=50+(6*length);map3[9].x=50+(length/2+length);map3[10].x=50;map3[11].x=50+(3*length);map3[12].x=50+(6*length);
    map3[0].y=100+(length/2)*sqrt(3);map3[1].y=100+(length/2)*sqrt(3);map3[2].y=100+(length)*sqrt(3);map3[3].y=100+(length)*sqrt(3);map3[4].y=100+(length/2+length)*sqrt(3);map3[5].y=100+(length/2+length)*sqrt(3);map3[6].y=100+(length*2)*sqrt(3);map3[7].y=100+(length/2+length*2)*sqrt(3);map3[8].y=100+(2*length+length/2)*sqrt(3);map3[9].y=100+(3*length)*sqrt(3);map3[10].y=100+(3*length+length/2)*sqrt(3);map3[11].y=100+(3*length+length/2)*sqrt(3);map3[12].y=100+(3*length+length/2)*sqrt(3);
    map3[4].color=0xff3c3c3c;map3[2].color=0xcca48100;map3[3].color=0xcca48187;map3[10].color=0xcc718b3c;map3[0].color=0xcc787878;map3[1].color=0xcc787878;map3[5].color=0xcc787878;map3[6].color=0xcc787878;map3[7].color=0xcc787878;map3[8].color=0xcc787878;map3[9].color=0xcc787878;map3[11].color=0xcc787878;map3[12].color=0xcc787878;
    struct map map4[14];
    map4[0].x=50;map4[1].x=50+(3*length);map4[2].x=50+(6*length);map4[3].x=50+(length+length/2);map4[4].x=50+(4*length+length/2);map4[5].x=50;map4[6].x=50+(6*length);map4[7].x=50;map4[8].x=50+(6*length);map4[9].x=50+(length+length/2);map4[10].x=50+(4*length+length/2);map4[11].x=50;map4[12].x=50+(length*3);map4[13].x=50+(length*6);
    map4[0].y=100+(length/2)*sqrt(3);map4[1].y=100+(length/2)*sqrt(3);map4[2].y=100+(length/2)*sqrt(3);map4[3].y=100+(length)*sqrt(3);map4[4].y=100+(length)*sqrt(3);map4[5].y=100+(length/2+length)*sqrt(3);map4[6].y=100+(length/2+length)*sqrt(3);map4[7].y=100+(length/2+length*2)*sqrt(3);map4[8].y=100+(2*length+length/2)*sqrt(3);map4[9].y=100+(3*length)*sqrt(3);map4[10].y=100+(3*length)*sqrt(3);map4[11].y=100+(3*length+length/2)*sqrt(3);map4[12].y=100+(3*length+length/2)*sqrt(3);map4[13].y=100+(3*length+length/2)*sqrt(3);
    map4[3].color=0xff3c3c3c;map4[10].color=0xff3c3c3c;map4[1].color=0xcca48100;map4[2].color=0xcca48100;map4[4].color=0xcca48100;map4[5].color=0xcca48100;map4[6].color=0xcca48100;map4[7].color=0xcca48100;map4[8].color=0xcca48100;map4[9].color=0xcca48100;map4[11].color=0xcca48100;map4[12].color=0xcca48100;map4[13].color=0xcca48100;map4[0].color=0xcc718b3c;
    int randomnums[32];
    int counter3=0;
    for (int i=0; i<32; i++){
        int r = rand()%3;
        randomnums[i]=r;
        if (r%2==0)
            counter3++;
    }
    for (int i=0; i<counter3; i++){
        map1[i].num=10;
    }
    Uint32 color[32];
    int flag = 1;
    while (flag){
        int s1=0,s2=0,s3=0,s4=0,s5=0;
        for (int i=0; i<32; i++){
            int r = rand()%5;
            if (r==0){
                if (randomnums[i]%2==0){
                    s1++;
                }
                color[i]=0xff3c3c3c;
            }
            if (r==1){
                if (randomnums[i]%2==0){
                    map1[s1+s2+s3+s4+s5].num=10;
                    s2++;
                }
                color[i]=0xcc787878;
            }
            if (r==2){
                if (randomnums[i]%2==0)
                    s3++;
                color[i]=0xcca48187;
            }
            if (r==3){
                if (randomnums[i]%2==0)
                    s4++;
                color[i]=0xcca48100;
            }
            if (r==4){
                if (randomnums[i]%2==0)
                    s5++;
                color[i]=0xcc718b3c;
            }
        }
        if (s1!=0 && s2>=4 && s3!=0 && s4!=0 && s5!=0 && s3-s4<2 && s4-s3<2 && s3-s5<2 && s5-s3<2 && s4-s5<2 && s5-s4<2){
            flag=0;
        }
    }
    int counter4=0, counter5=0;
    int state=0;
    int start=-1, stop=-1, number;
    int x, y, dx, dy;
    int dspeed[3];
    int numpo=0, timepo=0;
    int maxnum[3]={50};
    int z[3]={1};
    for (int i=0; i<3; i++){
        z[i]=1;
        maxnum[i]=50;
        dspeed[i]=15;
    }
        int counter=0, counter2=0;
        for (int i=0; i<7; i++){
            if (i%2==0){
                for (int j=0; j<3; j++){
                    if (randomnums[counter]%2==0){
                        map1[counter2].x=50+(length*j*3);
                        map1[counter2].y=100+((length/2*sqrt(3))*(1+(i)));
                        map1[counter2].color=color[counter];
                        map1[counter2].avpo=0;
                        counter2++;
                    }     
                    counter++;
                }
            }
            else{
                for (int j=0; j<2; j++){
                    if (randomnums[counter]%2==0){
                        map1[counter2].x=50+(length+(length/2))+(length*j*3);
                        map1[counter2].y=100+((length/2*sqrt(3))*(1+(i)));
                        map1[counter2].color=color[counter];
                        map1[counter2].avpo=0;
                        counter2++;
                    }
                    counter++;
                }
            }
        }
        int attackstate[counter2][counter2][5];
        for (int i=0; i<counter2; i++){
            for (int j=0; j<counter2; j++){
                for (int k=0; k<3; k++){
                    attackstate[i][j][k]=0;
                }
            }
        }
        double dxy[counter2*counter2][2];
        int timepocounter[counter2];
        for (int i=0; i<counter2; i++){
            timepocounter[i]=0;
        }
        int inpo=0;
    SDL_bool shallExit = SDL_FALSE;
    struct map map[32];
    char* inname2=name(sdlRenderer);
    int idk=0, now;
    for (int i=0; i<count; i++){
        if (*inname[i]!=*inname2){
            idk++;
        }
        else{
            now=i;
        }
    }
    if (idk==count && count!=5){
        inname[count]=inname2;
        now=count;
        count++;
    }
    int sel2;
    int sel=showmenu(sdlRenderer);
    if (sel==1){
        shallExit = SDL_TRUE;
    }
    else if (sel==2){
        shallExit = SDL_TRUE;
        showranks(sdlRenderer);
    }
    else{
        sel2=showmaps(sdlRenderer);
        if (sel2==0){
            for (int i=0; i<counter2; i++){
                map[i].x=map1[i].x;
                map[i].y=map1[i].y;
                map[i].num=map1[i].num;
                map[i].color=map1[i].color;
                map[i].avpo=0;
            }
        }
        else if (sel2==1){
            counter2=10;
            for (int i=0; i<counter2; i++){
                map[i].x=map2[i].x;
                map[i].y=map2[i].y;
                map[i].num=10;
                map[i].color=map2[i].color;
                map[i].avpo=0;
            }
        }
        else if (sel2==2){
            counter2=13;
            for (int i=0; i<counter2; i++){
                map[i].x=map3[i].x;
                map[i].y=map3[i].y;
                map[i].num=10;
                map[i].color=map3[i].color;
                map[i].avpo=0;
            }
        }
        else if (sel2==3){
            counter2=14;
            for (int i=0; i<counter2; i++){
                map[i].x=map4[i].x;
                map[i].y=map4[i].y;
                map[i].num=10;
                map[i].color=map4[i].color;
                map[i].avpo=0;
            }
        }
    }
    while (shallExit == SDL_FALSE) {
        SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(sdlRenderer);
        char labels[2][13];
        int pos[2][4];
        pos[0][0]=50; pos[0][1]=20; pos[0][2]=200; pos[0][3]=40;
        labels[0][0]='y';labels[0][1]='o';labels[0][2]='u';labels[0][3]='\'';labels[0][4]='r';labels[0][5]='e';labels[0][6]=' ';labels[0][7]='b';labels[0][8]='l';labels[0][9]='u';labels[0][10]='e';labels[0][11]='!';labels[0][12]='\0';
        if (counter4<=100){
            shownumber(sdlRenderer, pos[0][0], pos[0][1], pos[0][2], pos[0][3], 30, 0, 0, 0, 255, labels[0]);
        }
        for (int i=0; i<counter2; i++){
            draw(sdlRenderer, map[i].y, map[i].x, map[i].color);
        }

        int check;
        if (counter4%900<=400){
            check=0;
            if (randpo[numpo][0]==0){
                showimage(sdlRenderer, "//home//paria//Desktop//state.io//images//1.bmp", pospo[numpo][0], pospo[numpo][1], 40, 60);
            }
            if (randpo[numpo][0]==1){
                showimage(sdlRenderer, "//home//paria//Desktop//state.io//images//3.bmp", pospo[numpo][0], pospo[numpo][1], 40, 60);
            }
            if (randpo[numpo][0]==2){
                showimage(sdlRenderer, "//home//paria//Desktop//state.io//images//4.bmp", pospo[numpo][0], pospo[numpo][1], 40, 60);
            }
            if (randpo[numpo][0]==3){
                showimage(sdlRenderer, "//home//paria//Desktop//state.io//images//5.bmp", pospo[numpo][0], pospo[numpo][1], 40, 60);
            }
            /*if (timepocounter[inpo]==500){
                numpo++;
            }*/
        }

        for (int i=0; i<counter2; i++){
            int colornum;
            if (map[i].color==0xcca48187 || map[i].color==0xcca48100 || map[i].color==0xcc718b3c){
                if (map[i].color==0xcca48187) colornum=0;
                if (map[i].color==0xcca48100) colornum=1;
                if (map[i].color==0xcc718b3c) colornum=2;
                char n[6];
                n[0]=map[i].num/10000+48;
                n[1]=map[i].num/1000+48;
                n[2]=map[i].num/100+48;
                n[3]=map[i].num/10+48;
                n[4]=map[i].num%10+48;
                n[5]='\0';
                while (n[0]=='0'){
                    for (int j=0; j<5; j++){
                        n[j]=n[j+1];
                    }
                }
                if (n[0]=='\0')
                    n[0]='0';
                shownumber(sdlRenderer, map[i].x+length-5, map[i].y+length/4+15, 15, 30, 30, 0, 0, 0, 255, n);
                if (map[i].num<maxnum[colornum] && counter4%(20/z[colornum])==0)
                    map[i].num++;
            }
            if (map[i].color==0xcc787878){
                char n[6];
                n[0]=map[i].num/10000+48;
                n[1]=map[i].num/1000+48;
                n[2]=map[i].num/100+48;
                n[3]=map[i].num/10+48;
                n[4]=map[i].num%10+48;
                n[5]='\0';
                while (n[0]=='0'){
                    for (int j=0; j<5; j++){
                        n[j]=n[j+1];
                    }
                }
                if (n[0]=='\0')
                    n[0]='0';
                shownumber(sdlRenderer, map[i].x+length-5, map[i].y+length/4+15, 15, 30, 30, 0, 0, 0, 255, n);
                if (map[i].num<10 && counter4%20==0)
                    map[i].num++;
            }
        }

        Uint32 buttons;
        state=0;
        SDL_Event ev;
        double solds[counter2*10][1000][3];
        while (SDL_PollEvent(&ev) != 0){
            switch(ev.type){
            case SDL_QUIT:
                shallExit = SDL_TRUE;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_PumpEvents();
                buttons = SDL_GetMouseState(&x, &y);
                start = findhex(ev.button.x, ev.button.y, counter2, map);
                number = map[start].num;
                for (int i=0; i<number; i++){
                    solds[counter5][i][0]=i-number+2;
                    solds[counter5][i][1]=map[start].x+length;
                    solds[counter5][i][2]=map[start].y;
                } 
                break;
            case SDL_MOUSEBUTTONUP:
                SDL_PumpEvents();
                if (start!=-1){
                    buttons = SDL_GetMouseState(&x, &y);
                    stop = findhex(ev.button.x, ev.button.y, counter2, map);
                    attackstate[start][stop][0]=1;
                    attackstate[start][stop][3]=number;  
                    attackstate[start][stop][4]=counter5;
                    dxy[counter5][0]=map[stop].x-map[start].x;
                    dxy[counter5][1]=map[stop].y-map[start].y;
                    counter5++;
                }
                break;
            }
        }

        if (counter4%5==0){
            for (int i=0; i<counter2; i++){
                for (int j=0; j<counter2; j++){
                    if (attackstate[i][j][0]==1){
                        int speed;
                        if (map[i].color==0xcca48187) speed=dspeed[0];
                        if (map[i].color==0xcca48100) speed=dspeed[1];
                        if (map[i].color==0xcc718b3c) speed=dspeed[2];
                        attack(sdlRenderer, attackstate[i][j][3], i, j, counter2, dxy[attackstate[i][j][4]][0], dxy[attackstate[i][j][4]][1], map, speed, solds, attackstate[i][j][4], attackstate);
                    }
                }
            }
        }

        Uint32 fincol[32];
        int counter7=0;
        for (int i=0; i<counter2; i++){
            if (map[i].color==0xcca48187 || map[i].color==0xcca48100 || map[i].color==0xcc718b3c){
                fincol[counter7]=map[i].color;
                counter7++;
            }
        }
        int finish=0;
        for (int i=0; i<counter7-1; i++){
            if (fincol[i]==fincol[i+1]){
                finish++;
            }
        }
        if (finish==counter7-1){
            if (fincol[0]==0xcca48100){
                scores[now]++;
            }
            else{
                scores[now]--;
            }
            shallExit = SDL_TRUE;
        }

        for (int i=0; i<counter2; i++){
            for (int j=0; j<counter2; j++){
                for (int k=0; k<counter2; k++){
                    for (int l=0; l<counter2; l++){
                        if (attackstate[i][j][0]==1 && attackstate[k][l][0]==1 && map[i].color==map[k].color){
                            for (int m=0; m<attackstate[i][j][3]; m++){
                                for (int n=0; n<attackstate[k][l][3]; n++){
                                    if (solds[attackstate[i][j][4]][m][1]-solds[attackstate[k][l][4]][n][1]<10 && solds[attackstate[i][j][4]][m][2]-solds[attackstate[k][l][4]][n][2]<10 && solds[attackstate[i][j][4]][m][1]-solds[attackstate[k][l][4]][n][1]>-10 && solds[attackstate[i][j][4]][m][2]-solds[attackstate[k][l][4]][n][2]>-10){
                                        solds[attackstate[i][j][4]][m][0]==-10000;
                                        solds[attackstate[k][l][4]][n][0]==-10000;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        for (int i=0; i<counter2; i++){
            for (int j=0; j<counter2; j++){
                if (attackstate[i][j][0]==1){
                    for (int k=0; k<attackstate[i][j][3]; k++){
                        if (solds[attackstate[i][j][4]][k][1]-pospo[numpo][0]<36 && solds[attackstate[i][j][4]][k][2]-pospo[numpo][1]<36 && solds[attackstate[i][j][4]][k][1]-pospo[numpo][0]>-36 && solds[attackstate[i][j][4]][k][2]-pospo[numpo][1]>-36 && randpo[numpo][1]==1){
                            randpo[numpo][1]=0;
                            inpo=i;
                            map[i].avpo=1;
                            break;
                        }
                    }
                }
            }
        }

        for (int i=0; i<counter2; i++){
            if (map[i].avpo==1){
                timepocounter[i]++;
                if (timepocounter[i]>400){
                    timepocounter[i]=0;
                    map[i].avpo=0;
                    numpo++;
                    if (randpo[numpo-1][0]==0){
                        if (map[i].color==0xcca48187) dspeed[0]=15;
                        if (map[i].color==0xcca48100) dspeed[1]=15;
                        if (map[i].color==0xcc718b3c) dspeed[2]=15;
                    }
                    if (randpo[numpo-1][0]==1){
                        if (map[i].color==0xcca48187){ dspeed[1]=15; dspeed[2]=15;}
                        if (map[i].color==0xcca48100){ dspeed[0]=15; dspeed[2]=15;}
                        if (map[i].color==0xcc718b3c){ dspeed[0]=15; dspeed[1]=15;}
                    }
                    if (randpo[numpo-1][0]==2){
                        if (map[i].color==0xcca48187) maxnum[0]=50;
                        if (map[i].color==0xcca48100) maxnum[1]=50;
                        if (map[i].color==0xcc718b3c) maxnum[2]=50;
                    }
                    if (randpo[numpo-1][0]==3){
                        if (map[i].color==0xcca48187) z[0]=1;
                        if (map[i].color==0xcca48100) z[1]=1;
                        if (map[i].color==0xcc718b3c) z[2]=1;
                    }
                }
                else{
                    for (int j=0; j<counter2; j++){
                        if (map[j].color==map[i].color){
                            filledCircleColor(sdlRenderer, map[j].x+length+length/2, map[j].y-40, 5, 0xff0000ff);
                        }
                    }
                    if (randpo[numpo][0]==0){
                        if (map[i].color==0xcca48187) dspeed[0]=5;
                        if (map[i].color==0xcca48100) dspeed[1]=5;
                        if (map[i].color==0xcc718b3c) dspeed[2]=5;
                    }
                    if (randpo[numpo][0]==1){
                        if (map[i].color==0xcca48187){ dspeed[1]=50; dspeed[2]=50;}
                        if (map[i].color==0xcca48100){ dspeed[0]=50; dspeed[2]=50;}
                        if (map[i].color==0xcc718b3c){ dspeed[0]=50; dspeed[1]=50;}
                    }
                    if (randpo[numpo][0]==2){
                        if (map[i].color==0xcca48187) maxnum[0]=10000;
                        if (map[i].color==0xcca48100) maxnum[1]=10000;
                        if (map[i].color==0xcc718b3c) maxnum[2]=10000;
                    }
                    if (randpo[numpo][0]==3){
                        if (map[i].color==0xcca48187) z[0]=2;
                        if (map[i].color==0xcca48100) z[1]=2;
                        if (map[i].color==0xcc718b3c) z[2]=2;
                    }
                }
            }
        }
        int counter8=0;
        for (int i=0; i<counter2; i++){
            if (map[i].avpo==0){
                counter8++;
            }
        }
        if (counter8==counter2 && counter4%900>400 && check==0){
            numpo++;
            check=1;
        }

        for (int i=0; i<counter2; i++){
            int min=1000;
            int number2=0;
            if (map[i].color==0xcca48187 || map[i].color==0xcc718b3c){
                if ((map[i].num>=30 && map[i].color==0xcca48187) || (map[i].color==0xcc718b3c && map[i].num>=15)){
                    for (int j=0; j<counter2; j++){
                        if (map[j].num<min && map[j].color!=0xff3c3c3c){
                            min=map[j].num;
                            number2=j;
                        }
                    }
                    int t=0;
                    for (int j=0; j<counter2; j++){
                        if (attackstate[i][j][0]==0){
                            t++;
                        }
                    }
                    //printf("%d \n", t);
                    if (t==counter2){
                        number = map[i].num;
                        for (int j=0; j<number; j++){
                            solds[counter5][j][0]=j-number+2;
                            solds[counter5][j][1]=map[i].x+length;
                            solds[counter5][j][2]=map[i].y;
                        } 
                        attackstate[i][number2][0]=1;
                        attackstate[i][number2][3]=number;  
                        attackstate[i][number2][4]=counter5;
                        dxy[counter5][0]=map[number2].x-map[i].x;
                        dxy[counter5][1]=map[number2].y-map[i].y;
                        counter5++;
                    }
                }
            }
        }

        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(1000/FPS); 
        counter4++;
    }

    SDL_DestroyWindow(sdlWindow);
    printf("Hello World\n");
    SDL_Quit();
    return 0;
}