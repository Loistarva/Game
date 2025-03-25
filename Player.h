#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#include "graphics.h"
#include "Enemy.h"

struct Player {
    double PosX, PosY; // Vị trí hiện tại
    double PWidth, PHeight; // Kích thước Player
    int laneIndex; // Chỉ số làn đường (0-4)
    std::vector<double> lanes; // Danh sách vị trí X của các làn đường

    Player(double startY);
    void moveLeft();
    void moveRight();
    bool checkCollision(const std::vector<Enemy>& enemies) const;
};

std::vector<SDL_Texture*> loadPlayer(Graphics& graphics);

void renderPlayer(Graphics& graphics, const Player& player, const std::vector<SDL_Texture*>& PlayerVec);

#endif // PLAYER_H

