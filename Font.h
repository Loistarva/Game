#ifndef FONT_H
#define FONT_H

#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>
#include <string>

#include "Defs.h"

struct Font {
    TTF_Font* font;
    SDL_Color color;

    Font();
    ~Font();

    void close();


    bool init(const std::string& fontPath, int fontSize, SDL_Color textColor);
    void render(SDL_Renderer* renderer, const std::string& text, int x, int y, double scaleW, double scaleH);
};

bool initFonts(Font& scoreFont, Font& Title, Font& TellScore);

#endif

