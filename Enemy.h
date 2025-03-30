#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <random>
#include <unordered_set>
#include <chrono>

#include <SDL.h>
#include <SDL_image.h>

#include "graphics.h"


struct Enemy {

    int type;
    int portrait;

    int delayFrames;
    double StartX, StartY; // Vị trí ban đầu
    double PosX, PosY; // Vị trí hiện tại
    double targetX, targetY; // Vị trí mục tiêu
    double EWidth, EHeight; // Kích thước hiện tại

    Enemy(int _type);

    void move(double SPD);
    bool hasReachedTarget() const;
};

extern std::vector<Enemy> enemies;
void UpdateEnemies(long long Score, double SPD);

std::vector<SDL_Texture*> loadEnemies(Graphics &graphics);
void renderEnemy(Graphics& graphics, Enemy enemy,std::vector<SDL_Texture*> enemiesVec);

#endif // ENEMY_H
