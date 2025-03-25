#include "Font.h"
#include <iostream>

Font::Font() : font(nullptr), color({255, 255, 255}) {}


bool Font::init(const std::string& fontPath, int fontSize, SDL_Color textColor) {
    if (TTF_Init() == -1) {
    std::cerr << "TTF_Init error: " << TTF_GetError() << std::endl;
    return false;
    }
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    color = textColor;

    if (!font) {
        std::cout << "Error in loading font: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}


Font::~Font() {
    if (font) {
        TTF_CloseFont(font);
    }
}


void Font::render(SDL_Renderer* renderer, const std::string& text, int x, int y, double scaleW, double scaleH) {
    if (!font) return;

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!textSurface) {
        std::cout << "Can't create Surface: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        std::cout << "Can't create Texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect textRect = { x, y, (textSurface->w) * scaleW, (textSurface->h) * scaleH };
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}


