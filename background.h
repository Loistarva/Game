#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <vector>


#include <SDL.h>
#include <SDL_image.h>

#include "graphics.h"
#include "Defs.h"
#include "Enemy.h"
#include "Player.h"


struct Background {
    SDL_Texture* leftForest;
    SDL_Texture* rightForest;
    SDL_Texture* top;
    SDL_Texture* sky;
    SDL_Texture* blur;
    SDL_Texture* menuKnight;
    SDL_Texture* BloodScreen;
};

void renderPlayerAndEnemies(const std::vector<Enemy> &enemies, std::vector<SDL_Texture*> EnemiesV, Player &player, std::vector<SDL_Texture*> PlayerV, Graphics &graphics, int &HurtFrame, Background bg);

Background loadBackground(Graphics &graphics);

std::vector<SDL_Texture*> loadGroundTextures(Graphics &graphics);

void renderBackground(Graphics &graphics, Background &bg, double speed, const std::vector<SDL_Texture*> &GroundV);

void scrollingLeftForest(const double v,Graphics graphics ,SDL_Texture* LeftForest);

void scrollingRightForest(const double v, Graphics graphics, SDL_Texture* RightForest);

void scrollingSky(Graphics graphics,SDL_Texture* Sky);

void scrollingGround(Graphics graphics,std::vector<SDL_Texture*> ground,double v);

struct ScrollingBackground {
    SDL_Texture *texture;
    double offsetX = 0;
    double SPD = 2;
    double sclae = 1;
    double scaleSPD = 0.02;
    double h,w;

};
#endif // BACKGROUND_H
