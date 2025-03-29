#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <fstream>

#include <SDL.h>
#include <SDL_image.h>

#include "Defs.h"

struct Graphics {
    SDL_Window* gwindow;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    const char *title = "Hollow Knight";
    bool fullscr = 0;

    void LogErrAndExit(const char *msg, const char *err);

    void init();

    SDL_Texture *loadTexture(const char *filename);


    void prepareScene(SDL_Texture *background);

    void renderTexture(SDL_Texture *image, const double x, const double y, const double w, const double h);

    void renderTexture(SDL_Texture *image, const double x, const double y, const double w, const double h, const double cx, const double cy, const double cw, const double ch);

    void renderTexture(SDL_Texture *image, const double x, const double y);

    void presentScene();

    void drawMovingIMG(SDL_Texture *IMG,SDL_Texture *background, double x1,double y1,double w1,double h1,double x2,double y2,double w2,double h2, double t);

    void quit();

};

long long loadHighScore(const std::string& filename);

void saveHighScore(const std::string& filename, long long newScore);

#endif

