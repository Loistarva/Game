#include <SDL.h>
#include <SDL_image.h>
#include "Grahics.h"
#include "Defs.h"

using namespace std;



void Graphics::LogErrAndExit(const char *msg, const char *err) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s %s", msg, err);
    SDL_Quit();
}

void Graphics::init() {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        LogErrAndExit("SDL Init ", SDL_GetError());
    }
    if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
        LogErrAndExit("IMG Init ", IMG_GetError());
    }
    if(!fullscr) {
        gwindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Gwidth, Gheight, SDL_WINDOW_SHOWN);
    } else gwindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Gwidth, Gheight, SDL_WINDOW_FULLSCREEN);
    if(gwindow==nullptr) {
        LogErrAndExit("Create Window ", SDL_GetError());
    }
    renderer = SDL_CreateRenderer(gwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer==nullptr) {
        LogErrAndExit("Create Renderer ", SDL_GetError());
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, Gwidth, Gheight);
}

SDL_Texture *Graphics::loadTexture(const char *filename) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    Graphics::texture = IMG_LoadTexture(renderer, filename);
    if(texture==nullptr) {
        LogErrAndExit("Fail in loading texture",IMG_GetError());
    }
    return texture;
}

void Graphics::prepareScene(SDL_Texture *background) {
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL , NULL);
}

void Graphics::renderTexture(SDL_Texture *image, const double x, const double y, const double w, const double h, const double cx, const double cy, const double cw, const double ch) {
    SDL_Rect PrsDest = {x,y,w,h};
    SDL_Rect CutDest = {cx,cy,cw,ch};
    SDL_RenderCopy(renderer, image, &CutDest, &PrsDest);

}

void Graphics::renderTexture(SDL_Texture *image, const double x, const double y) {
    SDL_RenderCopy(renderer,image,NULL,NULL);
}

void Graphics::renderTexture(SDL_Texture *image, const double x, const double y, const double w, const double h) {
    SDL_Rect Dest = {x,y,w,h};
    SDL_RenderCopy(renderer,image,NULL,&Dest);
}

void Graphics::presentScene() {
    SDL_RenderPresent(renderer);
}

void Graphics::quit() {
    SDL_DestroyWindow(gwindow);
    SDL_DestroyTexture(texture);
    SDL_Quit();
    IMG_Quit();
}

void TurnRight(int& x, const int v) {
    x+=1000/FPS*v;
}

void TurnLeft(int &x,const int v) {
    x-=1000/FPS*v;
}

void Up(int &y, const int v) {
    y-=1000/FPS*v;
}

void Down(int &y, const int v) {
    y+=1000/FPS*v;
}

