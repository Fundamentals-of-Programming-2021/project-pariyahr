struct map{
    int x;
    int y;
    Uint32 color;
    int num;
    int avpo;
};
void shownumber(SDL_Renderer *sdlRenderer, double x, double y, double w, double h, int fontsize, int R, int G, int B, int A, const char *n);
void showimage(SDL_Renderer *sdlRenderer, char *image_path, int x, int y, int w, int h);
int showmenu(SDL_Renderer *sdlRenderer);
int showmaps(SDL_Renderer *sdlRenderer);
void showranks(SDL_Renderer *sdlRenderer, char *ranks[5], int points[5], int index);
void draw(SDL_Renderer *sdlRenderer,int j, int i, Uint32 color);
void drawsolds(SDL_Renderer *sdlRenderer, int x, int y, Uint32 color);
int findhex(Sint32 x, Sint32 y, int counter2, struct map map[32]);
void attack(SDL_Renderer *sdlRenderer, int number, int start, int stop, int counter2, double dx, double dy, struct map map[32], int dspeed, double solds[counter2*3][1000][3], int counter5, int attackstate[counter2][counter2][5]);
char* name(SDL_Renderer *sdlRenderer);