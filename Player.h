#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#include "Grahics.h"
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

void renderPlayer(Graphics& graphics, const Player& player, const std::vector<SDL_Texture*>& PlayerVec, int frameCount);

#endif // PLAYER_H

